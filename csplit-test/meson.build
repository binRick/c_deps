csplit_test_srcs = [
  'csplit-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
csplit_test_include_dirs = [
  '.',
  inc,
]
csplit_test_deps = [
  c_greatest_dep,
  csplit_dep,
]
csplit_test_c_args = [
]
csplit_test_link_args = [
]

csplit_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  csplit_test_exec = executable('csplit-test',
     csplit_test_srcs,
     dependencies: csplit_test_deps,
     include_directories: csplit_test_include_dirs,
     link_args: csplit_test_link_args,
     c_args: csplit_test_c_args,
     install: false,
  )
  test('csplit-test', 
    csplit_test_exec, args: ['-v','-a'],
    workdir: csplit_test_test_dir,
  )
endif
