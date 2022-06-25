greatest_dirs = [
  '../../../submodules/greatest',
  ]
greatest_lib = library('greatest', 
  install: false, dependencies: [], 
  include_directories: greatest_dirs,
)
greatest_dep = declare_dependency(include_directories: greatest_dirs, link_with: greatest_lib)
