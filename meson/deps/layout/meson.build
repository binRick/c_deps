layout_srcs = [files(
  '../../../submodules/layout/layout.h',
)]

layout_dirs = [
  '../../../submodules/layout',
  inc,
]

layout_deps = [

]

layout_lib = shared_library('layout',
  layout_srcs,
  install: false,
  dependencies: layout_deps,
  include_directories: layout_dirs,
)

layout_dep = declare_dependency(
  include_directories: layout_dirs,
  link_with: layout_lib,
)
