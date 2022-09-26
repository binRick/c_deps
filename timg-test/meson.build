timg_test_srcs = [
  'timg-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
timg_test_include_dirs = [
  '.',
  inc,
]
timg_test_deps = [
  c_greatest_dep,
  ansi_codes_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  c_string_buffer_dep,
  timestamp_dep,
  log_dep,
  ms_dep,
  bytes_dep,
  timg_dep,
]
timg_test_c_args = [
]
timg_test_link_args = [
]

timg_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  timg_test_exec = executable('timg-test',
     timg_test_srcs,
     dependencies: timg_test_deps,
     include_directories: timg_test_include_dirs,
     link_args: timg_test_link_args,
     c_args: timg_test_c_args,
     install: false,
  )
  test('timg-test', 
    timg_test_exec, args: ['-v','-a'],
    workdir: timg_test_test_dir,
  )
endif
