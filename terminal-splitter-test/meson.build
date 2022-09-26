terminal_splitter_test_srcs = [
  'terminal-splitter-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
terminal_splitter_test_include_dirs = [
  '.',
  inc,
]
terminal_splitter_test_deps = [
  c_greatest_dep,
  ansi_codes_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  c_string_buffer_dep,
  timestamp_dep,
  log_dep,
  ms_dep,
  terminalSplitter_dep,
  curses_dep,
  bytes_dep,
]
terminal_splitter_test_c_args = [
]
terminal_splitter_test_link_args = [
]

terminal_splitter_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  terminal_splitter_test_exec = executable('terminal-splitter-test',
     terminal_splitter_test_srcs,
     dependencies: terminal_splitter_test_deps,
     include_directories: terminal_splitter_test_include_dirs,
     link_args: terminal_splitter_test_link_args,
     c_args: terminal_splitter_test_c_args,
     install: false,
  )
  test('terminal-splitter-test', 
    terminal_splitter_test_exec, args: ['-v','-a'],
    workdir: terminal_splitter_test_test_dir,
  )
endif
