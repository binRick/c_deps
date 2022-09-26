c_greatest_system_headers = [

]
c_greatest_local_headers = [
  'c_greatest/greatest/greatest.h',
]
c_greatest_srcs = [

]

c_greatest_dirs = [
  '../../../submodules/c_greatest',
  inc,
]

c_greatest_deps = [

]

if c_greatest_srcs.length() > 0
  c_greatest_lib =library('c_greatest',
    files(c_greatest_srcs),
    install: false,
    dependencies: c_greatest_deps,
    include_directories: c_greatest_dirs,
  )
  c_greatest_links = [c_greatest_lib]
else
  c_greatest_links = []
endif

c_greatest_dep = declare_dependency(
  include_directories: c_greatest_dirs,
  link_with: c_greatest_links,
)
