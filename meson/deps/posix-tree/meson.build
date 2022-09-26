posix_tree_srcs = [files(
  '../../../submodules/posix-tree/posix-tree.c',
)]

posix_tree_dirs = [
  '../../../submodules/posix-tree',
  '../../../submodules/posix-tree/screens',
  inc,
]

posix_tree_deps = [

]

posix_tree_lib =library('posix-tree',
  posix_tree_srcs,
  install: false,
  dependencies: posix_tree_deps,
  include_directories: posix_tree_dirs,
)

posix_tree_dep = declare_dependency(
  include_directories: posix_tree_dirs,
  link_with: posix_tree_lib,
)
