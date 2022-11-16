match_test_srcs = [
  'match-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
match_test_include_dirs = [
  '.',
  inc,
]
match_test_deps = [
  c_greatest_dep,
  ansi_codes_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  c_string_buffer_dep,
  timestamp_dep,
  log_dep,
  ms_dep,
  bytes_dep,
  match_dep,
]
match_test_c_args = [
]
match_test_link_args = [
]

match_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  match_test_exec = executable('match-test',
     match_test_srcs,
     dependencies: match_test_deps,
     include_directories: match_test_include_dirs,
     link_args: match_test_link_args,
     c_args: match_test_c_args,
     install: false,
  )
  #test('match-test', 
  #  match_test_exec, args: ['-v','-a'],
  #  workdir: match_test_test_dir,
  #)
endif
