libtermkey_srcs = [
  'libtermkey-test.c',
]
libtermkey_inc = [
 inc,
 '.',
]
libtermkey_deps = [
 reproc_dep,
 libtermkey_dep,
 ansi_codes_dep,
 c_fsio_dep,
 c_stringfn_dep,
 c_vector_dep,
 tempdir_dep,
 which_dep,
 timestamp_dep,
 ansi_utils_dep,
 #debug_memory_dep,
 c_string_buffer_dep,
 log_dep,
]

  deps_test_exec = executable('libtermkey-test',
     libtermkey_srcs,
     dependencies: libtermkey_deps,
     include_directories: libtermkey_inc,
     link_args: [
       '-lcurses',
       ],
     c_args: [],
     install: false,
  )
