imagequant_test_srcs = [
  'imagequant-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
imagequant_test_include_dirs = [
  '.',
  inc,
]
imagequant_test_deps = [
  imagequant_dep,
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
]
imagequant_test_c_args = [
]
imagequant_test_link_args = [
]

imagequant_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  imagequant_test_exec = executable('imagequant-test',
     imagequant_test_srcs,
     dependencies: imagequant_test_deps,
     include_directories: imagequant_test_include_dirs,
     link_args: imagequant_test_link_args,
     c_args: imagequant_test_c_args,
     install: false,
  )
  test('imagequant-test', 
    imagequant_test_exec, args: ['-v','-a'],
    workdir: imagequant_test_test_dir,
  )
endif
