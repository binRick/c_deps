dbgp_test_srcs = [
  'dbgp-test.c',
]
dbgp_include_dirs = [
  inc,
]
dbgp_test_dbgp = [
 sdl2_dep,
 dbgp_dep,
 chan_dep,
 c_greatest_dep,
 ansi_codes_dep,
 log_dep,
 ms_dep,
 timestamp_dep,
 c_timer_dep,
 bytes_dep,  
 app_utils_dep,
 window_utils_dep,
 active_app_dep,
]

if get_option('enable-binaries')
    dbgp_test_exec = executable('dbgp-test',
     dbgp_test_srcs,
     dependencies: dbgp_test_dbgp,
     include_directories: dbgp_include_dirs,
  )
  if get_option('enable-binary-tests')
    #    test('dbgp-test', dbgp_test_exec, args: [])
  endif
endif
