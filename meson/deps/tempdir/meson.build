tempdir_dirs = [
  inc,
  ]
tempdir_lib =library('tempdir', 
  c_deps_dir + '/submodules/tempdir.c/tempdir.c',
  install: false, 
  dependencies: [],
  include_directories: tempdir_dirs,
)
tempdir_dep = declare_dependency(include_directories: inc,
link_with: tempdir_lib)
