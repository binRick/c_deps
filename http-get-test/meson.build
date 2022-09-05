http_get_test_srcs = [
  'http-get-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
http_get_test_include_dirs = [
  '.',
  inc,
]
http_get_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  c_fsio_dep,
  http_get_dep,
  c_stringfn_dep,
  ansi_codes_dep,
  log_dep,
  timestamp_dep,
]
http_get_test_c_args = [
]
http_get_test_link_args = [
]

http_get_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  http_get_test_exec = executable('http-get-test',
     http_get_test_srcs,
     dependencies: http_get_test_deps,
     include_directories: http_get_test_include_dirs,
     link_args: http_get_test_link_args,
     c_args: http_get_test_c_args,
     install: false,
  )
  test('http-get-test', 
    http_get_test_exec, args: ['-v','-a'],
    workdir: http_get_test_test_dir,
  )
endif
