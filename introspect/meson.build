introspect_srcs = [
  'introspect.c',
]
introspect_inc = [
 inc,
 '.',
 '../introspect',
]
introspect_deps = [
 reproc_dep,
 list_dep,
 c_fsio_dep,
 c_stringfn_dep,
 c_string_buffer_dep,
 c_greatest_dep,
 ansi_codes_dep,
 logh_dep,
 ee_dep,
 parson_dep,
 debug_memory_dep,
]


introspect_lib = static_library('introspect',
  introspect_srcs,
  install: false,
  dependencies: introspect_deps,
  include_directories: [
    introspect_inc,
  ],
)

introspect_dep = declare_dependency(
  include_directories: introspect_inc,
  link_with: introspect_lib,
)
