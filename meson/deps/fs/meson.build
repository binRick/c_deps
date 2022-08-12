fs_lib = library('fs', 
  '../../../submodules/fs.c/fs.c',
  install: false, 
  dependencies: [], 
  include_directories: [
    inc,
  ]
)
fs_dep = declare_dependency(
  include_directories: [
    inc,
  ], link_with: fs_lib,
)
