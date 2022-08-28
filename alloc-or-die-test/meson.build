alloc_or_die_test_srcs = [
  'alloc-or-die-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
alloc_or_die_test_include_dirs = [
  '.',
  inc,
]
alloc_or_die_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  ansi_codes_dep,
  alloc_or_die_dep,
]
alloc_or_die_test_c_args = [
]
alloc_or_die_test_link_args = [
]

alloc_or_die_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  alloc_or_die_test_exec = executable('alloc-or-die-test',
     alloc_or_die_test_srcs,
     dependencies: alloc_or_die_test_deps,
     include_directories: alloc_or_die_test_include_dirs,
     link_args: alloc_or_die_test_link_args,
     c_args: alloc_or_die_test_c_args,
     install: false,
  )
  test('alloc-or-die-test', 
    alloc_or_die_test_exec, args: ['-v','-a'],
    workdir: alloc_or_die_test_test_dir,
  )
endif
