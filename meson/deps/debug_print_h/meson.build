debug_print_h_lib = library('debug_print_h', 
  pwd+'/submodules/debug_print_h/debug_print.h',
  install: false, dependencies: [
   asprintf_dep,
  ], 
  include_directories: [
    inc,
  ]
)
debug_print_h_dep = declare_dependency(include_directories: [
  inc,
  ], link_with: debug_print_h_lib)
