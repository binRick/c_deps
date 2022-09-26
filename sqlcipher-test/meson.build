sqlcipher_test_srcs = [
  'sqlcipher-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
sqlcipher_test_include_dirs = [
  '.',
  inc,
]
sqlcipher_test_deps = [
  c_greatest_dep,
  ansi_codes_dep,
  c_vector_dep,
  sqlcipher_dep,
  c_fsio_dep,
  c_stringfn_dep,
  c_string_buffer_dep,
  timestamp_dep,
  log_dep,
  ms_dep,
  bytes_dep,
]
sqlcipher_test_c_args = [
]
sqlcipher_test_link_args = [
]

sqlcipher_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  sqlcipher_test_exec = executable('sqlcipher-test',
     sqlcipher_test_srcs,
     dependencies: sqlcipher_test_deps,
     include_directories: sqlcipher_test_include_dirs,
     link_args: sqlcipher_test_link_args,
     c_args: sqlcipher_test_c_args,
     install: false,
  )
  test('sqlcipher-test', 
    sqlcipher_test_exec, args: ['-v','-a'],
    workdir: sqlcipher_test_test_dir,
  )
endif
