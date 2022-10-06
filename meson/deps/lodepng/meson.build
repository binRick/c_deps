lodepng_system_headers = [

]
lodepng_local_headers = [
  'lodepng/lodepng.h',
  'lodepng/lodepng_util.h',
]
lodepng_srcs = [
  '../../../submodules/lodepng/lodepng.c',
]

lodepng_dirs = [
  '../../../submodules/lodepng',
  inc,
]

lodepng_c_args = [
]

lodepng_deps = [

]

if lodepng_srcs.length() > 0
  lodepng_lib = library('lodepng',
    files(lodepng_srcs),
    install: false,
    dependencies: lodepng_deps,
    include_directories: lodepng_dirs,
    c_args: lodepng_c_args,
  )
  lodepng_links = [lodepng_lib]
else
  lodepng_links = []
endif

lodepng_dep = declare_dependency(
  include_directories: lodepng_dirs,
  link_with: lodepng_links,
)
