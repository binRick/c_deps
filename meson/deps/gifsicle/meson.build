gifsicle_srcs = [files(
  '../../../submodules/gifsicle/src/optimize.c',
  '../../../submodules/gifsicle/include/lcdf/clp.h',
  '../../../submodules/gifsicle/include/lcdf/inttypes.h',
  '../../../submodules/gifsicle/include/lcdfgif/gif.h',
  '../../../submodules/gifsicle/include/lcdfgif/gifx.h',
  '../../../submodules/gifsicle/src/clp.c',
  '../../../submodules/gifsicle/src/fmalloc.c',
  '../../../submodules/gifsicle/src/gifdiff.c',
  '../../../submodules/gifsicle/src/giffunc.c',
  '../../../submodules/gifsicle/src/gifread.c',
  '../../../submodules/gifsicle/src/gifsicle.c',
  '../../../submodules/gifsicle/src/gifsicle.h',
  '../../../submodules/gifsicle/src/giftoc.c',
  '../../../submodules/gifsicle/src/gifunopt.c',
  '../../../submodules/gifsicle/src/gifview.c',
  '../../../submodules/gifsicle/src/gifwrite.c',
  '../../../submodules/gifsicle/src/gifx.c',
  '../../../submodules/gifsicle/src/kcolor.h',
  '../../../submodules/gifsicle/src/merge.c',
  '../../../submodules/gifsicle/src/opttemplate.c',
  '../../../submodules/gifsicle/src/quantize.c',
  '../../../submodules/gifsicle/src/strerror.c',
  '../../../submodules/gifsicle/src/support.c',
  '../../../submodules/gifsicle/src/ungifwrt.c',
  '../../../submodules/gifsicle/src/win32cfg.h',
  '../../../submodules/gifsicle/src/xform.c',
)]

gifsicle_dirs = [
  '../../../submodules/gifsicle',
  '../../../submodules/gifsicle/include',
  '../../../submodules/gifsicle/include/lcdf',
  '../../../submodules/gifsicle/include/lcdfgif',
  '../../../submodules/gifsicle/src',
  inc,
]

gifsicle_deps = [

]

gifsicle_lib = static_library('gifsicle',
  gifsicle_srcs,
  install: false,
  dependencies: gifsicle_deps,
  include_directories: gifsicle_dirs,
)

gifsicle_dep = declare_dependency(
  include_directories: gifsicle_dirs,
  link_with: gifsicle_lib,
)
