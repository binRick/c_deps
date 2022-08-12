url_h_drcs = [files(
  '../../../submodules/url.h/url.c',
)]

url_h_dirs = [
  '../../../submodules/url.h',
  inc,
]

url_h_deps = [

]

url_h_lib = library('url-h',
  url_h_drcs,
  install: false,
  dependencies: url_h_deps,
  include_directories: url_h_dirs,
)

url_h_dep = declare_dependency(
  include_directories: url_h_dirs,
  link_with: url_h_lib,
)
