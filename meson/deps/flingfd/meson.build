flingfd_srcs = [files(
  '../../../submodules/flingfd/src/flingfd.c',
  '../../../submodules/flingfd/src/flingfd.h',
)]

flingfd_dirs = [
  '../../../submodules/flingfd',
  '../../../submodules/flingfd/src',
  inc,
]

flingfd_deps = [

]

flingfd_lib = shared_library('flingfd',
  flingfd_srcs,
  install: false,
  dependencies: flingfd_deps,
  include_directories: flingfd_dirs,
)

flingfd_dep = declare_dependency(
  include_directories: flingfd_dirs,
  link_with: flingfd_lib,
)
