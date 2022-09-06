siphash_test_srcs = [
  'siphash-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
siphash_test_include_dirs = [
  '.',
  inc,
]
siphash_test_deps = [
  c_greatest_dep,
  ansi_codes_dep,
  c_vector_dep,siphash_dep,
  c_fsio_dep,
  c_stringfn_dep,
  c_string_buffer_dep,
  timestamp_dep,
  log_dep,
  ms_dep,
  bytes_dep,
]
siphash_test_c_args = [
]
siphash_test_link_args = [
]

siphash_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  siphash_test_exec = executable('siphash-test',
     siphash_test_srcs,
     dependencies: siphash_test_deps,
     include_directories: siphash_test_include_dirs,
     link_args: siphash_test_link_args,
     c_args: siphash_test_c_args,
     install: false,
  )
  test('siphash-test', 
    siphash_test_exec, args: ['-v','-a'],
    workdir: siphash_test_test_dir,
  )
endif
