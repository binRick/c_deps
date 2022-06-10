
c_stringfn_lib = static_library('c_stringfn', 
  '../../../submodules/c_stringfn/src/stringfn.c',
  install: false, 
  dependencies: [
  ], 
  include_directories: [
    '../../../submodules/c_stringfn/include',
  ]
)

c_stringfn_dep = declare_dependency(
  include_directories: [
    '../../../submodules/c_stringfn/include',
  ], 
  link_with: c_stringfn_lib,
)
