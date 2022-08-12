tiny_regex_c_inc = [
  '../../../submodules/tiny-regex-c',
  inc,
]
tiny_regex_c_lib = both_libraries('tiny-regex-c', 
  '../../../submodules/tiny-regex-c/re.c',
  install: false, 
  dependencies: [
  ], 
  include_directories: tiny_regex_c_inc,
)
tiny_regex_c_dep = declare_dependency(
  include_directories: tiny_regex_c_inc,
  link_with: tiny_regex_c_lib,
)
