extname_test_srcs = [
  'extname-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
extname_test_include_dirs = [
  '.',
  inc,
]
extname_test_deps = [
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
  extname_c_dep,
]
extname_test_c_args = [
]
extname_test_link_args = [
]

extname_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  extname_test_exec = executable('extname-test',
     extname_test_srcs,
     dependencies: extname_test_deps,
     include_directories: extname_test_include_dirs,
     link_args: extname_test_link_args,
     c_args: extname_test_c_args,
     install: false,
  )
  test('extname-test', 
    extname_test_exec, args: ['-v','-a'],
    workdir: extname_test_test_dir,
  )
endif
