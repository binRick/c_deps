base64_test_srcs = [
  'base64-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
base64_test_include_dirs = [
  '.',
  inc,
]
base64_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  ansi_codes_dep,
  base64_dep,
]
base64_test_c_args = [
]
base64_test_link_args = [
]

base64_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  base64_test_exec = executable('base64-test',
     base64_test_srcs,
     dependencies: base64_test_deps,
     include_directories: base64_test_include_dirs,
     link_args: base64_test_link_args,
     c_args: base64_test_c_args,
     install: false,
  )
  test('base64-test', 
    base64_test_exec, args: ['-v','-a'],
    workdir: base64_test_test_dir,
  )
endif
