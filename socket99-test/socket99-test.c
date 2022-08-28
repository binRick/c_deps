////////////////////////////////////////////

////////////////////////////////////////////
#include "socket99-test/socket99-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "socket99/socket99.h"
#include "timestamp/timestamp.h"
int port = 29332;

////////////////////////////////////////////
void do_socket99_tcp_server(void *PARAM){
  int             v_true = 1;
  socket99_config cfg    = {
    .host        = "127.0.0.1",
    .port        = port,
    .server      = true,
    .nonblocking = true,
    .sockopts    = {
      { SO_REUSEADDR, &v_true, sizeof(v_true) },
    },
  };

  socket99_result res;
  bool            ok = socket99_open(&cfg, &res);

  if (!ok) {
    char buf[128];
    if (128 < socket99_snprintf(buf, 128, &res)) {
      socket99_fprintf(stderr, &res);
    } else {
      fprintf(stderr, "%s\n", buf);
    }
    FAIL();
  }

  struct pollfd fds[2];

  fds[0].fd     = res.fd;
  fds[0].events = POLLIN;

  ssize_t received  = 0;
  nfds_t  poll_fds  = 1;
  int     client_fd = -1;

  for ( ;;) {
    int poll_res = poll(fds, poll_fds, 1000 /* msec */);
    if (poll_res > 0) {
      if (fds[0].revents & POLLIN) {
        struct sockaddr address;
        socklen_t       addr_len;
        client_fd = accept(res.fd, &address, &addr_len);
        if (client_fd == -1) {
          if (errno == EAGAIN) {
            errno = 0;
            continue;
          } else {
            break;
          }
        } else {
          fds[1].fd     = client_fd;
          fds[1].events = POLLIN;
          poll_fds++;
        }
      } else if (fds[0].revents & POLLERR || fds[0].revents & POLLHUP) {
        printf("POLLERR / POLLHUP\n");
        break;
      }

      if (poll_fds > 1) {
        if (fds[1].revents & POLLIN) {
          char buf[1024];
          received = recv(fds[1].fd, buf, 1024, 0);

          if (received > 0) {
            buf[received] = '\0';
            printf("Got: '%s'\n", buf);
            close(client_fd);
          } else {
            if (errno == EAGAIN) {
              errno = 0;
            } else {
              fprintf(stderr, "recv: %s\n", strerror(errno));
              close(client_fd);
            }
          }

          if (received > 0) {
            break;
          }
        } else if (fds[1].revents & POLLERR || fds[1].revents & POLLHUP) {
          printf("POLLERR / POLLHUP\n");
          close(client_fd);
          break;
        }
      }
    }
  }

  close(res.fd);
}   /* do_socket99_tcp_server */

TEST t_socket99_tcp_client(void){
  socket99_config cfg = {
    .host = "127.0.0.1",
    .port = port,
  };

  socket99_result res;
  bool            ok = socket99_open(&cfg, &res);

  if (!ok) {
    socket99_fprintf(stderr, &res);
    return(false);
  }

  const char *msg     = "hello\n";
  size_t     msg_size = strlen(msg);

  ssize_t    sent = send(res.fd, msg, msg_size, 0);
  bool       pass = ((size_t)sent == msg_size);

  close(res.fd);
  PASS();
}

TEST t_socket99_test(){
  PASS();
}

SUITE(s_socket99_test) {
  RUN_TEST(t_socket99_test);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_socket99_test);
  GREATEST_MAIN_END();
}
