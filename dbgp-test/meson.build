dbgp_test_srcs = [
  'dbgp-test.c',
]
dbgp_include_dirs = [
  inc,
]
dbgp_test_dbgp = [
  dbgp_dep,
  sdl2_dep,
  dbgp_dep,
  greatest_dep,
]

if get_option('enable-binaries')
  dbgp_test_exec = executable('dbgp-test',
     dbgp_test_srcs,
     dependencies: dbgp_test_dbgp,
     include_directories: dbgp_include_dirs,
  )
  if get_option('enable-binary-tests')
    test('dbgp-test', dbgp_test_exec, args: [])
  endif
endif
