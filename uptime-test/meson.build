uptime_test_srcs = [
  'uptime-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
uptime_test_include_dirs = [
  '.',
  inc,
]
uptime_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  ansi_codes_dep,
  logh_dep,
  uptime_dep,
  timestamp_dep,
]
uptime_test_c_args = [
]
uptime_test_link_args = [
]

uptime_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  uptime_test_exec = executable('uptime-test',
     uptime_test_srcs,
     dependencies: uptime_test_deps,
     include_directories: uptime_test_include_dirs,
     link_args: uptime_test_link_args,
     c_args: uptime_test_c_args,
     install: false,
  )
  test('uptime-test', 
    uptime_test_exec, args: ['-v','-a'],
    workdir: uptime_test_test_dir,
  )
endif
