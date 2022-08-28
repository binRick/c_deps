hash_test_srcs = [
  'hash-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
hash_test_include_dirs = [
  '.',
  inc,
]
hash_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  ansi_codes_dep,
  hash_dep,
]
hash_test_c_args = [
]
hash_test_link_args = [
]

hash_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  hash_test_exec = executable('hash-test',
     hash_test_srcs,
     dependencies: hash_test_deps,
     include_directories: hash_test_include_dirs,
     link_args: hash_test_link_args,
     c_args: hash_test_c_args,
     install: false,
  )
  test('hash-test', 
    hash_test_exec, args: ['-v','-a'],
    workdir: hash_test_test_dir,
  )
endif
