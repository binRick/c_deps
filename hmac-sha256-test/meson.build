hmac_sha256_test_srcs = [
  'hmac-sha256-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
hmac_sha256_test_include_dirs = [
  '.',
  inc,
]
hmac_sha256_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  ansi_codes_dep,
  hmac_sha256_dep,
  log_dep,
  timestamp_dep,
]
hmac_sha256_test_c_args = [
]
hmac_sha256_test_link_args = [
]

hmac_sha256_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  hmac_sha256_test_exec = executable('hmac-sha256-test',
     hmac_sha256_test_srcs,
     dependencies: hmac_sha256_test_deps,
     include_directories: hmac_sha256_test_include_dirs,
     link_args: hmac_sha256_test_link_args,
     c_args: hmac_sha256_test_c_args,
     install: false,
  )
  test('hmac-sha256-test', 
    hmac_sha256_test_exec, args: ['-v','-a'],
    workdir: hmac_sha256_test_test_dir,
  )
endif
