libmonitors_srcs = [files(
  '../../../submodules/libmonitors/src/monitors-darwin.c',
  '../../../submodules/libmonitors/src/monitors-internal.c',
  '../../../submodules/libmonitors/src/monitors-linux.c',
)]

libmonitors_dirs = [
  '../../../submodules/libmonitors',
  '../../../submodules/libmonitors/src',
  inc,
]

libmonitors_deps = [

]

libmonitors_lib = static_library('libmonitors',
  libmonitors_srcs,
  install: false,
  dependencies: libmonitors_deps,
  include_directories: libmonitors_dirs,
)

libmonitors_dep = declare_dependency(
  include_directories: libmonitors_dirs,
  link_with: libmonitors_lib,
)
