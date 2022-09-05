panic_test_srcs = [
  'panic-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
panic_test_include_dirs = [
  '.',
  inc,
]
panic_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  panic_dep,
  c_fsio_dep,
  c_stringfn_dep,
  ansi_codes_dep,
  log_dep,
  timestamp_dep,
]
panic_test_c_args = [
]
panic_test_link_args = [
]

panic_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  panic_test_exec = executable('panic-test',
     panic_test_srcs,
     dependencies: panic_test_deps,
     include_directories: panic_test_include_dirs,
     link_args: panic_test_link_args,
     c_args: panic_test_c_args,
     install: false,
  )
  test('panic-test', 
    panic_test_exec, args: ['-v','-a'],
    workdir: panic_test_test_dir,
  )
endif
