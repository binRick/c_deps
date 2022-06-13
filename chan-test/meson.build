chan_test_srcs = [
  'chan-test.c',
]
chan_test_inc = [
 inc,
]
chan_test_deps = [
 chan_dep,
 greatest_dep,
 ansicodes_dep,
 logh_dep,
 ms_dep,
 timestamp_dep,
]

if get_option('enable-binaries')
  chan_test_exec = executable('chan-test', 
     chan_test_srcs,
     dependencies: chan_test_deps,
     include_directories: chan_test_inc,
  )
  if get_option('enable-binary-tests')
    test('chan-test', chan_test_exec, args: [])
  endif
endif
