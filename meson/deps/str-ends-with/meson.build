str_ends_with_lib =library('str-ends-with',
  pwd + '/submodules/str-ends-with/src/str-ends-with.c',
  install: false, 
  dependencies: [
  ], 
  include_directories: [
    inc,
  ]
)
str_ends_with_dep = declare_dependency(include_directories: [inc], link_with: str_ends_with_lib)
