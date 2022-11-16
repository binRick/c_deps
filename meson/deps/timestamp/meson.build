
timestamp_srcs = [
  files(c_deps_dir + '/submodules/timestamp/timestamp.c'),
]

timestamp_lib_static =static_library('timestamp', timestamp_srcs,
  install: false,
  dependencies: [],
  include_directories: [inc],
)
timestamp_lib =library('timestamp', timestamp_srcs,
  install: false,
  dependencies: [],
  include_directories: [inc],
)

timestamp_dep = declare_dependency(include_directories: [inc], link_with: timestamp_lib)
