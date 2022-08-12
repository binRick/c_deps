c_timestamp_srcs = [files(
  '../../../submodules/c-timestamp/timestamp.h',
  '../../../submodules/c-timestamp/timestamp_compare.c',
  '../../../submodules/c-timestamp/timestamp_format.c',
  '../../../submodules/c-timestamp/timestamp_parse.c',
  '../../../submodules/c-timestamp/timestamp_tm.c',
  '../../../submodules/c-timestamp/timestamp_valid.c',
)]

c_timestamp_dirs = [
  '../../../submodules/c-timestamp',
  inc,
]

c_timestamp_deps = [

]

c_timestamp_lib = library('c-timestamp',
  c_timestamp_srcs,
  install: false,
  dependencies: c_timestamp_deps,
  include_directories: c_timestamp_dirs,
)

c_timestamp_dep = declare_dependency(
  include_directories: c_timestamp_dirs,
  link_with: c_timestamp_lib,
)
