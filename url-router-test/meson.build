url_router_test_srcs = [
  'url-router-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
url_router_test_include_dirs = [
  '.',
  inc,
]
url_router_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  c_fsio_dep,
  url_router_dep,
  c_stringfn_dep,
  ansi_codes_dep,
  log_dep,
  timestamp_dep,
]
url_router_test_c_args = [
]
url_router_test_link_args = [
]

url_router_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  url_router_test_exec = executable('url-router-test',
     url_router_test_srcs,
     dependencies: url_router_test_deps,
     include_directories: url_router_test_include_dirs,
     link_args: url_router_test_link_args,
     c_args: url_router_test_c_args,
     install: false,
  )
  test('url-router-test', 
    url_router_test_exec, args: ['-v','-a'],
    workdir: url_router_test_test_dir,
  )
endif
