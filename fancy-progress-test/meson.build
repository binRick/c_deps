fancy_progress_test_srcs = [
  'fancy-progress-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
fancy_progress_test_include_dirs = [
  '.',
  inc,
]
fancy_progress_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  ansi_codes_dep,
  fancy_progress_dep,
  debug_memory_dep,
]
fancy_progress_test_c_args = [
]
fancy_progress_test_link_args = [
]

fancy_progress_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  fancy_progress_test_exec = executable('fancy-progress-test',
     fancy_progress_test_srcs,
     dependencies: fancy_progress_test_deps,
     include_directories: fancy_progress_test_include_dirs,
     link_args: fancy_progress_test_link_args,
     c_args: fancy_progress_test_c_args,
     install: false,
  )
  test('fancy-progress-test', 
    fancy_progress_test_exec, args: ['-v','-a'],
    workdir: fancy_progress_test_test_dir,
  )
endif
