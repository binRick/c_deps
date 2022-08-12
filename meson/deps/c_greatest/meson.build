c_greatest_dirs = [
  '../../../submodules/c_greatest',
  inc,
  ]
c_greatest_deps = [
      parson_dep,
  ]
c_greatest_files = [
  '../../../submodules/c_greatest/greatest/greatest.c',
]

c_greatest_lib = library('c_greatest',
  c_greatest_files,
  install: false,
  dependencies: c_greatest_deps,
  include_directories: c_greatest_dirs,
)

c_greatest_dep = declare_dependency(
  include_directories: c_greatest_dirs,
  link_with: c_greatest_lib,
)

