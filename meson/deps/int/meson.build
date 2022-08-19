int_srcs = [files(
  '../../../submodules/int/int.c',
  '../../../submodules/int/int.h',
)]

int_dirs = [
  '../../../submodules/int',
  inc,
]

int_deps = [

]

int_lib = static_library('int',
  int_srcs,
  install: false,
  dependencies: int_deps,
  include_directories: int_dirs,
)

int_dep = declare_dependency(
  include_directories: int_dirs,
  link_with: int_lib,
)
