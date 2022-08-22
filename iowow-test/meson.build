iowow_test_srcs = [
  'iowow-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
iowow_test_include_dirs = [
  '.',
  inc,
]
iowow_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  iowow_dep,
  c_fsio_dep,
  c_stringfn_dep,
  ansi_codes_dep,
  debug_memory_dep,
]
iowow_test_c_args = [
]
iowow_test_link_args = [
]

iowow_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  iowow_test_exec = executable('iowow-test',
     iowow_test_srcs,
     dependencies: iowow_test_deps,
     include_directories: iowow_test_include_dirs,
     link_args: iowow_test_link_args,
     c_args: iowow_test_c_args,
     install: false,
  )
  #test('iowow-test', 
  #  iowow_test_exec, args: ['-v','-a'],
  #  workdir: iowow_test_test_dir,
  #)
endif
