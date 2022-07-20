#include "dbg/dbg.h"
#include "submodules/greatest/greatest.h"
#include "submodules/wireguard-tools/src/containers.h"
#include "wg-test/wg-test.h"
#include "wg/wg.h"
#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>


int main(int argc, char **argv) {
  (void)argc; (void)argv;
  char *interfaces = ipc_list_devices(), *interface;
  int  ret = 0;
  if (!interfaces) {
    perror("Unable to list interfaces");
    return(1);
  }
  ret       = !!*interfaces;
  interface = interfaces;
  for (size_t len = 0; (len = strlen(interface)); interface += len + 1) {
    struct wgdevice *device = NULL;
    if (ipc_get_device(&device, interface) < 0) {
      fprintf(stderr, "Unable to access interface %s: %s\n", interface, strerror(errno));
      continue;
    }
    dbg(interface, %s);
    free_wgdevice(device);
  }

  return(0);
}

