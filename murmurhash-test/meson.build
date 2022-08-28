murmurhash_test_srcs = [
  'murmurhash-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
murmurhash_test_include_dirs = [
  '.',
  inc,
]
murmurhash_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  murmurhash_dep,
  ansi_codes_dep,
  logh_dep,
  timestamp_dep,
]
murmurhash_test_c_args = [
]
murmurhash_test_link_args = [
]

murmurhash_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  murmurhash_test_exec = executable('murmurhash-test',
     murmurhash_test_srcs,
     dependencies: murmurhash_test_deps,
     include_directories: murmurhash_test_include_dirs,
     link_args: murmurhash_test_link_args,
     c_args: murmurhash_test_c_args,
     install: false,
  )
  test('murmurhash-test', 
    murmurhash_test_exec, args: ['-v','-a'],
    workdir: murmurhash_test_test_dir,
  )
endif
