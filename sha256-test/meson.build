sha256_test_srcs = [
  'sha256-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
sha256_test_include_dirs = [
  '.',
  inc,
]
sha256_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  sha256_c_dep,
  ansi_codes_dep,
  log_dep,
  timestamp_dep,
]
sha256_test_c_args = [
]
sha256_test_link_args = [
]

sha256_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  sha256_test_exec = executable('sha256-test',
     sha256_test_srcs,
     dependencies: sha256_test_deps,
     include_directories: sha256_test_include_dirs,
     link_args: sha256_test_link_args,
     c_args: sha256_test_c_args,
     install: false,
  )
  test('sha256-test', 
    sha256_test_exec, args: ['-v','-a'],
    workdir: sha256_test_test_dir,
  )
endif
