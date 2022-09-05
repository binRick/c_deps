wcwidth_test_srcs = [
  'wcwidth-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
wcwidth_test_include_dirs = [
  '.',
  inc,
]
wcwidth_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  wcwidth_dep,
  c_fsio_dep,
  c_stringfn_dep,
  ansi_codes_dep,
  log_dep,
  timestamp_dep,
  ms_dep,
  bytes_dep,
]
wcwidth_test_c_args = [
]
wcwidth_test_link_args = [
]

wcwidth_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  wcwidth_test_exec = executable('wcwidth-test',
     wcwidth_test_srcs,
     dependencies: wcwidth_test_deps,
     include_directories: wcwidth_test_include_dirs,
     link_args: wcwidth_test_link_args,
     c_args: wcwidth_test_c_args,
     install: false,
  )
  test('wcwidth-test', 
    wcwidth_test_exec, args: ['-v','-a'],
    workdir: wcwidth_test_test_dir,
  )
endif
