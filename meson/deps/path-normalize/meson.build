path_normalize_lib = both_libraries('path-normalize', 
  '../../../submodules/path-normalize.c/src/path-normalize.c',
  install: false, 
  dependencies: [
    strdup_dep,
  ], 
  include_directories: [
    '../../../submodules/path-normalize.c/src',
  ]
)
path_normalize_dep = declare_dependency(include_directories: ['../../../submodules/path-normalize.c/src'], link_with: path_normalize_lib)
