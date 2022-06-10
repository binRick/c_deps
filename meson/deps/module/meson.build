module_lib = library('module', 
  '../../../submodules/module/def.h',
  '../../../submodules/module/module.h',
  '../../../submodules/module/require.h',
  install: false, 
  dependencies: [
  ], 
  include_directories: [
  ]
)
module_dep = declare_dependency(
  include_directories: [
    '../../../submodules/module',
  ],
  link_with: module_lib,
)
