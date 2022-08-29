uuid4_test_srcs = [
  'uuid4-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
uuid4_test_include_dirs = [
  '.',
  inc,
]
uuid4_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  uuid4_dep,
  ansi_codes_dep,
  logh_dep,
  timestamp_dep,
]
uuid4_test_c_args = [
]
uuid4_test_link_args = [
]

uuid4_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  uuid4_test_exec = executable('uuid4-test',
     uuid4_test_srcs,
     dependencies: uuid4_test_deps,
     include_directories: uuid4_test_include_dirs,
     link_args: uuid4_test_link_args,
     c_args: uuid4_test_c_args,
     install: false,
  )
  test('uuid4-test', 
    uuid4_test_exec, args: ['-v','-a'],
    workdir: uuid4_test_test_dir,
  )
endif
