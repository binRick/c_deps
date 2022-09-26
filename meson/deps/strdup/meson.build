
strdup_dirs = [
  inc,
  include_directories(
    '../../../submodules',
    '../../../submodules/strdup',
    ),
  ]
strdup_lib =library('strdup', 
  c_deps_dir + '/submodules/strdup/strdup.c',
  install: false, 
  dependencies: [
  ], 
  include_directories: strdup_dirs,
)
strdup_dep = declare_dependency(
  link_with: strdup_lib,
  include_directories: strdup_dirs,
)
