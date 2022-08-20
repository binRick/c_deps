c_dbg_srcs = [
    '../../../submodules/c_dbg/c_dbg.c',
]
c_dbg_dirs = [
    '../../../submodules/c_dbg',
    '../../../submodules/asprintf',
    '../../../submodules',
]
c_dbg_deps = [
    asprintf_dep,
]

c_dbg_lib = static_library('dbg', 
  c_dbg_srcs,
  install: false, 
  dependencies: c_dbg_deps,
  include_directories: c_dbg_dirs,
)
c_dbg_dep = declare_dependency(
  include_directories: c_dbg_dirs,
  link_with: c_dbg_lib,
)

dbg_dep = c_dbg_dep
