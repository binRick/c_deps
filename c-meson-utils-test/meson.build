c_meson_utils_test_srcs = [
  'c-meson-utils-test.c',
]
c_meson_utils_test_inc = [
 inc,
 '../c-meson-utils-test',
 '../c-meson-utils',
]
c_meson_utils_test_deps = [
 dbg_dep,
 assertf_dep,
 c_fsio_dep,
 c_meson_utils_dep,
 c_stringfn_dep,
 c_string_buffer_dep,
 greatest_dep,
 ansi_codes_dep,
 logh_dep,
]

if get_option('enable-binaries')
  c_meson_utils_test_exec = executable('c-meson-utils-test', 
     c_meson_utils_test_srcs,
     dependencies: c_meson_utils_test_deps,
     include_directories: c_meson_utils_test_inc,
  )
  if get_option('enable-binary-tests')
    test('meson-utils-test', c_meson_utils_test_exec, args: [])
  endif
endif
