path_normalize_c_srcs = [files(
  '../../../submodules/path-normalize.c/src/path-normalize.c',
  '../../../submodules/path-normalize.c/src/path-normalize.h',
)]

path_normalize_c_dirs = [
  '../../../submodules/path-normalize.c',
  '../../../submodules/path-normalize.c/src',
  inc,
]

path_normalize_c_deps = [

]

path_normalize_c_lib =library('path-normalize.c',
  path_normalize_c_srcs,
  install: false,
  dependencies: path_normalize_c_deps,
  include_directories: path_normalize_c_dirs,
)

path_normalize_c_dep = declare_dependency(
  include_directories: path_normalize_c_dirs,
  link_with: path_normalize_c_lib,
)
