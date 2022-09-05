microtar_test_srcs = [
  'microtar-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
microtar_test_include_dirs = [
  '.',
  inc,
]
microtar_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  ansi_codes_dep,
  microtar_dep,
  log_dep,
  timestamp_dep,
]
microtar_test_c_args = [
]
microtar_test_link_args = [
]

microtar_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  microtar_test_exec = executable('microtar-test',
     microtar_test_srcs,
     dependencies: microtar_test_deps,
     include_directories: microtar_test_include_dirs,
     link_args: microtar_test_link_args,
     c_args: microtar_test_c_args,
     install: false,
  )
  test('microtar-test', 
    microtar_test_exec, args: ['-v','-a'],
    workdir: microtar_test_test_dir,
  )
endif
