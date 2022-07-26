clamp_srcs = [files(
  '../../../submodules/clamp/clamp.h',
)]

clamp_dirs = [
  '../../../submodules/clamp',
  inc,
]

clamp_deps = [

]

clamp_lib = shared_library('clamp',
  clamp_srcs,
  install: false,
  dependencies: clamp_deps,
  include_directories: clamp_dirs,
)

clamp_dep = declare_dependency(
  include_directories: clamp_dirs,
  link_with: clamp_lib,
)
