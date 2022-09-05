hexify_test_srcs = [
  'hexify-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
hexify_test_include_dirs = [
  '.',
  inc,
]
hexify_test_deps = [
  c_greatest_dep,
  c_vector_dep,hexify_c_dep,
  c_fsio_dep,
  c_stringfn_dep,
  ansi_codes_dep,
  log_dep,
  timestamp_dep,
  ms_dep,
  bytes_dep,
]
hexify_test_c_args = [
]
hexify_test_link_args = [
]

hexify_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  hexify_test_exec = executable('hexify-test',
     hexify_test_srcs,
     dependencies: hexify_test_deps,
     include_directories: hexify_test_include_dirs,
     link_args: hexify_test_link_args,
     c_args: hexify_test_c_args,
     install: false,
  )
  #test('hexify-test', 
  #  hexify_test_exec, args: ['-v','-a'],
  #  workdir: hexify_test_test_dir,
  #)
endif
