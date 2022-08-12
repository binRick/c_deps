httpd_srcs = [files(
  '../../../submodules/httpd/httpd.c',
)]

httpd_dirs = [
  '../../../submodules/httpd',
  inc,
]

httpd_deps = [

]

httpd_lib = library('httpd',
  httpd_srcs,
  install: false,
  dependencies: httpd_deps,
  include_directories: httpd_dirs,
)

httpd_dep = declare_dependency(
  include_directories: httpd_dirs,
  link_with: httpd_lib,
)
