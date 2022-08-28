optparse99_srcs = [files(
  '../../../submodules/optparse99/optparse99.c',
)]

optparse99_dirs = [
  '../../../submodules/optparse99',
  inc,
]

optparse99_deps = [

]

optparse99_lib = static_library('optparse99',
  optparse99_srcs,
  install: false,
  dependencies: optparse99_deps,
  include_directories: optparse99_dirs,
)

optparse99_dep = declare_dependency(
  include_directories: optparse99_dirs,
  link_with: optparse99_lib,
)
