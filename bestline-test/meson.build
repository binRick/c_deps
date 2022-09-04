bestline_test_srcs = [
  'bestline-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
bestline_test_include_dirs = [
  '.',
  inc,
]
bestline_test_deps = [
  c_greatest_dep,bestline_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  ansi_codes_dep,
  logh_dep,
  timestamp_dep,
  ms_dep,
  bytes_dep,
]
bestline_test_c_args = [
]
bestline_test_link_args = [
]

bestline_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  bestline_test_exec = executable('bestline-test',
     bestline_test_srcs,
     dependencies: bestline_test_deps,
     include_directories: bestline_test_include_dirs,
     link_args: bestline_test_link_args,
     c_args: bestline_test_c_args,
     install: false,
  )
  test('bestline-test', 
    bestline_test_exec, args: ['-v','-a'],
    workdir: bestline_test_test_dir,
  )
endif
