confuse_lib = both_libraries('libconfuse',
  '../../../submodules/libconfuse/src/confuse.c',
  install: false, 
  dependencies: [
  ], 
  include_directories: [
  '../../../submodules/libconfuse/src',
    inc,
  ]
)
confuse_dep = declare_dependency(include_directories: [
  inc,
  '../../../submodules/libconfuse/src',
  ], link_with: confuse_lib)
