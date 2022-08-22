yabai_srcs = [files(
  '../../../submodules/yabai/src/application.c',
  '../../../submodules/yabai/src/application.h',
  '../../../submodules/yabai/src/border.c',
  '../../../submodules/yabai/src/border.h',
  '../../../submodules/yabai/src/display.c',
  '../../../submodules/yabai/src/display.h',
  '../../../submodules/yabai/src/display_manager.c',
  '../../../submodules/yabai/src/display_manager.h',
  '../../../submodules/yabai/src/event.c',
  '../../../submodules/yabai/src/event.h',
  '../../../submodules/yabai/src/event_loop.c',
  '../../../submodules/yabai/src/event_loop.h',
  '../../../submodules/yabai/src/event_signal.c',
  '../../../submodules/yabai/src/event_signal.h',
  '../../../submodules/yabai/src/event_tap.c',
  '../../../submodules/yabai/src/event_tap.h',
  '../../../submodules/yabai/src/message.c',
  '../../../submodules/yabai/src/message.h',
  '../../../submodules/yabai/src/misc/autorelease.h',
  '../../../submodules/yabai/src/misc/hashtable.h',
  '../../../submodules/yabai/src/misc/helpers.h',
  '../../../submodules/yabai/src/misc/log.h',
  '../../../submodules/yabai/src/misc/macros.h',
  '../../../submodules/yabai/src/misc/memory_pool.h',
  '../../../submodules/yabai/src/misc/notify.h',
  '../../../submodules/yabai/src/misc/sbuffer.h',
  '../../../submodules/yabai/src/misc/ts.h',
  '../../../submodules/yabai/src/mission_control.c',
  '../../../submodules/yabai/src/mouse.c',
  '../../../submodules/yabai/src/mouse.h',
  '../../../submodules/yabai/src/osax/common.h',
  '../../../submodules/yabai/src/process_manager.c',
  '../../../submodules/yabai/src/process_manager.h',
  '../../../submodules/yabai/src/rule.c',
  '../../../submodules/yabai/src/rule.h',
  '../../../submodules/yabai/src/sa.h',
  '../../../submodules/yabai/src/space.c',
  '../../../submodules/yabai/src/space.h',
  '../../../submodules/yabai/src/space_manager.c',
  '../../../submodules/yabai/src/space_manager.h',
  '../../../submodules/yabai/src/view.c',
  '../../../submodules/yabai/src/view.h',
  '../../../submodules/yabai/src/window.c',
  '../../../submodules/yabai/src/window.h',
  '../../../submodules/yabai/src/window_manager.c',
  '../../../submodules/yabai/src/window_manager.h',
  '../../../submodules/yabai/src/workspace.h',
)]

yabai_dirs = [
  '../../../submodules/yabai',
  '../../../submodules/yabai/doc',
  '../../../submodules/yabai/src',
  '../../../submodules/yabai/src/misc',
  '../../../submodules/yabai/src/osax',
  inc,
]

yabai_deps = [

]

yabai_lib = both_libraries('yabai',
  yabai_srcs,
  install: false,
  dependencies: yabai_deps,
  include_directories: yabai_dirs,
)

yabai_dep = declare_dependency(
  include_directories: yabai_dirs,
  link_with: yabai_lib,
)
