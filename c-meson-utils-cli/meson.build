c_meson_utils_cli_srcs = [
  'c-meson-utils-cli.c',
]
c_meson_utils_cli_inc = [
 inc,
 '../c-meson-utils-cli',
 '../c-meson-utils',
]
c_meson_utils_cli_deps = [
 dbg_dep,
 assertf_dep,
 c_fsio_dep,
 c_meson_utils_dep,
 c_stringfn_dep,
 c_string_buffer_dep,
 ansi_codes_dep,
 logh_dep,
]

if get_option('enable-binaries')
  c_meson_utils_cli_exec = executable('c-meson-utils-cli', 
     c_meson_utils_cli_srcs,
     dependencies: c_meson_utils_cli_deps,
     include_directories: c_meson_utils_cli_inc,
  )
  if get_option('enable-binary-clis')
    cli('meson-utils-cli', c_meson_utils_cli_exec, args: [])
  endif
endif
