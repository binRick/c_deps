minmax_srcs = [files(
  '../../../submodules/minmax/include/minmax.h',
)]

minmax_dirs = [
  '../../../submodules/minmax',
  '../../../submodules/minmax/include',
  inc,
]

minmax_deps = [

]

minmax_lib = shared_library('minmax',
  minmax_srcs,
  install: false,
  dependencies: minmax_deps,
  include_directories: minmax_dirs,
)

minmax_dep = declare_dependency(
  include_directories: minmax_dirs,
  link_with: minmax_lib,
)
