flingfd_srcs = [files(
  '../../../submodules/flingfd/src/flingfd.c',
)]

flingfd_dirs = [
  '../../../submodules/flingfd',
  '../../../submodules/flingfd/src',
  inc,
]

flingfd_deps = [

]

flingfd_lib = static_library('flingfd',
  flingfd_srcs,
  install: false,
  dependencies: flingfd_deps,
  include_directories: flingfd_dirs,
)

flingfd_dep = declare_dependency(
  include_directories: flingfd_dirs,
  link_with: flingfd_lib,
)
