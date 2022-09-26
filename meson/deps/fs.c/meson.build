fs_c_system_headers = [

]
fs_c_local_headers = [
  'fs.c/fs.h',
]
fs_c_srcs = [
  '../../../submodules/fs.c/fs.c',
]

fs_c_dirs = [
  '../../../submodules/fs.c',
  '../../../submodules/fs.c/tmp',
  inc,
]

fs_c_c_args = [
]

fs_c_deps = [

]

if fs_c_srcs.length() > 0
  fs_c_lib =library('fs.c',
    files(fs_c_srcs),
    install: false,
    dependencies: fs_c_deps,
    include_directories: fs_c_dirs,
    c_args: fs_c_c_args,
  )
  fs_c_links = [fs_c_lib]
else
  fs_c_links = []
endif

fs_c_dep = declare_dependency(
  include_directories: fs_c_dirs,
  link_with: fs_c_links,
)
