roscha_srcs = [files(
  '../../../submodules/roscha/include/sds/sds.c',
  '../../../submodules/roscha/src/ast.c',
  '../../../submodules/roscha/src/hmap.c',
  '../../../submodules/roscha/src/lexer.c',
  '../../../submodules/roscha/src/object.c',
  '../../../submodules/roscha/src/parser.c',
  '../../../submodules/roscha/src/roscha.c',
  '../../../submodules/roscha/src/slice.c',
  '../../../submodules/roscha/src/token.c',
  '../../../submodules/roscha/src/vector.c',
)]

roscha_dirs = [
  '../../../submodules/roscha',
  '../../../submodules/roscha/include',
  '../../../submodules/roscha/include/sds',
  '../../../submodules/roscha/src',
  inc,
]

roscha_deps = [

]

roscha_lib =library('roscha',
  roscha_srcs,
  install: false,
  dependencies: roscha_deps,
  include_directories: roscha_dirs,
)

roscha_dep = declare_dependency(
  include_directories: roscha_dirs,
  link_with: roscha_lib,
)
