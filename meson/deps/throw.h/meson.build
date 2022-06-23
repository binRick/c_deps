throw_h_srcs = [files(
  '../../../submodules/throw.h/throw.h',
)]

throw_h_dirs = [
  '../../../submodules/throw.h',
  inc,
]

throw_h_deps = [

]

throw_h_lib = shared_library('throw.h',
  throw_h_srcs,
  install: false,
  dependencies: throw_h_deps,
  include_directories: throw_h_dirs,
)

throw_h_dep = declare_dependency(
  include_directories: throw_h_dirs,
  link_with: throw_h_lib,
)
