timestamp_lib = static_library('timestamp', 
  pwd + '/submodules/timestamp/timestamp.c',
    install: false,
  dependencies: [],
  include_directories: [inc],
)
timestamp_dep = declare_dependency(include_directories: [inc], link_with: timestamp_lib)
