libcyaml_test_srcs = [
  'libcyaml-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
libcyaml_test_include_dirs = [
  '.',
  inc,
]
libcyaml_test_deps = [
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
  libcyaml_dep,
]
libcyaml_test_c_args = [
]
libcyaml_test_link_args = [
]

libcyaml_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  libcyaml_test_exec = executable('libcyaml-test',
     libcyaml_test_srcs,
     dependencies: libcyaml_test_deps,
     include_directories: libcyaml_test_include_dirs,
     link_args: libcyaml_test_link_args,
     c_args: libcyaml_test_c_args,
     install: false,
  )
  test('libcyaml-test', 
    libcyaml_test_exec, args: ['-v','-a'],
    workdir: libcyaml_test_test_dir,
  )
endif
