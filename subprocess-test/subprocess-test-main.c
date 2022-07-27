#include "subprocess-test.h"
#define DEBUG_STDOUT               false
#define STDOUT_READ_BUFFER_SIZE    1024 * 16
#include "c_string_buffer/include/stringbuffer.h"


int subprocess_test_main(char *CMD){
  char                 *READ_STDOUT;
  int                  exited, result;
  struct subprocess_s  subprocess;
  const char           *command_line[]                        = { "/bin/sh", "--norc", "--noprofile", "-c", CMD, NULL };
  char                 stdout_buffer[STDOUT_READ_BUFFER_SIZE] = { 0 };
  struct  StringBuffer *SB                                    = stringbuffer_new_with_options(STDOUT_READ_BUFFER_SIZE, true);
  size_t               bytes_read                             = 0,
                       index                                  = 0;

  result = subprocess_create(command_line, 0, &subprocess);
  assert_eq(result, 0, %d);
  do {
    bytes_read = subprocess_read_stdout(&subprocess, stdout_buffer, STDOUT_READ_BUFFER_SIZE - 1);
    stringbuffer_append_string(SB, stdout_buffer);
    index += bytes_read;
  } while (bytes_read != 0);

  result = subprocess_join(&subprocess, &exited);
  assert_eq(result, 0, %d);
  dbg(exited, %d);
  assert_eq(exited, 0, %d);

  READ_STDOUT = stringbuffer_to_string(SB);

  stringbuffer_release(SB);
  dbg(command_line[4], %s);
  dbg(strlen(READ_STDOUT), %lu);
  if (DEBUG_STDOUT) {
    fprintf(stderr, "%s", READ_STDOUT);
  }

  return(0);
}
