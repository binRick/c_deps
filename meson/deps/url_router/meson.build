url_router_srcs = [files(
  '../../../submodules/url_router/src/dict.c',
  '../../../submodules/url_router/src/url_router.c',
  '../../../submodules/url_router/src/url_tree.c',
)]

url_router_dirs = [
  '../../../submodules/url_router',
  '../../../submodules/url_router/include',
  '../../../submodules/url_router/include/url_router',
  '../../../submodules/url_router/src',
  inc,
]

url_router_deps = [

]

url_router_lib = library('url_router',
  url_router_srcs,
  install: false,
  dependencies: url_router_deps,
  include_directories: url_router_dirs,
)

url_router_dep = declare_dependency(
  include_directories: url_router_dirs,
  link_with: url_router_lib,
)
