metaref_test_srcs = [
  'metaref-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
metaref_test_include_dirs = [
  '.',
  inc,
]
metaref_test_deps = [
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
  libmetaref_dep,
]
metaref_test_c_args = [
]
metaref_test_link_args = [
]

metaref_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  metaref_test_exec = executable('metaref-test',
     metaref_test_srcs,
     dependencies: metaref_test_deps,
     include_directories: metaref_test_include_dirs,
     link_args: metaref_test_link_args,
     c_args: metaref_test_c_args,
     install: false,
  )
  test('metaref-test', 
    metaref_test_exec, args: ['-v','-a'],
    workdir: metaref_test_test_dir,
  )
endif
