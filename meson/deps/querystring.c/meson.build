querystring_c_srcs = [files(
  '../../../submodules/querystring.c/querystring.c',
  '../../../submodules/querystring.c/querystring.h',
)]

querystring_c_dirs = [
  '../../../submodules/querystring.c',
  inc,
]

querystring_c_deps = [

]

querystring_c_lib = both_libraries('querystring.c',
  querystring_c_srcs,
  install: false,
  dependencies: querystring_c_deps,
  include_directories: querystring_c_dirs,
)

querystring_c_dep = declare_dependency(
  include_directories: querystring_c_dirs,
  link_with: querystring_c_lib,
)
