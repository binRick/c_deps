chan_test_srcs = [
  'chan-test.c',
]
chan_test_inc = [
 inc,
]
chan_test_deps = [
 chan_dep,
 c_greatest_dep,
 ansi_codes_dep,
 log_dep,
 ms_dep,
 timestamp_dep,
 c_timer_dep,
 bytes_dep,
 async_dep,
 match_dep,
 c_vector_dep,
 log_dep,
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
