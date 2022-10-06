pngquant_system_headers = [

]
pngquant_local_headers = [
  'pngquant/pngquant_opts.h',
  'pngquant/rwpng.h',
]
pngquant_srcs = [
  '../../../submodules/pngquant/pngquant.c',
  '../../../submodules/pngquant/pngquant_opts.c',
  '../../../submodules/pngquant/rwpng.c',
]

pngquant_dirs = [
  '../../../submodules/pngquant',
  '../../../submodules/pngquant/lib',
  '../../../submodules/pngquant/rust',
  inc,
]

pngquant_c_args = [
  '-Wno-unused-parameter',
]

pngquant_deps = [
  imagequant_dep,
]

if pngquant_srcs.length() > 0
  pngquant_lib = library('pngquant',
    files(pngquant_srcs),
    install: false,
    dependencies: pngquant_deps,
    include_directories: pngquant_dirs,
    c_args: pngquant_c_args,
  )
  pngquant_links = [pngquant_lib]
else
  pngquant_links = []
endif

pngquant_dep = declare_dependency(
  include_directories: pngquant_dirs,
  link_with: pngquant_links,
)
