libdefer_test_srcs = [
  'libdefer-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
libdefer_test_include_dirs = [
  '.',
  inc,
]
libdefer_test_deps = [
  c_greatest_dep,
  libdefer_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  ansi_codes_dep,
  log_dep,
  timestamp_dep,
  ms_dep,
  bytes_dep,
]
libdefer_test_c_args = [
]
libdefer_test_link_args = [
]

libdefer_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  libdefer_test_exec = executable('libdefer-test',
     libdefer_test_srcs,
     dependencies: libdefer_test_deps,
     include_directories: libdefer_test_include_dirs,
     link_args: libdefer_test_link_args,
     c_args: libdefer_test_c_args,
     install: false,
  )
  #test('libdefer-test', 
  #  libdefer_test_exec, args: ['-v','-a'],
  #  workdir: libdefer_test_test_dir,
  #)
endif
