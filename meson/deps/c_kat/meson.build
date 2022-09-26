c_kat_lib =library('c_kat', 
  '../../../submodules/c_kat/hashtable.c',
  '../../../submodules/c_kat/highlight.c',
  install: false, 
  dependencies: [], 
  include_directories: [
    '../../../submodules/c_kat',
    '../../../submodules/c_kat/include',
  ]
)
c_kat_dep = declare_dependency(
  include_directories: [
    '../../../submodules/c_kat',
    '../../../submodules/c_kat/include',
  ], 
  link_with: c_kat_lib,
)
