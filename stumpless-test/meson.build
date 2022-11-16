stumpless_test_srcs = [
  'stumpless-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
stumpless_test_include_dirs = [
  '.',
  inc,
]
stumpless_test_deps = [
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
  stumpless_dep,
]
stumpless_test_c_args = [
]
stumpless_test_link_args = [
]

stumpless_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  stumpless_test_exec = executable('stumpless-test',
     stumpless_test_srcs,
     dependencies: stumpless_test_deps,
     include_directories: stumpless_test_include_dirs,
     link_args: stumpless_test_link_args,
     c_args: stumpless_test_c_args,
     install: false,
  )
  test('stumpless-test', 
    stumpless_test_exec, args: ['-v','-a'],
    workdir: stumpless_test_test_dir,
  )
endif
