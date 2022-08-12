is_number_c_srcs = [files(
  '../../../submodules/is_number.c/is_number.c',
)]

is_number_c_dirs = [
  '../../../submodules/is_number.c',
  inc,
]

is_number_c_deps = [

]

is_number_c_lib = both_libraries('is_number.c',
  is_number_c_srcs,
  install: false,
  dependencies: is_number_c_deps,
  include_directories: is_number_c_dirs,
)

is_number_c_dep = declare_dependency(
  include_directories: is_number_c_dirs,
  link_with: is_number_c_lib,
)
