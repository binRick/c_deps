tiny_regex_test_srcs = [
  'tiny-regex-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
tiny_regex_test_include_dirs = [
  '.',
  inc,
]
tiny_regex_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  tiny_regex_c_dep,
  ansi_codes_dep,
  logh_dep,
  timestamp_dep,
]
tiny_regex_test_c_args = [
]
tiny_regex_test_link_args = [
]

tiny_regex_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  tiny_regex_test_exec = executable('tiny-regex-test',
     tiny_regex_test_srcs,
     dependencies: tiny_regex_test_deps,
     include_directories: tiny_regex_test_include_dirs,
     link_args: tiny_regex_test_link_args,
     c_args: tiny_regex_test_c_args,
     install: false,
  )
  test('tiny-regex-test', 
    tiny_regex_test_exec, args: ['-v','-a'],
    workdir: tiny_regex_test_test_dir,
  )
endif
