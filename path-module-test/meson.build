path_module_test_srcs = [
  'path-module-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
path_module_test_include_dirs = [
  '.',
  inc,
]
path_module_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  path_module_dep,
  ansi_codes_dep,
  log_dep,
  timestamp_dep,
]
path_module_test_c_args = [
]
path_module_test_link_args = [
]

path_module_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  path_module_test_exec = executable('path-module-test',
     path_module_test_srcs,
     dependencies: path_module_test_deps,
     include_directories: path_module_test_include_dirs,
     link_args: path_module_test_link_args,
     c_args: path_module_test_c_args,
     install: false,
  )
  test('path-module-test', 
    path_module_test_exec, args: ['-v','-a'],
    workdir: path_module_test_test_dir,
  )
endif
