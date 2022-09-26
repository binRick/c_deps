c_liamloads_srcs = [

]

c_liamloads_dirs = [
  '../../../submodules/c_liamloads',
  inc,
]

c_liamloads_deps = [

]
if c_liamloads_srcs.length() > 0

  c_liamloads_lib =library('c_liamloads',
    files(c_liamloads_srcs),
    install: false,
    dependencies: c_liamloads_deps,
    include_directories: c_liamloads_dirs,
  )
  c_liamloads_links = [c_liamloads_lib]
else
  c_liamloads_links = []
endif

c_liamloads_dep = declare_dependency(
  include_directories: c_liamloads_dirs,
  link_with: c_liamloads_links,
)
