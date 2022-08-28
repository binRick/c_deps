passh_test_srcs = [
  'passh-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
passh_test_include_dirs = [
  '.',
  inc,
]
passh_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  c_passh_dep,
  ansi_codes_dep,
  debug_memory_dep,
]
passh_test_c_args = [
  '-DPASSH_LIB',
]
passh_test_link_args = [
]

passh_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  passh_test_exec = executable('passh-test',
     passh_test_srcs,
     dependencies: passh_test_deps,
     include_directories: passh_test_include_dirs,
     link_args: passh_test_link_args,
     c_args: passh_test_c_args,
     install: false,
  )
  test('passh-test', 
    passh_test_exec, args: ['-v','-a'],
    workdir: passh_test_test_dir,
  )
endif
