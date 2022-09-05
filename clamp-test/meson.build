clamp_test_srcs = [
  'clamp-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
clamp_test_include_dirs = [
  '.',
  inc,
]
clamp_test_deps = [
  c_greatest_dep,
  clamp_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  ansi_codes_dep,
  log_dep,
  timestamp_dep,
]
clamp_test_c_args = [
]
clamp_test_link_args = [
]

clamp_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  clamp_test_exec = executable('clamp-test',
     clamp_test_srcs,
     dependencies: clamp_test_deps,
     include_directories: clamp_test_include_dirs,
     link_args: clamp_test_link_args,
     c_args: clamp_test_c_args,
     install: false,
  )
  test('clamp-test', 
    clamp_test_exec, args: ['-v','-a'],
    workdir: clamp_test_test_dir,
  )
endif
