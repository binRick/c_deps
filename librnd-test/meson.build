librnd_test_srcs = [
  'librnd-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
librnd_test_include_dirs = [
  '.',
  inc,
]
librnd_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  log_dep,
  ansi_codes_dep,
  debug_memory_dep,
  librnd_dep,
]
librnd_test_c_args = [
]
librnd_test_link_args = [
]

librnd_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  librnd_test_exec = executable('librnd-test',
     librnd_test_srcs,
     dependencies: librnd_test_deps,
     include_directories: librnd_test_include_dirs,
     link_args: librnd_test_link_args,
     c_args: librnd_test_c_args,
     install: false,
  )
  test('librnd-test', 
    librnd_test_exec, args: ['-v','-a'],
    workdir: librnd_test_test_dir,
  )
endif
