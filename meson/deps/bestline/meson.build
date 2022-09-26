bestline_srcs = [files(
  '../../../submodules/bestline/bestline.c',
  '../../../submodules/bestline/bestline.h',
)]

bestline_dirs = [
  '../../../submodules/bestline',
  inc,
]

bestline_deps = [

]

bestline_lib =library('bestline',
  bestline_srcs,
  install: false,
  dependencies: bestline_deps,
  include_directories: bestline_dirs,
)

bestline_dep = declare_dependency(
  include_directories: bestline_dirs,
  link_with: bestline_lib,
)
