ck_test_srcs = [
  'ck-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
ck_test_include_dirs = [
  '.',
  inc,
]
ck_test_deps = [
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
  ck_dep,
]
ck_test_c_args = [
]
ck_test_link_args = [
]

ck_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  ck_test_exec = executable('ck-test',
     ck_test_srcs,
     dependencies: ck_test_deps,
     include_directories: ck_test_include_dirs,
     link_args: ck_test_link_args,
     c_args: ck_test_c_args,
     install: false,
  )
  test('ck-test', 
    ck_test_exec, args: ['-v','-a'],
    workdir: ck_test_test_dir,
  )
endif
