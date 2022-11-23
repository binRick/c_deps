sqldbal_system_headers = [

]
sqldbal_local_headers = [
  'sqldbal/src/sqldbal.h',
]
sqldbal_srcs = [
  '../../../submodules/sqldbal/src/sqldbal.c',
]

sqldbal_dirs = [
  '../../../submodules/sqldbal',
  '../../../submodules/sqldbal/src',
  inc,
]

sqldbal_cargs = [
  '-DSQLDBAL_SQLITE',
  ]
sqldbal_deps = [

]

if sqldbal_srcs.length() > 0
  sqldbal_lib_static =static_library('sqldbal',
    files(sqldbal_srcs),
    install: false,
    dependencies: sqldbal_deps,
    include_directories: sqldbal_dirs,
    c_args: sqldbal_cargs,
  )
  sqldbal_lib =shared_library('sqldbal',
    files(sqldbal_srcs),
    install: false,
    dependencies: sqldbal_deps,
    include_directories: sqldbal_dirs,
    c_args: sqldbal_cargs,
  )
  sqldbal_links = [sqldbal_lib]
else
  sqldbal_links = []
endif

sqldbal_dep = declare_dependency(
  include_directories: sqldbal_dirs,
  link_with: sqldbal_links,
)
