
debug_print_h_lib = static_library('debug_print_h', 
  '../../../submodules/debug_print_h/src/debug_print.c',
  install: false, dependencies: [
   asprintf_dep,
   ansi_codes_dep,
  ], 
  include_directories: [
    inc,
  ]
)

debug_print_h_dep = declare_dependency(
  include_directories: [
    inc,
  ], 
  link_with: debug_print_h_lib,
)
