gifdec_system_headers = [

]
gifdec_local_headers = [
  'gifdec/gifdec.h',
]
gifdec_srcs = [
  '../../../submodules/gifdec/gifdec.c',
]

gifdec_dirs = [
  '../../../submodules/gifdec',
  inc,
]

gifdec_c_args = [
]

gifdec_deps = [

]

if gifdec_srcs.length() > 0
  gifdec_lib = library('gifdec',
    files(gifdec_srcs),
    install: false,
    dependencies: gifdec_deps,
    include_directories: gifdec_dirs,
    c_args: gifdec_c_args,
  )
  gifdec_links = [gifdec_lib]
else
  gifdec_links = []
endif

gifdec_dep = declare_dependency(
  include_directories: gifdec_dirs,
  link_with: gifdec_links,
)
