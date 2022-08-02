introspect_repos_srcs = [
  'introspect-repos.c',
]
introspect_repos_inc = [
 '.',
 '../introspect-repos',
 '../submodules',
 inc,
]
introspect_repos_deps = [
 reproc_dep,
 list_dep,
 ansi_codes_dep,
 c_fsio_dep,
 c_stringfn_dep,
 c_string_buffer_dep,
 assertf_dep,
 dbg_dep,
 c_greatest_dep,
 logh_dep,
 ee_dep,
 parson_dep,
 debug_memory_dep,
 tinydir_dep,
 wildcardcmp_dep,
 list_dep,
 chan_dep,
 c_timer_dep,
 rhash_md5_dep,
 b64_dep,
 c_vector_dep,
 subprocess_dep,
 path_normalize_dep,
 
 timestamp_dep,
 bytes_dep,
 tiny_regex_c_dep,
 occurrences_dep,
 ms_dep,
 which_dep,
 ctable_dep,
 progress_dep,
]
introspect_repos_cargs = [
  '-Wno-macro-redefined',
  ]

introspect_repos_lib = static_library('introspect-repos',
  introspect_repos_srcs,
  install: true,
  dependencies: introspect_repos_deps,
  c_args: introspect_repos_cargs,
  include_directories: introspect_repos_inc,
)

introspect_repos_dep = declare_dependency(
  include_directories: introspect_repos_inc,
  link_with: introspect_repos_lib,
)
