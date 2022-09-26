workqueue_test_srcs = [
  'workqueue-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
workqueue_test_include_dirs = [
  '.',
  inc,
]
workqueue_test_deps = [
  c_greatest_dep,
  c_workqueue_dep,
  ansi_codes_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  c_string_buffer_dep,
  timestamp_dep,
  log_dep,
  ms_dep,
  bytes_dep,
]
workqueue_test_c_args = [
]
workqueue_test_link_args = [
]

workqueue_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  workqueue_test_exec = executable('workqueue-test',
     workqueue_test_srcs,
     dependencies: workqueue_test_deps,
     include_directories: workqueue_test_include_dirs,
     link_args: workqueue_test_link_args,
     c_args: workqueue_test_c_args,
     install: false,
  )
  test('workqueue-test', 
    workqueue_test_exec, args: ['-v','-a'],
    workdir: workqueue_test_test_dir,
  )
endif
