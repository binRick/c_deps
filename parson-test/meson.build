parson_test_srcs = [
  'parson-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
parson_test_include_dirs = [
  '.',
  inc,
]
parson_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  parson_dep,
  ansi_codes_dep,
  log_dep,
  timestamp_dep,
]
parson_test_c_args = [
]
parson_test_link_args = [
]

parson_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  parson_test_exec = executable('parson-test',
     parson_test_srcs,
     dependencies: parson_test_deps,
     include_directories: parson_test_include_dirs,
     link_args: parson_test_link_args,
     c_args: parson_test_c_args,
     install: false,
  )
  test('parson-test', 
    parson_test_exec, args: ['-v','-a'],
    workdir: parson_test_test_dir,
  )
endif
