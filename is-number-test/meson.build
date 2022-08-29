is_number_test_srcs = [
  'is-number-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
is_number_test_include_dirs = [
  '.',
  inc,
]
is_number_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  is_number_c_dep,
  ansi_codes_dep,
  logh_dep,
  timestamp_dep,
]
is_number_test_c_args = [
]
is_number_test_link_args = [
]

is_number_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  is_number_test_exec = executable('is-number-test',
     is_number_test_srcs,
     dependencies: is_number_test_deps,
     include_directories: is_number_test_include_dirs,
     link_args: is_number_test_link_args,
     c_args: is_number_test_c_args,
     install: false,
  )
  test('is-number-test', 
    is_number_test_exec, args: ['-v','-a'],
    workdir: is_number_test_test_dir,
  )
endif
