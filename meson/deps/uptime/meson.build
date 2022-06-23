uptime_srcs = [files(
  '../../../submodules/uptime/include/uptime/uptime.h',
  '../../../submodules/uptime/src/uptime.c',
)]

uptime_dirs = [
  '../../../submodules/uptime',
  '../../../submodules/uptime/include',
  '../../../submodules/uptime/include/uptime',
  '../../../submodules/uptime/src',
  inc,
]

uptime_deps = [

]

uptime_lib = shared_library('uptime',
  uptime_srcs,
  install: false,
  dependencies: uptime_deps,
  include_directories: uptime_dirs,
)

uptime_dep = declare_dependency(
  include_directories: uptime_dirs,
  link_with: uptime_lib,
)
