fort_test_srcs = [
  'fort-test.c',
]
fort_test_inc = [
 '../fort-test',
 '../submodules/libfort/src',
 '../submodules/libfort/lib',
 inc,
]
fort_test_deps = [
 fort_dep,
 dbg_dep,
 assertf_dep,
 c_fsio_dep,
 c_stringfn_dep,
 c_string_buffer_dep,
 greatest_dep,
 ansi_codes_dep,
 logh_dep,
 fort_dep,
]

if get_option('enable-binaries')
  fort_test_exec = executable('fort-test', 
     fort_test_srcs,
     dependencies: fort_test_deps,
     include_directories: fort_test_inc,
  )
  if get_option('enable-binary-tests')
    test('fort-test', fort_test_exec, args: [])
  endif
endif
