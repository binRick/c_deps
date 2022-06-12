logh_lib = library('logh',
  install: false, 
  dependencies: [
    ansicodes_dep
  ], 
  include_directories: [
    inc,
  ]
)
logh_dep = declare_dependency(include_directories: [inc], link_with: logh_lib)
