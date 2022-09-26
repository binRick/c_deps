ui_test_srcs = [
  'ui-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
ui_test_include_dirs = [
  '.',
  '../c-go-interface',
  '../c-go-interface/go-ui',
  inc,
]
ui_test_deps = [
  c_greatest_dep,
  ansi_codes_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  c_string_buffer_dep,
  timestamp_dep,
  log_dep,
  ms_dep,
  bytes_dep,
  ui_dep,
]
ui_test_c_args = [
]
ui_test_link_args = [
]

ui_test_test_dir = join_paths(meson.current_source_dir(), '..')
ui_objects = ['c-go-interface/go-ui/libui.a']

if get_option('enable-binaries')
  ui_test_exec = executable('ui-test',
     ui_test_srcs,
     dependencies: ui_test_deps,
     include_directories: ui_test_include_dirs,
     link_args: ui_test_link_args,
     c_args: ui_test_c_args,
     #link_with: ui_objects,
     link_whole: ui_objects,
     #objects: ui_objects,
     #     link_with: ui_lib,
     install: false,
  )
  test('ui-test', 
    ui_test_exec, args: ['-v','-a'],
    workdir: ui_test_test_dir,
  )
endif
