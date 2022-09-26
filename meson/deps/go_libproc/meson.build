go_libproc_srcs = [files(
  '../../../submodules/go_libproc/golibproc.c',
)]

go_libproc_dirs = [
  '../../../submodules/go_libproc',
  inc,
]

go_libproc_deps = [

]

go_libproc_lib =library('go_libproc',
  go_libproc_srcs,
  install: false,
  dependencies: go_libproc_deps,
  include_directories: go_libproc_dirs,
)

go_libproc_dep = declare_dependency(
  include_directories: go_libproc_dirs,
  link_with: go_libproc_lib,
)
