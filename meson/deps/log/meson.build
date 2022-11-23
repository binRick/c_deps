log_srcs = [files(
  '../../../submodules/log/log-print.c',
)]

log_dirs = [
  '../../../submodules/log',
  inc,
]

log_deps = [
]

log_lib_static =static_library('log',
  log_srcs,
  install: false,
  dependencies: log_deps,
  include_directories: log_dirs,
)

log_lib =shared_library('log',
  log_srcs,
  install: false,
  dependencies: log_deps,
  include_directories: log_dirs,
)

log_dep = declare_dependency(
  include_directories: log_dirs,
  link_with: [log_lib],
)
