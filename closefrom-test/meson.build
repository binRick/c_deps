closefrom_test_srcs = [
  'closefrom-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
closefrom_test_include_dirs = [
  '.',
  inc,
]
closefrom_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  ansi_codes_dep,
  closefrom_dep,
  logh_dep,
  timestamp_dep,
]
closefrom_test_c_args = [
]
closefrom_test_link_args = [
]

closefrom_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  closefrom_test_exec = executable('closefrom-test',
     closefrom_test_srcs,
     dependencies: closefrom_test_deps,
     include_directories: closefrom_test_include_dirs,
     link_args: closefrom_test_link_args,
     c_args: closefrom_test_c_args,
     install: false,
  )
  test('closefrom-test', 
    closefrom_test_exec, args: ['-v','-a'],
    workdir: closefrom_test_test_dir,
  )
endif
