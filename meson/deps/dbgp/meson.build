dbgp_lib = static_library('dbgp', 
  meson_deps_dir+'/submodules/SDL_DBGP/SDL_DBGP.c',
  install: false, dependencies: [
    sdl2_dep,
  ], 
  include_directories: [
    inc,
  ]
)
dbgp_dep = declare_dependency(include_directories: [
    inc,
  ], 
  link_with: dbgp_lib
)
