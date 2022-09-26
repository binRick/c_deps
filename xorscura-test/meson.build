xorscura_test_srcs = [
  'xorscura-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
xorscura_test_include_dirs = [
  '.',
  inc,
]
xorscura_test_deps = [
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
  xorscura_dep,
]
xorscura_test_c_args = [
]
xorscura_test_link_args = [
]

xorscura_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  xorscura_test_exec = executable('xorscura-test',
     xorscura_test_srcs,
     dependencies: xorscura_test_deps,
     include_directories: xorscura_test_include_dirs,
     link_args: xorscura_test_link_args,
     c_args: xorscura_test_c_args,
     install: false,
  )
  test('xorscura-test', 
    xorscura_test_exec, args: ['-v','-a'],
    workdir: xorscura_test_test_dir,
  )
endif
