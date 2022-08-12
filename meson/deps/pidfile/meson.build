pidfile_srcs = [files(
  '../../../submodules/pidfile/pidfile.c',
  '../../../submodules/pidfile/pidfile.h',
)]

pidfile_dirs = [
  '../../../submodules/pidfile',
  inc,
]

pidfile_deps = [

]

pidfile_lib = library('pidfile',
  pidfile_srcs,
  install: false,
  dependencies: pidfile_deps,
  include_directories: pidfile_dirs,
)

pidfile_dep = declare_dependency(
  include_directories: pidfile_dirs,
  link_with: pidfile_lib,
)
