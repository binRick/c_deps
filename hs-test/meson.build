hs_test_srcs = [
  'hs-test.c',
]
hs_test_inc = [
 '.',
 inc,
]
hs_test_deps = [
 wireguard_tools_dep,
 c_greatest_dep,
 hs_dep,
 c_hs_dep,
]

if get_option('enable-binaries')
  hs_test_exec = executable('hs-test', 
     hs_test_srcs,
     dependencies: hs_test_deps,
     include_directories: hs_test_inc,
  )
  if get_option('enable-binary-tests')
    test('hs-test', passh_program, args: [hs_test_exec])
  endif
endif
