introspect_repos_test_srcs = [
  'introspect-repos-test.c',
]
introspect_repos_test_inc = [
 '.',
 '../introspect-repos',
 inc,
]
introspect_repos_test_deps = [
 reproc_dep,sqlite3_dep,c_vector_dep,
 list_dep,
 c_fsio_dep,
 c_stringfn_dep,
 c_string_buffer_dep,
 c_greatest_dep,
 ansi_codes_dep,
 log_dep,
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
     install: true,
  )
  if get_option('enable-binary-tests')
    test('introspect-repos-test', passh_program, args: [introspect_repos_test_exec,'-v','-a'])
  endif
endif
