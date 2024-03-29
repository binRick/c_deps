
#include "ansi-codes/ansi-codes.h"
#include "bytes/bytes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "log/log.h"
#include "ms/ms.h"
#include "timestamp/timestamp.h"
#include "wslay-test/wslay-test.h"
#include "wslay/wslay.h"

#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <poll.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <nettle/base64.h>
#include <nettle/sha.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wslay/wslay.h>

static int create_listen_socket(const char *service) {
  struct addrinfo hints, *res, *rp;
  int             sfd = -1;
  int             r;

  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family   = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags    = AI_PASSIVE | AI_ADDRCONFIG;
  r                 = getaddrinfo(0, service, &hints, &res);
  if (r != 0) {
    fprintf(stderr, "getaddrinfo: %s", gai_strerror(r));
    return(-1);
  }
  for (rp = res; rp; rp = rp->ai_next) {
    int val = 1;
    sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
    if (sfd == -1)
      continue;
    if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &val,
                   (socklen_t)sizeof(val)) == -1)
      continue;
    if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0)
      break;
    close(sfd);
  }
  freeaddrinfo(res);
  if (listen(sfd, 16) == -1) {
    perror("listen");
    close(sfd);
    return(-1);
  }
  return(sfd);
}

/*
 * Makes file descriptor *fd* non-blocking mode.
 * This function returns 0, or returns -1.
 */
static int make_non_block(int fd) {
  int flags, r;

  while ((flags = fcntl(fd, F_GETFL, 0)) == -1 && errno == EINTR) {
  }
  if (flags == -1) {
    perror("fcntl");
    return(-1);
  }
  while ((r = fcntl(fd, F_SETFL, flags | O_NONBLOCK)) == -1 && errno == EINTR) {
  }
  if (r == -1) {
    perror("fcntl");
    return(-1);
  }
  return(0);
}

/*
 * Calculates SHA-1 hash of *src*. The size of *src* is *src_length* bytes.
 * *dst* must be at least SHA1_DIGEST_SIZE.
 */
static void sha1(uint8_t *dst, const uint8_t *src, size_t src_length) {
  struct sha1_ctx ctx;

  sha1_init(&ctx);
  sha1_update(&ctx, src_length, src);
  sha1_digest(&ctx, SHA1_DIGEST_SIZE, dst);
}

/*
 * Base64-encode *src* and stores it in *dst*.
 * The size of *src* is *src_length*.
 * *dst* must be at least BASE64_ENCODE_RAW_LENGTH(src_length).
 */
static void base64(uint8_t *dst, const uint8_t *src, size_t src_length) {
  struct base64_encode_ctx ctx;

  base64_encode_init(&ctx);
  base64_encode_raw((char *)dst, src_length, src);
}

#define WS_GUID    "258EAFA5-E914-47DA-95CA-C5AB0DC85B11"

/*
 * Create Server's accept key in *dst*.
 * *client_key* is the value of |Sec-WebSocket-Key| header field in
 * client's handshake and it must be length of 24.
 * *dst* must be at least BASE64_ENCODE_RAW_LENGTH(20)+1.
 */
static void create_accept_key(char *dst, const char *client_key) {
  uint8_t sha1buf[20], key_src[60];

  memcpy(key_src, client_key, 24);
  memcpy(key_src + 24, WS_GUID, 36);
  sha1(sha1buf, key_src, sizeof(key_src));
  base64((uint8_t *)dst, sha1buf, 20);
  dst[BASE64_ENCODE_RAW_LENGTH(20)] = '\0';
}

/* We parse HTTP header lines of the format
 *   \r\nfield_name: value1, value2, ... \r\n
 *
 * If the caller is looking for a specific value, we return a pointer to the
 * start of that value, else we simply return the start of values list.
 */
static const char *http_header_find_field_value(const char *header,
                                                const char *field_name,
                                                const char *value) {
  const char *header_end, *field_start, *field_end, *next_crlf, *value_start;
  int        field_name_len;

  /* Pointer to the last character in the header */
  header_end = header + strlen(header) - 1;

  field_name_len = (int)strlen(field_name);

  field_start = header;

  do {
    field_start = strstr(field_start + 1, field_name);

    field_end = field_start + field_name_len - 1;

    if (field_start != NULL && field_start - header >= 2
        && field_start[-2] == '\r' && field_start[-1] == '\n'
        && header_end - field_end >= 1 && field_end[1] == ':') {
      break;    /* Found the field */
    } else {
      continue; /* This is not the one; keep looking. */
    }
  } while (field_start != NULL);

  if (field_start == NULL)
    return(NULL);

  /* Find the field terminator */
  next_crlf = strstr(field_start, "\r\n");

  /* A field is expected to end with \r\n */
  if (next_crlf == NULL) {
    return(NULL); /* Malformed HTTP header! */
  }
  /* If not looking for a value, then return a pointer to the start of values string */
  if (value == NULL)
    return(field_end + 2);

  value_start = strstr(field_start, value);

  /* Value not found */
  if (value_start == NULL)
    return(NULL);

  /* Found the value we're looking for */
  if (value_start > next_crlf) {
    return(NULL); /* ... but after the CRLF terminator of the field. */
  }
  /* The value we found should be properly delineated from the other tokens */
  if (isalnum(value_start[-1]) || isalnum(value_start[strlen(value)]))
    return(NULL);

  return(value_start);
} /* http_header_find_field_value */

