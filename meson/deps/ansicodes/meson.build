ansicodes_lib =library('ansicodes', 
  c_deps_dir+'/submodules/c_ansi/ansi-codes/ansi-codes.c',
  install: false, 
  dependencies: [
  ], 
  include_directories: [
    inc,
    '../../../submodules/c_ansi/ansi-utils',
  ]
)
ansicodes_lib_static =static_library('ansicodes', 
  c_deps_dir+'/submodules/c_ansi/ansi-codes/ansi-codes.c',
  install: false, 
  dependencies: [
  ], 
  include_directories: [
    inc,
    '../../../submodules/c_ansi/ansi-utils',
  ]
)
ansi_codes_dep = declare_dependency(
  include_directories: [
    '../../../submodules/c_ansi/ansi-utils',
    inc,
  ], 
  link_with: ansicodes_lib,
)
