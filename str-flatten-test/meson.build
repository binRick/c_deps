str_flatten_test_srcs = [
  'str-flatten-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
str_flatten_test_include_dirs = [
  '.',
  inc,
]
str_flatten_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  c_fsio_dep,
  str_flatten_c_dep,
  c_stringfn_dep,
  ansi_codes_dep,
  logh_dep,
  timestamp_dep,
]
str_flatten_test_c_args = [
]
str_flatten_test_link_args = [
]

str_flatten_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  str_flatten_test_exec = executable('str-flatten-test',
     str_flatten_test_srcs,
     dependencies: str_flatten_test_deps,
     include_directories: str_flatten_test_include_dirs,
     link_args: str_flatten_test_link_args,
     c_args: str_flatten_test_c_args,
     install: false,
  )
  test('str-flatten-test', 
    str_flatten_test_exec, args: ['-v','-a'],
    workdir: str_flatten_test_test_dir,
  )
endif