/*
 * Performs HTTP handshake. *fd* is the file descriptor of the
 * connection to the client. This function returns 0 if it succeeds,
 * or returns -1.
 */
static int http_handshake(int fd) {
  /*
   * Note: The implementation of HTTP handshake in this function is
   * written for just a example of how to use of wslay library and is
   * not meant to be used in production code.  In practice, you need
   * to do more strict verification of the client's handshake.
   */
  char       header[16384], accept_key[29], res_header[256];
  const char *keyhdstart, *keyhdend;
  size_t     header_length = 0, res_header_sent = 0, res_header_length;
  ssize_t    r;

  while (1) {
    while ((r = read(fd, header + header_length,
                     sizeof(header) - header_length)) == -1
           && errno == EINTR) {
    }
    if (r == -1) {
      perror("read");
      return(-1);
    } else if (r == 0) {
      fprintf(stderr, "HTTP Handshake: Got EOF");
      return(-1);
    } else {
      header_length += (size_t)r;
      if (header_length >= 4
          && memcmp(header + header_length - 4, "\r\n\r\n", 4) == 0)
        break;
      else if (header_length == sizeof(header)) {
        fprintf(stderr, "HTTP Handshake: Too large HTTP headers");
        return(-1);
      }
    }
  }

  if (http_header_find_field_value(header, "Upgrade", "websocket") == NULL
      || http_header_find_field_value(header, "Connection", "Upgrade") == NULL
      || (keyhdstart = http_header_find_field_value(header, "Sec-WebSocket-Key",
                                                    NULL)) == NULL) {
    fprintf(stderr, "HTTP Handshake: Missing required header fields");
    return(-1);
  }
  for ( ; *keyhdstart == ' '; ++keyhdstart) {
  }
  keyhdend = keyhdstart;
  for ( ; *keyhdend != '\r' && *keyhdend != ' '; ++keyhdend) {
  }
  if (keyhdend - keyhdstart != 24) {
    printf("%s\n", keyhdstart);
    fprintf(stderr, "HTTP Handshake: Invalid value in Sec-WebSocket-Key");
    return(-1);
  }
  create_accept_key(accept_key, keyhdstart);
  snprintf(res_header, sizeof(res_header),
           "HTTP/1.1 101 Switching Protocols\r\n"
           "Upgrade: websocket\r\n"
           "Connection: Upgrade\r\n"
           "Sec-WebSocket-Accept: %s\r\n"
           "\r\n",
           accept_key);
  res_header_length = strlen(res_header);
  while (res_header_sent < res_header_length) {
    while ((r = write(fd, res_header + res_header_sent,
                      res_header_length - res_header_sent)) == -1
           && errno == EINTR) {
    }
    if (r == -1) {
      perror("write");
      return(-1);
    } else
      res_header_sent += (size_t)r;
  }
  return(0);
} /* http_handshake */

/*
 * This struct is passed as *user_data* in callback function.  The
 * *fd* member is the file descriptor of the connection to the client.
 */
struct Session {
  int fd;
};

static ssize_t send_callback(wslay_event_context_ptr ctx, const uint8_t *data,
                             size_t len, void *user_data) {
  struct Session *session = (struct Session *)user_data;
  ssize_t        r;
  int            sflags = 0;

#ifdef MSG_MORE
  if (flags & WSLAY_MSG_MORE)
    sflags |= MSG_MORE;
#endif // MSG_MORE
  while ((r = send(session->fd, data, len, sflags)) == -1 && errno == EINTR) {
  }
  if (r == -1) {
    if (errno == EAGAIN || errno == EWOULDBLOCK)
      wslay_event_set_error(ctx, WSLAY_ERR_WOULDBLOCK);
    else
      wslay_event_set_error(ctx, WSLAY_ERR_CALLBACK_FAILURE);
  }
  return(r);
}

static ssize_t recv_callback(wslay_event_context_ptr ctx, uint8_t *buf,
                             size_t len, int flags, void *user_data) {
  struct Session *session = (struct Session *)user_data;
  ssize_t        r;

  (void)flags;
  while ((r = recv(session->fd, buf, len, 0)) == -1 && errno == EINTR) {
  }
  if (r == -1) {
    if (errno == EAGAIN || errno == EWOULDBLOCK)
      wslay_event_set_error(ctx, WSLAY_ERR_WOULDBLOCK);
    else
      wslay_event_set_error(ctx, WSLAY_ERR_CALLBACK_FAILURE);
  } else if (r == 0) {
    /* Unexpected EOF is also treated as an error */
    wslay_event_set_error(ctx, WSLAY_ERR_CALLBACK_FAILURE);
    r = -1;
  }
  return(r);
}

