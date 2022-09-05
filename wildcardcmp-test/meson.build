wildcardcmp_test_srcs = [
  'wildcardcmp-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
wildcardcmp_test_include_dirs = [
  '.',
  inc,
]
wildcardcmp_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  ansi_codes_dep,
  wildcardcmp_dep,
  log_dep,
  timestamp_dep,
]
wildcardcmp_test_c_args = [
]
wildcardcmp_test_link_args = [
]

wildcardcmp_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  wildcardcmp_test_exec = executable('wildcardcmp-test',
     wildcardcmp_test_srcs,
     dependencies: wildcardcmp_test_deps,
     include_directories: wildcardcmp_test_include_dirs,
     link_args: wildcardcmp_test_link_args,
     c_args: wildcardcmp_test_c_args,
     install: false,
  )
  test('wildcardcmp-test', 
    wildcardcmp_test_exec, args: ['-v','-a'],
    workdir: wildcardcmp_test_test_dir,
  )
endif
