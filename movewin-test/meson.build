movewin_test_srcs = [
  'movewin-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
movewin_test_include_dirs = [
  '.',
  inc,
]
movewin_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  ansi_codes_dep,
  logh_dep,
  timestamp_dep,
]
movewin_test_c_args = [
]
movewin_test_link_args = [
]

movewin_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  movewin_test_exec = executable('movewin-test',
     movewin_test_srcs,
     dependencies: movewin_test_deps,
     include_directories: movewin_test_include_dirs,
     link_args: movewin_test_link_args,
     c_args: movewin_test_c_args,
     install: false,
  )
  test('movewin-test', 
    movewin_test_exec, args: ['-v','-a'],
    workdir: movewin_test_test_dir,
  )
endif
