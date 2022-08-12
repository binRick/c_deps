panic_srcs = [files(
  '../../../submodules/panic/sources/panic.c',
)]

panic_dirs = [
  '../../../submodules/panic',
  '../../../submodules/panic/sources',
  inc,
]

panic_deps = [

]

panic_lib = library('panic',
  panic_srcs,
  install: false,
  dependencies: panic_deps,
  include_directories: panic_dirs,
)

panic_dep = declare_dependency(
  include_directories: panic_dirs,
  link_with: panic_lib,
)
