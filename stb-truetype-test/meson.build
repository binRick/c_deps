stb_truetype_test_srcs = [
  'stb-truetype-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
stb_truetype_test_include_dirs = [
  '.',
  inc,
]
stb_truetype_test_deps = [
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
  stb_dep,
  incbin_dep,tempdir_dep,
]
stb_truetype_test_c_args = [
  '-DSTB_TRUETYPE_IMPLEMENTATION',
  '-DINCBIN_SILENCE_BITCODE_WARNING',
  '-DINCBIN_STYLE=INCBIN_STYLE_SNAKE',
]
stb_truetype_test_link_args = [
]

stb_truetype_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  stb_truetype_test_exec = executable('stb-truetype-test',
     stb_truetype_test_srcs,
     dependencies: stb_truetype_test_deps,
     include_directories: stb_truetype_test_include_dirs,
     link_args: stb_truetype_test_link_args,
     c_args: stb_truetype_test_c_args,
     install: false,
  )
  test('stb-truetype-test', 
    stb_truetype_test_exec, args: ['-v','-a'],
    workdir: stb_truetype_test_test_dir,
  )
endif
