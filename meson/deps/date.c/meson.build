date_c_srcs = [files(
  '../../../submodules/date.c/date.c',
)]

date_c_dirs = [
  '../../../submodules/date.c',
  inc,
]

date_c_deps = [

]

date_c_lib =library('date-c',
  date_c_srcs,
  install: false,
  dependencies: date_c_deps,
  include_directories: date_c_dirs,
)

date_c_dep = declare_dependency(
  include_directories: date_c_dirs,
  link_with: date_c_lib,
)
