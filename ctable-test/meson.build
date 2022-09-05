ctable_test_srcs = [
  'ctable-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
ctable_test_include_dirs = [
  '.',
  inc,
]
ctable_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  ctable_dep,
  c_fsio_dep,
  c_stringfn_dep,
  ansi_codes_dep,
  log_dep,
  timestamp_dep,
]
ctable_test_c_args = [
]
ctable_test_link_args = [
]

ctable_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  ctable_test_exec = executable('ctable-test',
     ctable_test_srcs,
     dependencies: ctable_test_deps,
     include_directories: ctable_test_include_dirs,
     link_args: ctable_test_link_args,
     c_args: ctable_test_c_args,
     install: false,
  )
  test('ctable-test', 
    ctable_test_exec, args: ['-v','-a'],
    workdir: ctable_test_test_dir,
  )
endif
