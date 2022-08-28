spin_test_srcs = [
  'spin-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
spin_test_include_dirs = [
  '.',
  inc,
]
spin_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  spin_dep,
  c_fsio_dep,
  c_stringfn_dep,
  ansi_codes_dep,
  logh_dep,
  timestamp_dep,
]
spin_test_c_args = [
]
spin_test_link_args = [
]

spin_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  spin_test_exec = executable('spin-test',
     spin_test_srcs,
     dependencies: spin_test_deps,
     include_directories: spin_test_include_dirs,
     link_args: spin_test_link_args,
     c_args: spin_test_c_args,
     install: false,
  )
  test('spin-test', 
    spin_test_exec, args: ['-v','-a'],
    workdir: spin_test_test_dir,
  )
endif
