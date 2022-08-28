get_next_line_test_srcs = [
  'get-next-line-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
get_next_line_test_include_dirs = [
  '.',
  inc,
]
get_next_line_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  ansi_codes_dep,
  get_next_line_dep,
  debug_memory_dep,
]
get_next_line_test_c_args = [
]
get_next_line_test_link_args = [
]

get_next_line_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  get_next_line_test_exec = executable('get-next-line-test',
     get_next_line_test_srcs,
     dependencies: get_next_line_test_deps,
     include_directories: get_next_line_test_include_dirs,
     link_args: get_next_line_test_link_args,
     c_args: get_next_line_test_c_args,
     install: false,
  )
  test('get-next-line-test', 
    get_next_line_test_exec, args: ['-v','-a'],
    workdir: get_next_line_test_test_dir,
  )
endif
