totp_test_srcs = [
  'totp-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
totp_test_include_dirs = [
  '.',
  inc,
]
totp_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  ansi_codes_dep,
  libmutotp_dep,
  logh_dep,
  timestamp_dep,
]
totp_test_c_args = [
]
totp_test_link_args = [
]

totp_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  totp_test_exec = executable('totp-test',
     totp_test_srcs,
     dependencies: totp_test_deps,
     include_directories: totp_test_include_dirs,
     link_args: totp_test_link_args,
     c_args: totp_test_c_args,
     install: false,
  )
  test('totp-test', 
    totp_test_exec, args: ['-v','-a'],
    workdir: totp_test_test_dir,
  )
endif
