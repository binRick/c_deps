libdefer_srcs = [files(
  '../../../submodules/libdefer/defer.c',
)]

libdefer_dirs = [
  '../../../submodules/libdefer',
  '../../../submodules/libdefer/include',
  inc,
]

libdefer_deps = [

]

libdefer_lib = static_library('libdefer',
  libdefer_srcs,
  install: false,
  dependencies: libdefer_deps,
  include_directories: libdefer_dirs,
)

libdefer_dep = declare_dependency(
  include_directories: libdefer_dirs,
  link_with: libdefer_lib,
)
