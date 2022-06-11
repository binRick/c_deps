wildcardcmp_lib = static_library('wildcardcmp',
  pwd + '/submodules/wildcardcmp/src/wildcardcmp.c',
  install: false, 
  dependencies: [
  ], 
  include_directories: [
    inc,
  ]
)
wildcardcmp_dep = declare_dependency(include_directories: [inc], link_with: wildcardcmp_lib)
