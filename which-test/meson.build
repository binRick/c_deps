which_test_srcs = [
  'which-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
which_test_include_dirs = [
  '.',
  inc,
]
which_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  which_dep,
  c_fsio_dep,
  c_stringfn_dep,
  ansi_codes_dep,
  log_dep,
  timestamp_dep,
]
which_test_c_args = [
]
which_test_link_args = [
]

which_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  which_test_exec = executable('which-test',
     which_test_srcs,
     dependencies: which_test_deps,
     include_directories: which_test_include_dirs,
     link_args: which_test_link_args,
     c_args: which_test_c_args,
     install: false,
  )
  test('which-test', 
    which_test_exec, args: ['-v','-a'],
    workdir: which_test_test_dir,
  )
endif
