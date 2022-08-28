rrdtool_test_srcs = [
  'rrdtool-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
rrdtool_test_include_dirs = [
  '.',
  inc,
]
rrdtool_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  timestamp_dep, 
  logh_dep, 
  rrdtool_dep,
  c_fsio_dep,
  c_stringfn_dep,
  ansi_codes_dep,
  #debug_memory_dep,
]
rrdtool_test_c_args = [
]
rrdtool_test_link_args = [
]

rrdtool_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  rrdtool_test_exec = executable('rrdtool-test',
     rrdtool_test_srcs,
     dependencies: rrdtool_test_deps,
     include_directories: rrdtool_test_include_dirs,
     link_args: rrdtool_test_link_args,
     c_args: rrdtool_test_c_args,
     install: false,
  )
  test('rrdtool-test', 
    rrdtool_test_exec, args: ['-v','-a'],
    workdir: rrdtool_test_test_dir,
  )
endif
