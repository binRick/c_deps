libnsgif_system_headers = [

]
libnsgif_local_headers = [
  'libnsgif/include/nsgif.h',
  'libnsgif/src/lzw.h',
  'libnsgif/test/cli.h',
]
libnsgif_srcs = [
  '../../../submodules/libnsgif/src/gif.c',
  '../../../submodules/libnsgif/src/lzw.c',
]

libnsgif_dirs = [
  '../../../submodules/libnsgif',
  '../../../submodules/libnsgif/include',
  '../../../submodules/libnsgif/src',
  inc,
]

libnsgif_c_args = [
]

libnsgif_deps = [

]

if libnsgif_srcs.length() > 0
  libnsgif_lib = library('libnsgif',
    files(libnsgif_srcs),
    install: false,
    dependencies: libnsgif_deps,
    include_directories: libnsgif_dirs,
    c_args: libnsgif_c_args,
  )
  libnsgif_links = [libnsgif_lib]
else
  libnsgif_links = []
endif

libnsgif_dep = declare_dependency(
  include_directories: libnsgif_dirs,
  link_with: libnsgif_links,
)
