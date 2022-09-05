minmax_test_srcs = [
  'minmax-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
minmax_test_include_dirs = [
  '.',
  inc,
]
minmax_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  ansi_codes_dep,
  minmax_dep,
  log_dep,
  timestamp_dep,
]
minmax_test_c_args = [
]
minmax_test_link_args = [
]

minmax_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  minmax_test_exec = executable('minmax-test',
     minmax_test_srcs,
     dependencies: minmax_test_deps,
     include_directories: minmax_test_include_dirs,
     link_args: minmax_test_link_args,
     c_args: minmax_test_c_args,
     install: false,
  )
  test('minmax-test', 
    minmax_test_exec, args: ['-v','-a'],
    workdir: minmax_test_test_dir,
  )
endif
