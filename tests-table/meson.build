tests_table_test_srcs = [
  'tests-table-main.c',
  'tests-table.c',
]
tests_table_test_inc = [
  inc,
]
tests_table_test_deps = [
  ctable_dep,
]

if get_option('enable-binaries')
  tests_table_test_exec = executable('tests-table',
     [
      tests_table_test_srcs,
     ],
     dependencies: tests_table_test_deps,
     include_directories: [
       tests_table_test_inc,
     ],
  )
  if get_option('enable-binary-tests')
    test('tests-table', tests_table_test_exec, args: ['--test'])
  endif
endif
