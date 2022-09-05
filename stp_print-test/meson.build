stp_print_test_srcs = [
  'stp_print-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
stp_print_test_include_dirs = [
  '.',
  inc,
]
stp_print_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  stp_print_dep,
  ansi_codes_dep,
  log_dep,
  timestamp_dep,
]
stp_print_test_c_args = [
]
stp_print_test_link_args = [
]

stp_print_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  stp_print_test_exec = executable('stp_print-test',
     stp_print_test_srcs,
     dependencies: stp_print_test_deps,
     include_directories: stp_print_test_include_dirs,
     link_args: stp_print_test_link_args,
     c_args: stp_print_test_c_args,
     install: false,
  )
  test('stp_print-test', 
    stp_print_test_exec, args: ['-v','-a'],
    workdir: stp_print_test_test_dir,
  )
endif
