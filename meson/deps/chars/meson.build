chars_srcs = [files(
  '../../../submodules/chars/chars/c_escape.c',
  '../../../submodules/chars/chars/case_convert.c',
  '../../../submodules/chars/chars/char_class.c',
  '../../../submodules/chars/chars/elide.c',
  '../../../submodules/chars/chars/quote.c',
  '../../../submodules/chars/chars/uint8_convert.c',
  '../../../submodules/chars/chars/url_encode.c',
)]

chars_dirs = [
  '../../../submodules/chars',
  '../../../submodules/chars/chars',
  inc,
]

chars_deps = [

]

chars_lib =library('chars',
  chars_srcs,
  install: false,
  dependencies: chars_deps,
  include_directories: chars_dirs,
)

chars_dep = declare_dependency(
  include_directories: chars_dirs,
  link_with: chars_lib,
)
