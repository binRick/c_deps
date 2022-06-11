term_tests_test_srcs = [
  'term-tests-test.c',
]
term_tests_test_inc = [
  '../submodules/termpaint',
]
term_tests_test_deps = [
  term_tests_dep,
]

if get_option('enable-binaries')
  term_tests_test_exec = executable('term-tests-test',
     [
      term_tests_test_srcs,
     ],
     dependencies: term_tests_test_deps,
     include_directories: [
       term_tests_test_inc,
     ],
  )
  if get_option('enable-binary-tests')
    test('term-tests-test', term_tests_test_exec, args: ['--test'])
  endif
endif
