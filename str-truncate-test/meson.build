str_truncate_test_srcs = [
  'str-truncate-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
str_truncate_test_include_dirs = [
  '.',
  inc,
]
str_truncate_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  str_truncate_dep,
  ansi_codes_dep,
  log_dep,
  timestamp_dep,
]
str_truncate_test_c_args = [
]
str_truncate_test_link_args = [
]

str_truncate_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  str_truncate_test_exec = executable('str-truncate-test',
     str_truncate_test_srcs,
     dependencies: str_truncate_test_deps,
     include_directories: str_truncate_test_include_dirs,
     link_args: str_truncate_test_link_args,
     c_args: str_truncate_test_c_args,
     install: false,
  )
  test('str-truncate-test', 
    str_truncate_test_exec, args: ['-v','-a'],
    workdir: str_truncate_test_test_dir,
  )
endif
