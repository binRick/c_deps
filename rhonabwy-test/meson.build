rhonabwy_test_srcs = [
  'rhonabwy-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
rhonabwy_test_include_dirs = [
  '.',
  inc,
]
rhonabwy_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  ansi_codes_dep,
  rhonabwy_dep,
  zlib_dep,
  nettle_dep,
  logh_dep,
  timestamp_dep,
  ms_dep,
  bytes_dep,
]
rhonabwy_test_c_args = [
]
rhonabwy_test_link_args = [
]

rhonabwy_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  rhonabwy_test_exec = executable('rhonabwy-test',
     rhonabwy_test_srcs,
     dependencies: rhonabwy_test_deps,
     include_directories: rhonabwy_test_include_dirs,
     link_args: rhonabwy_test_link_args,
     c_args: rhonabwy_test_c_args,
     install: false,
  )
  #test('rhonabwy-test', 
  #  rhonabwy_test_exec, args: ['-v','-a'],
  #  workdir: rhonabwy_test_test_dir,
  #)
endif
