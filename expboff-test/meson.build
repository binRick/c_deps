expboff_test_srcs = [
  'expboff-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
expboff_test_include_dirs = [
  '.',
  inc,
]
expboff_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  expboff_dep,
  c_fsio_dep,
  c_stringfn_dep,
  ansi_codes_dep,
  logh_dep,
  timestamp_dep,
  ms_dep,
  bytes_dep,
]
expboff_test_c_args = [
]
expboff_test_link_args = [
]

expboff_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  expboff_test_exec = executable('expboff-test',
     expboff_test_srcs,
     dependencies: expboff_test_deps,
     include_directories: expboff_test_include_dirs,
     link_args: expboff_test_link_args,
     c_args: expboff_test_c_args,
     install: false,
  )
  #test('expboff-test', 
  #  expboff_test_exec, args: ['-v','-a'],
  #  workdir: expboff_test_test_dir,
  #)
endif
