libutf8_test_srcs = [
  'libutf8-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
libutf8_test_include_dirs = [
  '.',
  inc,
]
libutf8_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  libutf8_dep,
  c_fsio_dep,
  c_stringfn_dep,
  ansi_codes_dep,
  logh_dep,
  timestamp_dep,
]
libutf8_test_c_args = [
]
libutf8_test_link_args = [
]

libutf8_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  libutf8_test_exec = executable('libutf8-test',
     libutf8_test_srcs,
     dependencies: libutf8_test_deps,
     include_directories: libutf8_test_include_dirs,
     link_args: libutf8_test_link_args,
     c_args: libutf8_test_c_args,
     install: false,
  )
  test('libutf8-test', 
    libutf8_test_exec, args: ['-v','-a'],
    workdir: libutf8_test_test_dir,
  )
endif
