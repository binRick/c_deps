genpassword_test_srcs = [
  'genpassword-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
genpassword_test_include_dirs = [
  '.',
  inc,
]
genpassword_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  genpassword_c_dep,
  c_fsio_dep,
  c_stringfn_dep,
  ansi_codes_dep,
  logh_dep,
  timestamp_dep,
]
genpassword_test_c_args = [
]
genpassword_test_link_args = [
]

genpassword_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  genpassword_test_exec = executable('genpassword-test',
     genpassword_test_srcs,
     dependencies: genpassword_test_deps,
     include_directories: genpassword_test_include_dirs,
     link_args: genpassword_test_link_args,
     c_args: genpassword_test_c_args,
     install: false,
  )
  test('genpassword-test', 
    genpassword_test_exec, args: ['-v','-a'],
    workdir: genpassword_test_test_dir,
  )
endif
