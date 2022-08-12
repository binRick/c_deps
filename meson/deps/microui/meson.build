microui_inc = [
  '../../../submodules/microui/src',
  '../../../submodules/microui',
  inc,
]
microui_lib = both_libraries('microui', 
  '../../../submodules/microui/src/microui.c',
  install: false, 
  dependencies: [
  ], 
  include_directories: microui_inc,
  c_args: [], #//'-L/usr/local/lib','-lSDL2'],
)
microui_dep = declare_dependency(
  include_directories: microui_inc,
  link_with: microui_lib,
)
