bitfield_test_srcs = [
  'bitfield-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
bitfield_test_include_dirs = [
  '.',
  inc,
]
bitfield_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  c_fsio_dep,
  bitfield_dep,
  c_stringfn_dep,
  ansi_codes_dep,
  logh_dep,
  timestamp_dep,
]
bitfield_test_c_args = [
]
bitfield_test_link_args = [
]

bitfield_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  bitfield_test_exec = executable('bitfield-test',
     bitfield_test_srcs,
     dependencies: bitfield_test_deps,
     include_directories: bitfield_test_include_dirs,
     link_args: bitfield_test_link_args,
     c_args: bitfield_test_c_args,
     install: false,
  )
  test('bitfield-test', 
    bitfield_test_exec, args: ['-v','-a'],
    workdir: bitfield_test_test_dir,
  )
endif
