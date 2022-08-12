subhook_srcs = [files(
  '../../../submodules/subhook/subhook.c',
  '../../../submodules/subhook/subhook.h',
)]

subhook_dirs = [
  '../../../submodules/subhook',
  inc,
]

subhook_deps = [

]

subhook_lib = library('subhook',
  subhook_srcs,
  install: false,
  dependencies: subhook_deps,
  include_directories: subhook_dirs,
)

subhook_dep = declare_dependency(
  include_directories: subhook_dirs,
  link_with: subhook_lib,
)
