////////////////////////////////////////////

////////////////////////////////////////////
#include "msgbox-test/msgbox-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "bytes/bytes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "log/log.h"
#include "ms/ms.h"
#include "msgbox/msgbox/msgbox.h"
#include "timestamp/timestamp.h"
static volatile size_t svr_recv_msgs = 0;
static volatile size_t cl_recv_msgs = 0;
int                    LISTEN_PORT = 49119;
char                   *LISTEN_HOST = "127.0.0.1";
const char             *TCP_SERVICE, *UDP_SERVICE;
void __attribute__((constructor)) __constructor__msgbox_test(){
  if (getenv("PORT") != NULL) {
    LISTEN_PORT = atoi(getenv("PORT"));
  }
  if (getenv("HOST") != NULL) {
    LISTEN_HOST = getenv("HOST");
  }
  asprintf(&TCP_SERVICE, "tcp://%s:%d", LISTEN_HOST, LISTEN_PORT);
  asprintf(&UDP_SERVICE, "udp://%s:%d", LISTEN_HOST, LISTEN_PORT);
  log_debug("UDP Service: %s", UDP_SERVICE);
  log_debug("TCP Service: %s", TCP_SERVICE);
}

void msg_update_server(msg_Conn *conn, msg_Event event, msg_Data data) {
  if (event == msg_request) {
    msg_send(conn, data);
    svr_recv_msgs++;
  }
}

void msg_update_client(msg_Conn *conn, msg_Event event, msg_Data data) {
  if (event == msg_connection_ready) {
    msg_Data data = msg_new_data("hello!");
    msg_get(conn, data, msg_no_context);
    msg_delete_data(data);
  }
  if (event == msg_reply) {
    printf("Got the reply: '%s'.\n", msg_as_str(data));
    cl_recv_msgs++;
  }
}

TEST t_msgbox_tcp_client(void){
  msg_connect(TCP_SERVICE, msg_update_client, msg_no_context);
  while (cl_recv_msgs < 1) {
    msg_runloop(10);
  }
  ASSERT_GTE(cl_recv_msgs, 1);
  char *msg;
  asprintf(&msg, "Receieved %lu messages on client", cl_recv_msgs);
  PASSm(msg);
}

TEST t_msgbox_udp_client(void){
  msg_connect(UDP_SERVICE, msg_update_client, msg_no_context);
  while (cl_recv_msgs < 1) {
    msg_runloop(10);
  }
  ASSERT_GTE(cl_recv_msgs, 1);
  char *msg;
  asprintf(&msg, "Receieved %lu messages on client", cl_recv_msgs);
  PASSm(msg);
}

TEST t_msgbox_tcp_server(void){
  msg_listen(TCP_SERVICE, msg_update_server);
  while (svr_recv_msgs < 1) {
    msg_runloop(10);
  }
  ASSERT_GTE(svr_recv_msgs, 1);
  char *msg;
  asprintf(&msg, "Receieved %lu messages on server", svr_recv_msgs);
  PASSm(msg);
}

TEST t_msgbox_udp_server(void){
  msg_listen(UDP_SERVICE, msg_update_server);
  while (svr_recv_msgs < 1) {
    msg_runloop(10);
  }
  ASSERT_GTE(svr_recv_msgs, 1);
  char *msg;
  asprintf(&msg, "Receieved %lu messages on server", svr_recv_msgs);
  PASSm(msg);
}

SUITE(s_msgbox_test_udp_server) {
  RUN_TEST(t_msgbox_udp_server);
}
SUITE(s_msgbox_test_udp_client) {
  RUN_TEST(t_msgbox_udp_client);
}
SUITE(s_msgbox_test_tcp_server) {
  RUN_TEST(t_msgbox_tcp_server);
}
SUITE(s_msgbox_test_tcp_client) {
  RUN_TEST(t_msgbox_tcp_client);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  if (isatty(STDOUT_FILENO)) {
    RUN_SUITE(s_msgbox_test_tcp_server);
    RUN_SUITE(s_msgbox_test_tcp_client);
    RUN_SUITE(s_msgbox_test_udp_server);
    RUN_SUITE(s_msgbox_test_udp_client);
  }
  GREATEST_MAIN_END();
}
