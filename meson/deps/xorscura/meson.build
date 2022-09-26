xorscura_srcs = [
  '../../../submodules/xorscura/libxorscura.c',
  '../../../submodules/xorscura/xorscura.c',
]

xorscura_dirs = [
  '../../../submodules/xorscura',
  inc,
]

xorscura_deps = [

]
if xorscura_srcs.length() > 0

  xorscura_lib =library('xorscura',
    files(xorscura_srcs),
    install: false,
    dependencies: xorscura_deps,
    include_directories: xorscura_dirs,
  )
  xorscura_links = [xorscura_lib]
else
  xorscura_links = []
endif

xorscura_dep = declare_dependency(
  include_directories: xorscura_dirs,
  link_with: xorscura_links,
)
