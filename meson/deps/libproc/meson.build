libproc_system_headers = [

]
libproc_local_headers = [
  'libproc/cmd.h',
  'libproc/config.h',
  'libproc/critical.h',
  'libproc/debug.h',
  'libproc/docs/cmd-pkt.h',
  'libproc/eventTimer.h',
  'libproc/events.h',
  'libproc/hashtable.h',
  'libproc/ipc.h',
  'libproc/json.h',
  'libproc/md5.h',
  'libproc/plugin.h',
  'libproc/polysat.h',
  'libproc/priorityQueue.h',
  'libproc/proclib.h',
  'libproc/proctest.h',
  'libproc/pseudo_threads.h',
  'libproc/telm_dict.h',
  'libproc/tests/plugin/cube.h',
  'libproc/util.h',
  'libproc/watchdog_cmd.h',
  'libproc/xdr-saved.h',
  'libproc/xdr.h',
  'libproc/zmqlite.h',
]
libproc_srcs = [
  '../../../submodules/libproc/cmd.c',
  '../../../submodules/libproc/config.c',
  '../../../submodules/libproc/critical.c',
  '../../../submodules/libproc/debug.c',
  '../../../submodules/libproc/eventTimer.c',
  '../../../submodules/libproc/events.c',
  '../../../submodules/libproc/globalTimer.c',
  '../../../submodules/libproc/hashtable.c',
  '../../../submodules/libproc/ipc.c',
  '../../../submodules/libproc/json.c',
  '../../../submodules/libproc/md5.c',
  '../../../submodules/libproc/plugin.c',
  '../../../submodules/libproc/priorityQueue.c',
  '../../../submodules/libproc/proclib.c',
  '../../../submodules/libproc/pseudo_threads.c',
  '../../../submodules/libproc/telm_dict.c',
  '../../../submodules/libproc/util.c',
  '../../../submodules/libproc/xdr.c',
  '../../../submodules/libproc/zmqlite.c',
]

libproc_dirs = [
  '../../../submodules/libproc',
  '../../../submodules/libproc/docs',
  inc,
]

libproc_c_args = [
]

libproc_deps = [

]

if libproc_srcs.length() > 0
  libproc_lib =library('libproc',
    files(libproc_srcs),
    install: false,
    dependencies: libproc_deps,
    include_directories: libproc_dirs,
    c_args: libproc_c_args,
  )
  libproc_links = [libproc_lib]
else
  libproc_links = []
endif

libproc_dep = declare_dependency(
  include_directories: libproc_dirs,
  link_with: libproc_links,
)
