fort_lib = library('fort',
  '../../../submodules/libfort/lib/fort.c',
  install: false, 
  dependencies: [
  ], 
  include_directories: [
    '../../../submodules/libfort/lib',
    '../../../submodules/libfort/src',
    inc,
  ]
)
fort_dep = declare_dependency(include_directories: [inc], link_with: fort_lib)
