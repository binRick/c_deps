microhex_test_srcs = [
  'microhex-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
microhex_test_include_dirs = [
  '.',
  inc,
]
microhex_test_deps = [
  c_greatest_dep,
  ansi_codes_dep,
  microhex_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  c_string_buffer_dep,
  timestamp_dep,
  log_dep,
  ms_dep,
  bytes_dep,
]
microhex_test_c_args = [
]
microhex_test_link_args = [
]

microhex_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  microhex_test_exec = executable('microhex-test',
     microhex_test_srcs,
     dependencies: microhex_test_deps,
     include_directories: microhex_test_include_dirs,
     link_args: microhex_test_link_args,
     c_args: microhex_test_c_args,
     install: false,
  )
  test('microhex-test', 
    microhex_test_exec, args: ['-v','-a'],
    workdir: microhex_test_test_dir,
  )
endif
