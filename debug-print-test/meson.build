debug_print_test_srcs = [
  'debug-print-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
debug_print_test_include_dirs = [
  '.',
  inc,
]
debug_print_test_deps = [
  c_greatest_dep,
  debug_print_h_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  ansi_codes_dep,
  log_dep,
  timestamp_dep,
]
debug_print_test_c_args = [
]
debug_print_test_link_args = [
]

debug_print_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  debug_print_test_exec = executable('debug-print-test',
     debug_print_test_srcs,
     dependencies: debug_print_test_deps,
     include_directories: debug_print_test_include_dirs,
     link_args: debug_print_test_link_args,
     c_args: debug_print_test_c_args,
     install: false,
  )
  test('debug-print-test', 
    debug_print_test_exec, args: ['-v','-a'],
    workdir: debug_print_test_test_dir,
  )
endif
