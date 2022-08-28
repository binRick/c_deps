logy_test_srcs = [
  'logy-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
logy_test_include_dirs = [
  '.',
  inc,
]
logy_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  logy_dep,
  c_fsio_dep,
  c_stringfn_dep,
  ansi_codes_dep,
  debug_memory_dep,
]
logy_test_c_args = [
]
logy_test_link_args = [
]

logy_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  logy_test_exec = executable('logy-test',
     logy_test_srcs,
     dependencies: logy_test_deps,
     include_directories: logy_test_include_dirs,
     link_args: logy_test_link_args,
     c_args: logy_test_c_args,
     install: false,
  )
  test('logy-test', 
    logy_test_exec, args: ['-v','-a'],
    workdir: logy_test_test_dir,
  )
endif
