libforks_srcs = [files(
  '../../../submodules/libforks/libforks.c',
  '../../../submodules/libforks/libforks.h',
)]

libforks_dirs = [
  '../../../submodules/libforks',
  inc,
]

libforks_deps = [

]

libforks_lib = shared_library('libforks',
  libforks_srcs,
  install: false,
  dependencies: libforks_deps,
  include_directories: libforks_dirs,
)

libforks_dep = declare_dependency(
  include_directories: libforks_dirs,
  link_with: libforks_lib,
)
