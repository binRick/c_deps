generic_print_lib = library('generic_print', 
pwd + '/submodules/generic-print/print.h',
install: false, dependencies: [
  asprintf_dep,
  ], 
  include_directories: [
    inc,
  ]
)
generic_print_dep = declare_dependency(include_directories: [
  inc,
  ], link_with: generic_print_lib)
