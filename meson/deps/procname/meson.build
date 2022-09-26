procname_srcs = [files(
  '../../../submodules/procname/src/libprocname.c',
)]

procname_dirs = [
  '../../../submodules/procname',
  '../../../submodules/procname/src',
  inc,
]

procname_deps = [

]

procname_lib =library('procname',
  procname_srcs,
  install: false,
  dependencies: procname_deps,
  include_directories: procname_dirs,
)

procname_dep = declare_dependency(
  include_directories: procname_dirs,
  link_with: procname_lib,
)
