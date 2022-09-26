knock_srcs = [files(
  '../../../submodules/knock/config.h',
)]

knock_dirs = [
  '../../../submodules/knock',
  '../../../submodules/knock/src',
  inc,
]

knock_deps = [
  pcap_dep,

]

knock_lib =library('knock',
  knock_srcs,
  install: false,
  dependencies: knock_deps,
  include_directories: knock_dirs,
)

knock_dep = declare_dependency(
  include_directories: knock_dirs,
  link_with: knock_lib,
)
