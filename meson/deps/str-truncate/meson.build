str_truncate_inc = [
  '../../../submodules/str-truncate.c/src',
  inc,
]
str_truncate_lib = both_libraries('truncate', 
  '../../../submodules/str-truncate.c/src/str-truncate.c',
  install: false, 
  dependencies: [
  ], 
  include_directories: str_truncate_inc,
)
str_truncate_dep = declare_dependency(
  include_directories: str_truncate_inc,
  link_with: str_truncate_lib,
)
