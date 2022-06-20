cgif_test_srcs = [
  'cgif-test.c',
]
cgif_test_inc = [
 inc,
]
cgif_test_deps = [
 cgif_dep,
]

if get_option('enable-binaries')
  #  cgif_test_exec = executable('cgif-test', 
  #   cgif_test_srcs,
  #   dependencies: cgif_test_deps,
  #   include_directories: cgif_test_inc,
  #)
  if get_option('enable-binary-tests')
    #    test('cgif-test', cgif_test_exec, args: ['--test'])
  endif
endif
