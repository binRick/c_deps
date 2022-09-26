qoi_ci_test_srcs = [
  'qoi-ci-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
qoi_ci_test_include_dirs = [
  '.',
  inc,
]
qoi_ci_test_deps = [
  c_greatest_dep,
  ansi_codes_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  c_string_buffer_dep,
  timestamp_dep,
  log_dep,
  ms_dep,
  bytes_dep,incbin_dep,
  qoi_ci_dep,
]
qoi_ci_test_c_args = [
  '-DINCBIN_SILENCE_BITCODE_WARNING',
]
qoi_ci_test_link_args = [
]

qoi_ci_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  qoi_ci_test_exec = executable('qoi-ci-test',
     qoi_ci_test_srcs,
     dependencies: qoi_ci_test_deps,
     include_directories: qoi_ci_test_include_dirs,
     link_args: qoi_ci_test_link_args,
     c_args: qoi_ci_test_c_args,
     install: false,
  )
  test('qoi-ci-test', 
    qoi_ci_test_exec, args: ['-v','-a'],
    workdir: qoi_ci_test_test_dir,
  )
endif
