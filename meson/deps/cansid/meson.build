cansid_lib = static_library('cansid',
  pwd + '/submodules/cansid/cansid.c',
  install: false, 
  dependencies: [
  ], 
  include_directories: [
    inc,
  ]
)
cansid_dep = declare_dependency(include_directories: [inc], link_with: cansid_lib)
