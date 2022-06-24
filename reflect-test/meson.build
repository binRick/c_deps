reflect_test_srcs = [
  'reflect-test.c',
]
reflect_include_dirs = [
  inc,
]
reflect_test_reflect = [
  generic_print_dep,
  logh_dep,
  dbg_dep,
  dmt_dep,
  ansi_utils_dep,
  mkcreflect_dep,
]
reflect_c_args = [
]
reflect_link_args = [
]
if get_option('enable-binaries')
  reflect_test_exec = executable('reflect-test',
     reflect_test_srcs,
     dependencies: reflect_test_reflect,
     include_directories: reflect_include_dirs,
     link_args: reflect_link_args,
     c_args: reflect_c_args,
     install: true,
     pie: true,
  )
  if get_option('enable-binary-tests')
    test('reflect-test', 
      passh_program, args: [reflect_test_exec],
      timeout: 5,
      is_parallel: true,
      workdir: meson.current_source_dir(),
      verbose: true,
      )
  endif
endif
