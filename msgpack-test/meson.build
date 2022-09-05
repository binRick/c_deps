msgpack_test_srcs = [
  'msgpack-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
msgpack_test_include_dirs = [
  '.',
  inc,
]
msgpack_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  ansi_codes_dep,
  msgpack_c_dep,
  log_dep,
  timestamp_dep,
  ms_dep,
  bytes_dep,
]
msgpack_test_c_args = [
]
msgpack_test_link_args = [
]

msgpack_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  msgpack_test_exec = executable('msgpack-test',
     msgpack_test_srcs,
     dependencies: msgpack_test_deps,
     include_directories: msgpack_test_include_dirs,
     link_args: msgpack_test_link_args,
     c_args: msgpack_test_c_args,
     install: false,
  )
  test('msgpack-test', 
    msgpack_test_exec, args: ['-v','-a'],
    workdir: msgpack_test_test_dir,
  )
endif
