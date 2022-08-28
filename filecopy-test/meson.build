filecopy_test_srcs = [
  'filecopy-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
filecopy_test_include_dirs = [
  '.',
  inc,
]
filecopy_test_deps = [
  c_greatest_dep,
  c_fsio_dep,
  filecopy_dep,
]
filecopy_test_c_args = [
]
filecopy_test_link_args = [
]

filecopy_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  filecopy_test_exec = executable('filecopy-test',
     filecopy_test_srcs,
     dependencies: filecopy_test_deps,
     include_directories: filecopy_test_include_dirs,
     link_args: filecopy_test_link_args,
     c_args: filecopy_test_c_args,
     install: false,
  )
  #test('filecopy-test', 
  #  filecopy_test_exec, args: ['-v','-a'],
  #  workdir: filecopy_test_test_dir,
  #)
endif
