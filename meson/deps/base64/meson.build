base64_srcs = [files(
  '../../../submodules/base64/base64.c',
)]

base64_dirs = [
  '../../../submodules/base64',
  inc,
]

base64_deps = [

]

base64_lib =library('base64',
  base64_srcs,
  install: false,
  dependencies: base64_deps,
  include_directories: base64_dirs,
)

base64_dep = declare_dependency(
  include_directories: base64_dirs,
  link_with: base64_lib,
)
