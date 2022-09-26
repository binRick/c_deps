hexify_c_srcs = [files(
  '../../../submodules/hexify_c/hexify.c',
)]

hexify_c_dirs = [
  '../../../submodules/hexify_c',
  inc,
]

hexify_c_deps = [

]

hexify_c_lib =library('hexify_c',
  hexify_c_srcs,
  install: false,
  dependencies: hexify_c_deps,
  include_directories: hexify_c_dirs,
)

hexify_c_dep = declare_dependency(
  include_directories: hexify_c_dirs,
  link_with: hexify_c_lib,
)
