log_test_srcs = [
  'log-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
log_test_include_dirs = [
  '.',
  inc,
]
log_test_deps = [
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
]
log_test_c_args = [
]
log_test_link_args = [
]

log_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  log_test_exec = executable('log-test',
     log_test_srcs,
     dependencies: log_test_deps,
     include_directories: log_test_include_dirs,
     link_args: log_test_link_args,
     c_args: log_test_c_args,
     install: false,
  )
  test('log-test', 
    log_test_exec, args: ['-v','-a'],
    workdir: log_test_test_dir,
  )
endif
