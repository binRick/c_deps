path_module_srcs = [files(
  '../../../submodules/path_module/src/path.c',
)]

path_module_dirs = [
  '../../../submodules/path_module',
  '../../../submodules/path_module/src',
  inc,
]

path_module_deps = [

]

path_module_lib =library('path_module',
  path_module_srcs,
  install: false,
  dependencies: path_module_deps,
  include_directories: path_module_dirs,
)

path_module_dep = declare_dependency(
  include_directories: path_module_dirs,
  link_with: path_module_lib,
)
