str_replace_test_srcs = [
  'str-replace-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
str_replace_test_include_dirs = [
  '.',
  inc,
]
str_replace_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  c_fsio_dep,
  str_replace_dep,
  c_stringfn_dep,
  ansi_codes_dep,
  logh_dep,
  timestamp_dep,
]
str_replace_test_c_args = [
]
str_replace_test_link_args = [
]

str_replace_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  str_replace_test_exec = executable('str-replace-test',
     str_replace_test_srcs,
     dependencies: str_replace_test_deps,
     include_directories: str_replace_test_include_dirs,
     link_args: str_replace_test_link_args,
     c_args: str_replace_test_c_args,
     install: false,
  )
  test('str-replace-test', 
    str_replace_test_exec, args: ['-v','-a'],
    workdir: str_replace_test_test_dir,
  )
endif