static void on_msg_recv_callback(wslay_event_context_ptr                  ctx,
                                 const struct wslay_event_on_msg_recv_arg *arg,
                                 void                                     *user_data) {
  (void)user_data;
  /* Echo back non-control message */
  if (!wslay_is_ctrl_frame(arg->opcode)) {
    log_debug("recv|%s|%lu|%d|%d|%d|", arg->msg, arg->msg_length, arg->opcode, arg->status_code, arg->rsv);
    struct wslay_event_msg msgarg = { arg->opcode, arg->msg, arg->msg_length };
    wslay_event_queue_msg(ctx, &msgarg);
  }
}

/*
 * Communicate with the client. This function performs HTTP handshake
 * and WebSocket data transfer until close handshake is done or an
 * error occurs. *fd* is the file descriptor of the connection to the
 * client. This function returns 0 if it succeeds, or returns 0.
 */
static int communicate(int fd) {
  wslay_event_context_ptr      ctx;
  struct wslay_event_callbacks callbacks = {
    recv_callback, send_callback, NULL, NULL, NULL,
    NULL,          on_msg_recv_callback
  };
  struct Session               session = { fd };
  int                          val     = 1;
  struct pollfd                event;
  int                          res = 0;

  if (http_handshake(fd) == -1)
    return(-1);

  if (make_non_block(fd) == -1)
    return(-1);

  if (setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &val, (socklen_t)sizeof(val)) ==
      -1) {
    perror("setsockopt: TCP_NODELAY");
    return(-1);
  }
  memset(&event, 0, sizeof(struct pollfd));
  event.fd     = fd;
  event.events = POLLIN;
  wslay_event_context_server_init(&ctx, &callbacks, &session);
  /*
   * Event loop: basically loop until both wslay_event_want_read(ctx)
   * and wslay_event_want_write(ctx) return 0.
   */
  while (wslay_event_want_read(ctx) || wslay_event_want_write(ctx)) {
    int r;
    while ((r = poll(&event, 1, -1)) == -1 && errno == EINTR) {
    }
    if (r == -1) {
      perror("poll");
      res = -1;
      break;
    }
    if (((event.revents & POLLIN) && wslay_event_recv(ctx) != 0)
        || ((event.revents & POLLOUT) && wslay_event_send(ctx) != 0)
        || (event.revents & (POLLERR | POLLHUP | POLLNVAL))) {
      /*
       * If either wslay_event_recv() or wslay_event_send() return
       * non-zero value, it means serious error which prevents wslay
       * library from processing further data, so WebSocket connection
       * must be closed.
       */
      res = -1;
      break;
    }
    event.events = 0;
    if (wslay_event_want_read(ctx))
      event.events |= POLLIN;
    if (wslay_event_want_write(ctx))
      event.events |= POLLOUT;
  }
  return(res);
} /* communicate */

/*
 * Serves echo back service forever.  *sfd* is the file descriptor of
 * the server socket.  when the incoming connection from the client is
 * accepted, this function forks another process and the forked
 * process communicates with client. The parent process goes back to
 * the loop and can accept another client.
 */
static void __attribute__((noreturn)) serve(int sfd) {
  while (1) {
    int fd;
    while ((fd = accept(sfd, NULL, NULL)) == -1 && errno == EINTR) {
    }
    if (fd == -1)
      perror("accept");
    else {
      int r = fork();
      if (r == -1) {
        perror("fork");
        close(fd);
      } else if (r == 0) {
        r = communicate(fd);
        shutdown(fd, SHUT_WR);
        close(fd);
        if (r == 0)
          exit(EXIT_SUCCESS);
        else
          exit(EXIT_FAILURE);
      }
    }
  }
}

int wslay_main(int argc, char **argv) {
  struct sigaction act;
  int              sfd;

  if (argc < 2) {
    fprintf(stderr, "Usage: %s PORT\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  memset(&act, 0, sizeof(struct sigaction));
  act.sa_handler = SIG_IGN;
  sigaction(SIGPIPE, &act, NULL);
  sigaction(SIGCHLD, &act, NULL);

  sfd = create_listen_socket(argv[1]);
  if (sfd == -1) {
    fprintf(stderr, "Failed to create server socket\n");
    exit(EXIT_FAILURE);
  }
  printf("WebSocket echo server, listening on %s\n", argv[1]);
  serve(sfd);
  return(EXIT_SUCCESS);
}

TEST t_wslay_test2(){
  PASS();
}

TEST t_wslay_test1(){
  PASS();
}

SUITE(s_wslay_test) {
  RUN_TEST(t_wslay_test1);
  if (isatty(STDOUT_FILENO))
    RUN_TEST(t_wslay_test2);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
  return(wslay_main(argc, argv));

  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_wslay_test);
  GREATEST_MAIN_END();
}
