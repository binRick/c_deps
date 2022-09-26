sigstr_srcs = [files(
  #  '../../../submodules/sigstr/wifi_helper.c',
  '../../../submodules/sigstr/sigstr.swift',
)]

sigstr_dirs = [
  '../../../submodules/sigstr',
  inc,
]

sigstr_deps = [

]

sigstr_lib =library('sigstr',
  sigstr_srcs,
  install: false,
  dependencies: sigstr_deps,
  include_directories: sigstr_dirs,
)

sigstr_dep = declare_dependency(
  include_directories: sigstr_dirs,
  link_with: sigstr_lib,
)
