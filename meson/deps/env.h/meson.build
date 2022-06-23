env_h_srcs = [files(
  '../../../submodules/env.h/env.h',
)]

env_h_dirs = [
  '../../../submodules/env.h',
  inc,
]

env_h_deps = [

]

env_h_lib = shared_library('env.h',
  env_h_srcs,
  install: false,
  dependencies: env_h_deps,
  include_directories: env_h_dirs,
)

env_h_dep = declare_dependency(
  include_directories: env_h_dirs,
  link_with: env_h_lib,
)
