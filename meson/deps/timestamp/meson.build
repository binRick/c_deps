
timestamp_srcs = [
  files(pwd + '/submodules/timestamp/timestamp.c'),
]

timestamp_lib = static_library('timestamp', timestamp_srcs,
  install: false,
  dependencies: [],
  include_directories: [inc],
)

timestamp_dep = declare_dependency(include_directories: [inc], link_with: timestamp_lib)
