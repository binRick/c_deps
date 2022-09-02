eventemitter_test_srcs = [
  'eventemitter-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
eventemitter_test_include_dirs = [
  '.',
  inc,
]
eventemitter_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  ansi_codes_dep,
  logh_dep,
  timestamp_dep,
  ms_dep,
  bytes_dep,
  c_eventemitter_dep,
]
eventemitter_test_c_args = [
]
eventemitter_test_link_args = [
]

eventemitter_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  eventemitter_test_exec = executable('eventemitter-test',
     eventemitter_test_srcs,
     dependencies: eventemitter_test_deps,
     include_directories: eventemitter_test_include_dirs,
     link_args: eventemitter_test_link_args,
     c_args: eventemitter_test_c_args,
     install: false,
  )
  #test('eventemitter-test', 
  #  eventemitter_test_exec, args: ['-v','-a'],
  #  workdir: eventemitter_test_test_dir,
  #)
endif
