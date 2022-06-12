gumbo_test_srcs = [
  'gumbo-test.c',
]
gumbo_test_inc = [
 inc,
]
gumbo_test_deps = [
 gumbo_dep,
]

if get_option('enable-binaries')
  gumbo_test_exec = executable('gumbo-test', 
     gumbo_test_srcs,
     dependencies: gumbo_test_deps,
     include_directories: gumbo_test_inc,
  )
  if get_option('enable-binary-tests')
    test('gumbo-test', gumbo_test_exec, args: ['--test'])
  endif
endif
