font_test_srcs = [
  'font-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
font_test_include_dirs = [
  '.',
  inc,
]
font_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  c_fsio_dep,
  font_dep,
  c_stringfn_dep,
  ansi_codes_dep,
  logh_dep,
  timestamp_dep,
]
font_test_c_args = [
]
font_test_link_args = [
]

font_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  font_test_exec = executable('font-test',
     font_test_srcs,
     dependencies: font_test_deps,
     include_directories: font_test_include_dirs,
     link_args: font_test_link_args,
     c_args: font_test_c_args,
     install: false,
  )
  test('font-test', 
    font_test_exec, args: ['-v','-a'],
    workdir: font_test_test_dir,
  )
endif
