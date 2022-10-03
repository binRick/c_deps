memory_leak_detector_test_srcs = [
  'memory-leak-detector-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
memory_leak_detector_test_include_dirs = [
  '.',
  inc,
]
memory_leak_detector_test_deps = [
  c_greatest_dep,
  ansi_codes_dep,memory_leak_detector_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  c_string_buffer_dep,
  timestamp_dep,
  log_dep,
  ms_dep,
  bytes_dep,
]
memory_leak_detector_test_c_args = [
  '-Wno-unused-variable',
]
memory_leak_detector_test_link_args = [
]

memory_leak_detector_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  memory_leak_detector_test_exec = executable('memory-leak-detector-test',
     memory_leak_detector_test_srcs,
     dependencies: memory_leak_detector_test_deps,
     include_directories: memory_leak_detector_test_include_dirs,
     link_args: memory_leak_detector_test_link_args,
     c_args: memory_leak_detector_test_c_args,
     install: false,
  )
  #test('memory-leak-detector-test', 
  #  memory_leak_detector_test_exec, args: ['-v','-a'],
  #  workdir: memory_leak_detector_test_test_dir,
  #)
endif
