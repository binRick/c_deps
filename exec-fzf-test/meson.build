exec_fzf_test_srcs = [
  'exec-fzf-test.c',
]
exec_fzf_test_inc = [
 '../exec-fzf-test',
 '../exec-fzf',
 inc,
]
exec_fzf_test_deps = [
 reproc_dep,
 list_dep,
 ansi_codes_dep,
 c_fsio_dep,
 c_stringfn_dep,
 c_vector_dep,
 exec_fzf_dep,
 tempdir_dep,
 which_dep,
 timestamp_dep,
 ansi_utils_dep,
 debug_memory_dep,
 c_string_buffer_dep,
 greatest_dep,
 logh_dep,
]

if get_option('enable-binaries')
  exec_fzf_test_exec = executable('exec-fzf-test', 
     exec_fzf_test_srcs,
     dependencies: exec_fzf_test_deps,
     include_directories: exec_fzf_test_inc,
  )
  if get_option('enable-binary-tests')
    test('exec-fzf-test', exec_fzf_test_exec, args: [])
  endif
endif
