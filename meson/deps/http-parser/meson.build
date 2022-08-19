http_parser_srcs = [
  '../../../submodules/http-parser/http_parser.c',
]

http_parser_dirs = [
  '../../../submodules/http-parser',
  inc,
]

http_parser_deps = [

]

http_parser_lib = static_library('http-parser',
  http_parser_srcs,
  install: false,
  dependencies: http_parser_deps,
  include_directories: http_parser_dirs,
)

http_parser_dep = declare_dependency(
  include_directories: http_parser_dirs,
  link_with: http_parser_lib,
)
