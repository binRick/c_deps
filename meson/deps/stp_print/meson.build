stp_print_srcs = [files(
  '../../../submodules/stp_print/stp_print.c',
)]

stp_print_dirs = [
  '../../../submodules/stp_print',
  inc,
]

stp_print_deps = [

]

stp_print_lib =library('stp_print',
  stp_print_srcs,
  install: false,
  dependencies: stp_print_deps,
  include_directories: stp_print_dirs,
)

stp_print_dep = declare_dependency(
  include_directories: stp_print_dirs,
  link_with: stp_print_lib,
)
