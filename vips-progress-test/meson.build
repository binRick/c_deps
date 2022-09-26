vips_progress_test_srcs = [
  'vips-progress-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
vips_progress_test_include_dirs = [
  '.',
  inc,
]
vips_progress_test_deps = [
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
  vips_dep,
]
vips_progress_test_c_args = [
]
vips_progress_test_link_args = [
]

vips_progress_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  vips_progress_test_exec = executable('vips-progress-test',
     vips_progress_test_srcs,
     dependencies: vips_progress_test_deps,
     include_directories: vips_progress_test_include_dirs,
     link_args: vips_progress_test_link_args,
     c_args: vips_progress_test_c_args,
     install: false,
  )
  test('vips-progress-test', 
    vips_progress_test_exec, args: ['-v','-a'],
    workdir: vips_progress_test_test_dir,
  )
endif
