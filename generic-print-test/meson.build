generic_print_test_srcs = [
  'generic-print-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
generic_print_test_include_dirs = [
  '.',
  inc,
]
generic_print_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  generic_print_dep,
  c_fsio_dep,
  c_stringfn_dep,
  ansi_codes_dep,
  logh_dep,
  timestamp_dep,
]
generic_print_test_c_args = [
]
generic_print_test_link_args = [
]

generic_print_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  generic_print_test_exec = executable('generic-print-test',
     generic_print_test_srcs,
     dependencies: generic_print_test_deps,
     include_directories: generic_print_test_include_dirs,
     link_args: generic_print_test_link_args,
     c_args: generic_print_test_c_args,
     install: false,
  )
  test('generic-print-test', 
    generic_print_test_exec, args: ['-v','-a'],
    workdir: generic_print_test_test_dir,
  )
endif
