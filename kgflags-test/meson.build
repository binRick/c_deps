kgflags_test_srcs = [
  'kgflags-test.c',
]
kgflags_include_dirs = [
  inc,
]
kgflags_test_kgflags = [
  kgflags_dep,
]
kgflags_c_args = [
]
kgflags_link_args = [
]

if get_option('enable-binaries')
  kgflags_test_exec = executable('kgflags-test',
     kgflags_test_srcs,
     dependencies: kgflags_test_kgflags,
     include_directories: kgflags_include_dirs,
     link_args: kgflags_link_args,
     c_args: kgflags_c_args,
     install: true,
  )
  if get_option('enable-binary-tests')
    test('kgflags-test', 
      kgflags_test_exec, args: ['-v','-a'],
      timeout: 20,
      is_parallel: true,
      workdir: meson.current_source_dir(),
      )
  endif
endif
