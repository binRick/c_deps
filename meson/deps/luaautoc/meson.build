luaautoc_system_headers = [

]
luaautoc_local_headers = [
  'luaautoc/lautoc.h',
  'luaautoc/lautocall.h',
]
luaautoc_srcs = [
  '../../../submodules/luaautoc/lautoc.c',
]

luaautoc_dirs = [
  '../../../submodules/luaautoc',
  inc,
]

luaautoc_c_args = [
]

luaautoc_deps = [
  lua_dep,
]

if luaautoc_srcs.length() > 0
  luaautoc_lib = library('luaautoc',
    files(luaautoc_srcs),
    install: false,
    dependencies: luaautoc_deps,
    include_directories: luaautoc_dirs,
    c_args: luaautoc_c_args,
  )
  luaautoc_links = [luaautoc_lib]
else
  luaautoc_links = []
endif

luaautoc_dep = declare_dependency(
  include_directories: luaautoc_dirs,
  link_with: luaautoc_links,
)
