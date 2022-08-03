str_flatten_c_srcs = [files(
  '../../../submodules/str-flatten.c/src/str-flatten.c',
)]

str_flatten_c_dirs = [
  '../../../submodules/str-flatten.c',
  '../../../submodules/str-flatten.c/src',
  inc,
]

str_flatten_c_deps = [

]

str_flatten_c_lib = static_library('str-flatten.c',
  str_flatten_c_srcs,
  install: false,
  dependencies: str_flatten_c_deps,
  include_directories: str_flatten_c_dirs,
)

str_flatten_c_dep = declare_dependency(
  include_directories: str_flatten_c_dirs,
  link_with: str_flatten_c_lib,
)
