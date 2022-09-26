wcwidth_srcs = [files(
  '../../../submodules/wcwidth/wcwidth.c',
)]

wcwidth_dirs = [
  '../../../submodules/wcwidth',
  inc,
]

wcwidth_deps = [

]

wcwidth_lib =library('wcwidth',
  wcwidth_srcs,
  install: false,
  dependencies: wcwidth_deps,
  c_args: [
      '-Wno-implicit-function-declaration',
    ],
  include_directories: wcwidth_dirs,
)

wcwidth_dep = declare_dependency(
  include_directories: wcwidth_dirs,
  link_with: wcwidth_lib,
)
