str_truncate_inc = [
  '../../../submodules/str-truncate.c/src',
  inc,
]
str_c_args = [
  '-Wno-sign-compare',
  ]
str_truncate_lib =library('truncate', 
  '../../../submodules/str-truncate.c/src/str-truncate.c',
  install: false, 
  dependencies: [
  ], 
  include_directories: str_truncate_inc,
  c_args: str_c_args,
)
str_truncate_dep = declare_dependency(
  include_directories: str_truncate_inc,
  link_with: str_truncate_lib,
)
