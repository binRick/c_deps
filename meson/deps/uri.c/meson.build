uri_c_srcs = [files(
  '../../../submodules/uri.c/decode.c',
  '../../../submodules/uri.c/encode.c',
)]

uri_c_dirs = [
  '../../../submodules/uri.c',
  inc,
]

uri_c_args = [
  '-Wno-sign-compare',
  ]
uri_c_deps = [

]

uri_c_lib =library('uri.c',
  uri_c_srcs,
  install: false,
  dependencies: uri_c_deps,
  include_directories: uri_c_dirs,
  c_args: uri_c_args,
)

uri_c_dep = declare_dependency(
  include_directories: uri_c_dirs,
  link_with: uri_c_lib,
)
