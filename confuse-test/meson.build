confuse_test_srcs = [
  'confuse-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
confuse_test_include_dirs = [
  '.',
  inc,
]
confuse_test_deps = [
  c_greatest_dep,libconfuse_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  ansi_codes_dep,
  log_dep,
  timestamp_dep,
  ms_dep,
  bytes_dep,
]
confuse_test_c_args = [
]
confuse_test_link_args = [
]

confuse_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  confuse_test_exec = executable('confuse-test',
     confuse_test_srcs,
     dependencies: confuse_test_deps,
     include_directories: confuse_test_include_dirs,
     link_args: confuse_test_link_args,
     c_args: confuse_test_c_args,
     install: false,
  )
  test('confuse-test', 
    confuse_test_exec, args: ['-v','-a'],
    workdir: confuse_test_test_dir,
  )
endif
