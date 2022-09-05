smaz_test_srcs = [
  'smaz-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
smaz_test_include_dirs = [
  '.',
  inc,
]
smaz_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  c_fsio_dep,
  smaz_dep,
  c_stringfn_dep,
  ansi_codes_dep,
  log_dep,
  timestamp_dep,
]
smaz_test_c_args = [
]
smaz_test_link_args = [
]

smaz_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  smaz_test_exec = executable('smaz-test',
     smaz_test_srcs,
     dependencies: smaz_test_deps,
     include_directories: smaz_test_include_dirs,
     link_args: smaz_test_link_args,
     c_args: smaz_test_c_args,
     install: false,
  )
  test('smaz-test', 
    smaz_test_exec, args: ['-v','-a'],
    workdir: smaz_test_test_dir,
  )
endif
