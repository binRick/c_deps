sigstr_test_srcs = [
  'sigstr-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
sigstr_test_include_dirs = [
  '.',
  inc,
]
sigstr_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  sigstr_dep,
  ansi_codes_dep,
  logh_dep,
  timestamp_dep,
]
sigstr_test_c_args = [
]
sigstr_test_link_args = [
]

sigstr_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  sigstr_test_exec = executable('sigstr-test',
     sigstr_test_srcs,
     dependencies: sigstr_test_deps,
     include_directories: sigstr_test_include_dirs,
     link_args: sigstr_test_link_args,
     c_args: sigstr_test_c_args,
     install: false,
  )
  test('sigstr-test', 
    sigstr_test_exec, args: ['-v','-a'],
    workdir: sigstr_test_test_dir,
  )
endif
