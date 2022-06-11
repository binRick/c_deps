ctable_test_srcs = [
  'ctable-main.c',
  'ctable-test.c',
]
ctable_test_inc = [
  inc,
]
ctable_test_deps = [
  ctable_dep,
]

if get_option('enable-binaries')
  ctable_test_exec = executable('ctable-test',
     [
      ctable_test_srcs,
     ],
     dependencies: ctable_test_deps,
     include_directories: [
       ctable_test_inc,
     ],
  )
  if get_option('enable-binary-tests')
    test('ctable-test', ctable_test_exec, args: ['--test'])
  endif
endif
