tmt_test_srcs = [
  'tmt-test.c',
]
tmt_test_inc = [
 inc,
 '../submodules/libtmt',
]
tmt_test_deps = [
 tmt_dep,
 tmt_dep,
 ansicodes_dep,
 c_fsio_dep,
 c_stringfn_dep,
 c_string_buffer_dep,
 greatest_dep,
 ansicodes_dep,
 logh_dep,
 tmt_dep,
]

if get_option('enable-binaries')
  tmt_test_exec = executable('tmt-test', 
     tmt_test_srcs,
     dependencies: tmt_test_deps,
     include_directories: tmt_test_inc,
  )
  if get_option('enable-binary-tests')
    #    test('tmt-test', tmt_test_exec, args: [])
  endif
endif
