md5_test_srcs = [
  'md5-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
md5_test_include_dirs = [
  '.',
  inc,
]
md5_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  c_fsio_dep,
  rhash_md5_dep,
  b64_dep,
  c_stringfn_dep,
  ansi_codes_dep,
  logh_dep,
  timestamp_dep,
]
md5_test_c_args = [
]
md5_test_link_args = [
]

md5_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  md5_test_exec = executable('md5-test',
     md5_test_srcs,
     dependencies: md5_test_deps,
     include_directories: md5_test_include_dirs,
     link_args: md5_test_link_args,
     c_args: md5_test_c_args,
     install: false,
  )
  test('md5-test', 
    md5_test_exec, args: ['-v','-a'],
    workdir: md5_test_test_dir,
  )
endif
