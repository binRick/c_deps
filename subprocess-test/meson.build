subprocess_test_srcs = [
  'subprocess-test.c',
]
subprocess_test_inc = [
 inc,
 '../subprocess-test',
 '../submodules/subprocess.h',
]
subprocess_test_deps = [
 subprocess_dep,
 dbg_dep,
 assertf_dep,
 c_fsio_dep,
 c_stringfn_dep,
 c_string_buffer_dep,
 c_greatest_dep,
 ansi_codes_dep,
 log_dep,
 subprocess_dep,
]

if get_option('enable-binaries')
  subprocess_test_exec = executable('subprocess-test', 
     subprocess_test_srcs,
     dependencies: subprocess_test_deps,
     include_directories: subprocess_test_inc,
  )
  if get_option('enable-binary-tests')
    test('subprocess-test', subprocess_test_exec, args: [])
  endif
endif
