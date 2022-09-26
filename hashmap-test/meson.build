hashmap_test_srcs = [
  'hashmap-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
hashmap_test_include_dirs = [
  '.',
  inc,
]
hashmap_test_deps = [
  c_greatest_dep,
  ansi_codes_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  c_string_buffer_dep,
  timestamp_dep,
  log_dep,
  ms_dep,
  bytes_dep,
  hashmap_h_dep,
]
hashmap_test_c_args = [
]
hashmap_test_link_args = [
]

hashmap_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  hashmap_test_exec = executable('hashmap-test',
     hashmap_test_srcs,
     dependencies: hashmap_test_deps,
     include_directories: hashmap_test_include_dirs,
     link_args: hashmap_test_link_args,
     c_args: hashmap_test_c_args,
     install: false,
  )
  test('hashmap-test', 
    hashmap_test_exec, args: ['-v','-a'],
    workdir: hashmap_test_test_dir,
  )
endif
