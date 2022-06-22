
generic_print_srcs = [
  # '../../../submodules/generic-print/print.h',

]

generic_print_inc = [
  '../../../submodules/generic-print',
  inc,
]

generic_print_lib = library('generic_print', 
  generic_print_srcs,
  install: false, 
  dependencies: [
    asprintf_dep,
  ], 
  include_directories: generic_print_inc,
)
generic_print_dep = declare_dependency(
 include_directories: generic_print_inc,
 link_with: generic_print_lib,
 )
