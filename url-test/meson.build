url_test_srcs = [
  'url-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
url_test_include_dirs = [
  '.',
  inc,
]
url_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  url_h_dep,
  ansi_codes_dep,
  log_dep,
  timestamp_dep,
]
url_test_c_args = [
]
url_test_link_args = [
]

url_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  url_test_exec = executable('url-test',
     url_test_srcs,
     dependencies: url_test_deps,
     include_directories: url_test_include_dirs,
     link_args: url_test_link_args,
     c_args: url_test_c_args,
     install: false,
  )
  test('url-test', 
    url_test_exec, args: ['-v','-a'],
    workdir: url_test_test_dir,
  )
endif
