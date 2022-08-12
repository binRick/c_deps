sqldbal_srcs = [files(
  '../../../submodules/sqldbal/src/sqldbal.c',
  '../../../submodules/sqldbal/src/sqldbal.h',
)]

sqldbal_dirs = [
  '../../../submodules/sqldbal',
  '../../../submodules/sqldbal/src',
  inc,
]

sqldbal_deps = [

]
sqldbal_link_args = [
    '-lsqlite3',
]
sqldbal_c_args = [
    '-DSQLDBAL_SQLITE',
]

sqldbal_lib = library('sqldbal',
  sqldbal_srcs,
  install: false,
  dependencies: sqldbal_deps,
  link_args: sqldbal_link_args,
  c_args: sqldbal_c_args,
  include_directories: sqldbal_dirs,
)

sqldbal_dep = declare_dependency(
  include_directories: sqldbal_dirs,
  link_with: sqldbal_lib,
)
