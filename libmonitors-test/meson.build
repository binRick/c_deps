libmonitors_test_srcs = [
  'libmonitors-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
libmonitors_test_include_dirs = [
  '.',
  inc,
]
libmonitors_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  libmonitors_dep,
  ansi_codes_dep,
  log_dep,
  timestamp_dep,
]
libmonitors_test_c_args = [
]
libmonitors_test_link_args = [
]

libmonitors_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  libmonitors_test_exec = executable('libmonitors-test',
     libmonitors_test_srcs,
     dependencies: libmonitors_test_deps,
     include_directories: libmonitors_test_include_dirs,
     link_args: libmonitors_test_link_args,
     c_args: libmonitors_test_c_args,
     install: false,
  )
  test('libmonitors-test', 
    libmonitors_test_exec, args: ['-v','-a'],
    workdir: libmonitors_test_test_dir,
  )
endif
