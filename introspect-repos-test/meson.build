introspect_repos_test_srcs = [
  'introspect-repos-test.c',
]
introspect_repos_test_inc = [
 inc,
 '.',
 '../introspect-repos',
]
introspect_repos_test_deps = [
 reproc_dep,
 list_dep,
 ansicodes_dep,
 c_fsio_dep,
 c_stringfn_dep,
 c_string_buffer_dep,
 greatest_dep,
 ansicodes_dep,
 logh_dep,
 introspect_dep,
 parson_dep,
 ee_dep,
 debug_memory_dep,
 tinydir_dep,
 introspect_repos_dep,
]

if get_option('enable-binaries')
  introspect_repos_test_exec = executable('introspect-repos-test', 
     introspect_repos_test_srcs,
     dependencies: introspect_repos_test_deps,
     include_directories: introspect_repos_test_inc,
  )
  if get_option('enable-binary-tests')
    test('introspect-repos-test', introspect_repos_test_exec, args: [])
  endif
endif
