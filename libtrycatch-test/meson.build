libtrycatch_test_srcs = [
  'libtrycatch-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
libtrycatch_test_include_dirs = [
  '.',
  inc,
]
libtrycatch_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  libtrycatch_dep,
  c_fsio_dep,
  c_stringfn_dep,
  ansi_codes_dep,
  logh_dep,
  timestamp_dep,
]
libtrycatch_test_c_args = [
]
libtrycatch_test_link_args = [
]

libtrycatch_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  libtrycatch_test_exec = executable('libtrycatch-test',
     libtrycatch_test_srcs,
     dependencies: libtrycatch_test_deps,
     include_directories: libtrycatch_test_include_dirs,
     link_args: libtrycatch_test_link_args,
     c_args: libtrycatch_test_c_args,
     install: false,
  )
  test('libtrycatch-test', 
    libtrycatch_test_exec, args: ['-v','-a'],
    workdir: libtrycatch_test_test_dir,
  )
endif
