base64_simple_srcs = [files(
  '../../../submodules/base64_simple/src/libbase64simple.c',
)]

base64_simple_dirs = [
  '../../../submodules/base64_simple',
  inc,
]

base64_simple_deps = [

]

base64_simple_lib = static_library('base64_simple',
  base64_simple_srcs,
  install: false,
  dependencies: base64_simple_deps,
  include_directories: base64_simple_dirs,
)

base64_simple_dep = declare_dependency(
  include_directories: base64_simple_dirs,
  link_with: base64_simple_lib,
)
