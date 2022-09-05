slug_test_srcs = [
  'slug-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
slug_test_include_dirs = [
  '.',
  inc,
]
slug_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  c_fsio_dep,
  slug_dep,
  c_stringfn_dep,
  ansi_codes_dep,
  log_dep,
  timestamp_dep,
]
slug_test_c_args = [
]
slug_test_link_args = [
]

slug_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  slug_test_exec = executable('slug-test',
     slug_test_srcs,
     dependencies: slug_test_deps,
     include_directories: slug_test_include_dirs,
     link_args: slug_test_link_args,
     c_args: slug_test_c_args,
     install: false,
  )
  test('slug-test', 
    slug_test_exec, args: ['-v','-a'],
    workdir: slug_test_test_dir,
  )
endif
