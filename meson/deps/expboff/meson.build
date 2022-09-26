expboff_srcs = [files(
  '../../../submodules/expboff/expboff.c',
)]

expboff_dirs = [
  '../../../submodules/expboff',
  '../../../submodules/expboff/doc',
  inc,
]

expboff_deps = [

]

expboff_lib =library('expboff',
  expboff_srcs,
  install: false,
  dependencies: expboff_deps,
  include_directories: expboff_dirs,
)

expboff_dep = declare_dependency(
  include_directories: expboff_dirs,
  link_with: expboff_lib,
)
