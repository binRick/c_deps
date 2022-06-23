socket99_srcs = [files(
  '../../../submodules/socket99/socket99.c',
  '../../../submodules/socket99/socket99.h',
)]

socket99_dirs = [
  '../../../submodules/socket99',
  inc,
]

socket99_deps = [

]

socket99_lib = shared_library('socket99',
  socket99_srcs,
  install: false,
  dependencies: socket99_deps,
  include_directories: socket99_dirs,
)

socket99_dep = declare_dependency(
  include_directories: socket99_dirs,
  link_with: socket99_lib,
)
