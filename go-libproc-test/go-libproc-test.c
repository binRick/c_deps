////////////////////////////////////////////
#include <errno.h>
#include <mach/mach.h>
#include <mach/mach_host.h>
#include <mach/mach_init.h>
#include <mach/mach_types.h>
#include <mach/vm_statistics.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/_types.h>
#include <sys/appleapiopts.h>
#include <sys/cdefs.h>
#include <sys/resource.h>
#include <sys/sysctl.h>
#include <sys/time.h>

////////////////////////////////////////////
#include "go-libproc-test/go-libproc-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "go_libproc/_reference/proc_info.h"
#include "go_libproc/golibproc.h"
#include "log.h/log.h"
#include "timestamp/timestamp.h"

////////////////////////////////////////////
TEST t_go_libproc_test(){
  PASS();
}
#define BUFFER_SIZE    128 * 1024
SUITE(s_go_libproc_test) {
  char buf[32][BUFFER_SIZE];
  int  pid[2] = {
    getpid(), 1
  };
  int  res[32];

  res[0] = name(pid[0], &buf[0], BUFFER_SIZE);
  log_info("name| pid %d: %s> res: %d", pid[0], buf[0], res[0]);

  res[1] = listchildpids(pid[0], &buf[1], BUFFER_SIZE);
  log_info("listchildpids| pid %d: %s> res: %d", pid[0], buf[1], res[1]);
  res[1] = listchildpids(pid[1], &buf[1], BUFFER_SIZE);
  log_info("listchildpids| pid %d: %s> res: %d", pid[1], buf[1], res[1]);

  res[2] = pidpath(pid[0], &buf[2], BUFFER_SIZE);
  log_info("pidpath| pid %d: %s> res: %d", pid[0], buf[2], res[2]);

  res[3] = listallpids(&buf[3], BUFFER_SIZE);
  log_info("listallpids|  %s > res: %d", buf[3], res[3]);

  res[4] = listpgrppids(pid[0], &buf[4], BUFFER_SIZE);
  log_info("listpgrppids| pid %d: %s> res: %d", pid[0], buf[4], res[4]);
  res[4] = listpgrppids(pid[1], &buf[4], BUFFER_SIZE);
  log_info("listpgrppids| pid %d: %s> res: %d", pid[1], buf[4], res[4]);

  vm_size_t              page_size;
  mach_port_t            mach_port;
  mach_msg_type_number_t count;
  vm_statistics64_data_t vm_stats;

  mach_port = mach_host_self();
  count     = sizeof(vm_stats) / sizeof(natural_t);
  if (KERN_SUCCESS == host_page_size(mach_port, &page_size)
      && KERN_SUCCESS == host_statistics64(mach_port, HOST_VM_INFO,
                                           (host_info64_t)&vm_stats, &count)) {
    long long free_memory = (int64_t)vm_stats.free_count * (int64_t)page_size;

    long long used_memory = ((int64_t)vm_stats.active_count +
                             (int64_t)vm_stats.inactive_count +
                             (int64_t)vm_stats.wire_count) * (int64_t)page_size;
    printf("free memory: %lld | used memory: %lld", free_memory, used_memory);
  }

/*
 *
 *
 * struct rusage_info_t usage = { 0 };
 * res[5] = pid_rusage(pid[0], PROC_PID_RUSAGE, &usage);
 * log_info("pid_rusage| pid %d: ru_utime: %ld> res: %d",
 *    pid[0],
 *    usage.ru_utime.tv_sec,
 *    res[4]
 *    );
 *
 */

  struct task_basic_info t_info;
  mach_msg_type_number_t t_info_count = TASK_BASIC_INFO_COUNT;

  if (KERN_SUCCESS != task_info(mach_task_self(),
                                TASK_BASIC_INFO, (task_info_t)&t_info,
                                &t_info_count)) {
    return(-1);
  }

  log_info("task info> t_info.resident_size: %lu", t_info.resident_size);
  log_info("task info> t_info.virtual_size: %lu", t_info.virtual_size);

#include <sys/resource.h>

  struct rusage r_usage;

  if (getrusage(RUSAGE_SELF, &r_usage)) {
    FAIL();
  }

  log_info("Total User CPU = %ld.%d",
           r_usage.ru_utime.tv_sec,
           r_usage.ru_utime.tv_usec);
  log_info("Total System CPU = %ld.%d",
           r_usage.ru_stime.tv_sec,
           r_usage.ru_stime.tv_usec);

  RUN_TEST(t_go_libproc_test);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_go_libproc_test);
  GREATEST_MAIN_END();
}
