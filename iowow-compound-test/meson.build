iowow_compound_test_srcs = [
  'iowow-compound-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
iowow_compound_test_include_dirs = [
  '.',
  inc,
]
iowow_compound_test_deps = [
  c_greatest_dep,
  ansi_codes_dep,
  iowow_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  c_string_buffer_dep,
  timestamp_dep,
  log_dep,
  ms_dep,
  bytes_dep,
]
iowow_compound_test_c_args = [
]
iowow_compound_test_link_args = [
]

iowow_compound_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  iowow_compound_test_exec = executable('iowow-compound-test',
     iowow_compound_test_srcs,
     dependencies: iowow_compound_test_deps,
     include_directories: iowow_compound_test_include_dirs,
     link_args: iowow_compound_test_link_args,
     c_args: iowow_compound_test_c_args,
     install: false,
  )
  #test('iowow-compound-test', 
  #  iowow_compound_test_exec, args: ['-v','-a'],
  #  workdir: iowow_compound_test_test_dir,
  #)
endif
