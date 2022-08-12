rwimg_srcs = [files(
  '../../../submodules/rwimg/readimage.c',
  '../../../submodules/rwimg/readimage.h',
  '../../../submodules/rwimg/rwgif.c',
  '../../../submodules/rwimg/rwgif.h',
  '../../../submodules/rwimg/rwjpeg.c',
  '../../../submodules/rwimg/rwjpeg.h',
  '../../../submodules/rwimg/rwpng.c',
  '../../../submodules/rwimg/rwpng.h',
  '../../../submodules/rwimg/writeimage.c',
  '../../../submodules/rwimg/writeimage.h',
)]

rwimg_dirs = [
  '../../../submodules/rwimg',
  inc,
]

rwimg_deps = [

]

rwimg_lib = both_libraries('rwimg',
  rwimg_srcs,
  install: false,
  dependencies: rwimg_deps,
  include_directories: rwimg_dirs,
)

rwimg_dep = declare_dependency(
  include_directories: rwimg_dirs,
  link_with: rwimg_lib,
)
