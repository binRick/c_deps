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
]

pngquant_deps = [

]

imagequant_dep = dependency('imagequant', method: 'pkg-config', required : true)
