icns_srcs = [
  '../../../submodules/icns/src/icns_debug.c',
  '../../../submodules/icns/src/icns_element.c',
  '../../../submodules/icns/src/icns_family.c',
  '../../../submodules/icns/src/icns_image.c',
  '../../../submodules/icns/src/icns_io.c',
  '../../../submodules/icns/src/icns_jp2.c',
  '../../../submodules/icns/src/icns_png.c',
  '../../../submodules/icns/src/icns_rle24.c',
  '../../../submodules/icns/src/icns_utils.c',
]

icns_dirs = [
  '../../../submodules/icns',
  '../../../submodules/icns/src',
  inc,
]

icns_cargs = [
  '-Wno-sign-compare','-Wno-parentheses-equality','-Wno-unused-variable','-Wno-implicit-int',
  ]
icns_deps = [
  jasper_dep,
]
if icns_srcs.length() > 0

  icns_lib =library('icns',
    files(icns_srcs),
    install: false,
    dependencies: icns_deps,
    c_args: icns_cargs,
    include_directories: icns_dirs,
  )
  icns_links = [icns_lib]
else
  icns_links = []
endif

icns_dep = declare_dependency(
  include_directories: icns_dirs,
  link_with: icns_links,
)
