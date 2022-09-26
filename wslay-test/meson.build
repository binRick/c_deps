wslay_test_srcs = [
  'wslay-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
wslay_test_include_dirs = [
  '.',
  inc,
]
wslay_test_deps = [
  wslay_dep,
  c_greatest_dep,
  nettle_dep,
  ansi_codes_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  c_string_buffer_dep,
  timestamp_dep,
  log_dep,
  ms_dep,
  bytes_dep,
]
wslay_test_c_args = [
]
wslay_test_link_args = [
]

wslay_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  wslay_test_exec = executable('wslay-test',
     wslay_test_srcs,
     dependencies: wslay_test_deps,
     include_directories: wslay_test_include_dirs,
     link_args: wslay_test_link_args,
     c_args: wslay_test_c_args,
     install: false,
  )
  #  test('wslay-test', 
  #  wslay_test_exec, args: ['-v','-a'],
  #  workdir: wslay_test_test_dir,
  #)
endif
