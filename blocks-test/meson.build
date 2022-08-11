blocks_test_srcs = [
  'blocks-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
blocks_test_include_dirs = [
  '.',
  inc,
]
blocks_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  ansi_codes_dep,
  debug_memory_dep,
]
blocks_test_c_args = [
]
blocks_test_link_args = [
]

blocks_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  blocks_test_exec = executable('blocks-test',
     blocks_test_srcs,
     dependencies: blocks_test_deps,
     include_directories: blocks_test_include_dirs,
     link_args: blocks_test_link_args,
     c_args: blocks_test_c_args,
     install: false,
  )
  #test('blocks-test', 
  #  blocks_test_exec, args: ['-v','-a'],
  #  workdir: blocks_test_test_dir,
  #)
endif
