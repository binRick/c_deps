microui_inc = [
  '../../../submodules/microui/src',
  '../../../submodules/microui',
  inc,
]
microui_lib = static_library('microui', 
  '../../../submodules/microui/src/microui.c',
  install: false, 
  dependencies: [
    sdl2_dep,
    sdl2_ttf_dep,
  ], 
  include_directories: microui_inc,
  c_args: [],
)
microui_dep = declare_dependency(
  include_directories: microui_inc,
  link_with: microui_lib,
)
