wslay_system_headers = [

]
wslay_local_headers = [
  'wslay/lib/includes/wslay/wslay.h',
  'wslay/lib/wslay_event.h',
  'wslay/lib/wslay_frame.h',
  'wslay/lib/wslay_macro.h',
  'wslay/lib/wslay_net.h',
  'wslay/lib/wslay_queue.h',
  'wslay/tests/wslay_event_test.h',
  'wslay/tests/wslay_frame_test.h',
  'wslay/tests/wslay_queue_test.h',
  'wslay/tests/wslay_session_test.h',
  'wslay/tests/wslay_stack_test.h',
]
wslay_srcs = [
  '../../../submodules/wslay/lib/wslay_event.c',
  '../../../submodules/wslay/lib/wslay_frame.c',
  '../../../submodules/wslay/lib/wslay_net.c',
  '../../../submodules/wslay/lib/wslay_queue.c',
]

wslay_dirs = [
  '../../../submodules/wslay',
  '../../../submodules/wslay/lib',
  '../../../submodules/wslay/lib/includes',
  '../../../submodules/wslay/lib/includes/wslay',
  inc,
]

wslay_c_args = [
]

wslay_deps = [

]

if wslay_srcs.length() > 0
  wslay_lib =library('wslay',
    files(wslay_srcs),
    install: false,
    dependencies: wslay_deps,
    include_directories: wslay_dirs,
    c_args: wslay_c_args,
  )
  wslay_links = [wslay_lib]
else
  wslay_links = []
endif

wslay_dep = declare_dependency(
  include_directories: wslay_dirs,
  link_with: wslay_links,
)
