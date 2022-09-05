libmonitors_srcs = [files(
  '../../../submodules/c_libmonitors/src/monitors-darwin.c',
  '../../../submodules/c_libmonitors/src/monitors-internal.c',
)]

libmonitors_dirs = [
  '../../../submodules/c_libmonitors',
  '../../../submodules/c_libmonitors/src',
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
