wg_test_srcs = [
  'wg-test.c',
]
wg_test_inc = [
 '.',
 inc,
]
wg_test_deps = [
 wireguard_tools_dep,
 greatest_dep,
 wg_dep,
]

if get_option('enable-binaries')
  wg_test_exec = executable('wg-test', 
     wg_test_srcs,
     dependencies: wg_test_deps,
     include_directories: wg_test_inc,
  )
  if get_option('enable-binary-tests')
    test('wg-test', sudo_bin, args: [wg_test_exec,'-v','-a'])
  endif
endif
