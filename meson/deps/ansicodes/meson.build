ansicodes_lib = static_library('ansicodes', 
  meson_deps_dir+'/submodules/c_ansi/ansi-codes/ansi-codes.c',
  install: false, 
  dependencies: [
  ], 
  include_directories: [
    inc,
  ]
)
ansi_codes_dep = declare_dependency(
  include_directories: [
    inc,
  ], 
  link_with: ansicodes_lib,
)
