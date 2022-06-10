ansicodes_lib = static_library('ansicodes', 
  '../../../submodules/c_ansi/ansi-codes/ansi-codes.c',
  install: false, 
  dependencies: [
  ], 
  include_directories: [
    '../../../submodules/c_ansi/ansi-codes',
  ]
)
ansicodes_dep = declare_dependency(
  include_directories: [
    '../../../submodules/c_ansi/ansi-codes',
  ], 
  link_with: ansicodes_lib,
)
