querystring_test_srcs = [
  'querystring-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
querystring_test_include_dirs = [
  '.',
  inc,
]
querystring_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  c_fsio_dep,
  querystring_c_dep,
  c_stringfn_dep,
  ansi_codes_dep,
  logh_dep,
  timestamp_dep,
]
querystring_test_c_args = [
]
querystring_test_link_args = [
]

querystring_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  querystring_test_exec = executable('querystring-test',
     querystring_test_srcs,
     dependencies: querystring_test_deps,
     include_directories: querystring_test_include_dirs,
     link_args: querystring_test_link_args,
     c_args: querystring_test_c_args,
     install: false,
  )
  test('querystring-test', 
    querystring_test_exec, args: ['-v','-a'],
    workdir: querystring_test_test_dir,
  )
endif
