SDL_QOI_system_headers = [

]
SDL_QOI_local_headers = [
  'SDL_QOI/SDL_QOI.h',
]
SDL_QOI_srcs = [
  '../../../submodules/SDL_QOI/SDL_QOI.c',
]

SDL_QOI_dirs = [
  '../../../submodules/SDL_QOI',
  inc,
]

SDL_QOI_c_args = [
]

SDL_QOI_deps = [
  qoi_dep,
  sdl2_dep,

]

if SDL_QOI_srcs.length() > 0
  SDL_QOI_lib = library('SDL_QOI',
    files(SDL_QOI_srcs),
    install: false,
    dependencies: SDL_QOI_deps,
    include_directories: SDL_QOI_dirs,
    c_args: SDL_QOI_c_args,
  )
  SDL_QOI_links = [SDL_QOI_lib]
else
  SDL_QOI_links = []
endif

sdl_qoi_dep = declare_dependency(
  include_directories: SDL_QOI_dirs,
  link_with: SDL_QOI_links,
)
