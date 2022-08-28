librnd_srcs = [files(
  '../../../submodules/librnd/rnd.c',
)]

librnd_dirs = [
  '../../../submodules/librnd',
  inc,
]

librnd_deps = [

]

librnd_lib = static_library('librnd',
  librnd_srcs,
  install: false,
  dependencies: librnd_deps,
  include_directories: librnd_dirs,
)

librnd_dep = declare_dependency(
  include_directories: librnd_dirs,
  link_with: librnd_lib,
)
