font_system_headers = [

]
font_local_headers = [
  'font/demo.h',
  'font/font.h',
  'font/lib.h',
]
font_srcs = [
  '../../../submodules/font/font.c',
  '../../../submodules/font/lib.c',
]

font_dirs = [
  '../../../submodules/font',
  inc,
]

font_deps = [

]
if font_srcs.length() > 0

  font_lib = static_library('font',
    files(font_srcs),
    install: false,
    dependencies: font_deps,
    include_directories: font_dirs,
  )
  font_links = [font_lib]
else
  font_links = []
endif

font_dep = declare_dependency(
  include_directories: font_dirs,
  link_with: font_links,
)
