chfreq_test_srcs = [
  'chfreq-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
chfreq_test_include_dirs = [
  '.',
  inc,
]
chfreq_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  c_fsio_dep,
  chfreq_c_dep,
  c_stringfn_dep,
  ansi_codes_dep,
  logh_dep,
  timestamp_dep,
]
chfreq_test_c_args = [
]
chfreq_test_link_args = [
]

chfreq_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  chfreq_test_exec = executable('chfreq-test',
     chfreq_test_srcs,
     dependencies: chfreq_test_deps,
     include_directories: chfreq_test_include_dirs,
     link_args: chfreq_test_link_args,
     c_args: chfreq_test_c_args,
     install: false,
  )
  test('chfreq-test', 
    chfreq_test_exec, args: ['-v','-a'],
    workdir: chfreq_test_test_dir,
  )
endif
