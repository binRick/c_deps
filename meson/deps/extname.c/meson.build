
extname_c_dirs = [
  '../../../submodules/extname.c',
  inc,
]

extname_c_deps = [

]



extname_c_srcs = [files(
  '../../../submodules/extname.c/src/extname.c',
)]

extname_c_lib = both_libraries('extname-c',
  extname_c_srcs,
  install: false,
  dependencies: extname_c_deps,
  include_directories: extname_c_dirs,
)

extname_c_dep = declare_dependency(
  include_directories: extname_c_dirs,
  link_with: extname_c_lib,
)
