occurrences_test_srcs = [
  'occurrences-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
occurrences_test_include_dirs = [
  '.',
  inc,
]
occurrences_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  occurrences_dep,
  ansi_codes_dep,
  log_dep,
  timestamp_dep,
]
occurrences_test_c_args = [
  '-DGREATEST_USE_LONGJMP=0',
]
occurrences_test_link_args = [
]

occurrences_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  occurrences_test_exec = executable('occurrences-test',
     occurrences_test_srcs,
     dependencies: occurrences_test_deps,
     include_directories: occurrences_test_include_dirs,
     link_args: occurrences_test_link_args,
     c_args: occurrences_test_c_args,
     install: false,
  )
  test('occurrences-test', 
    occurrences_test_exec, args: ['-v','-a'],
    workdir: occurrences_test_test_dir,
  )
endif
