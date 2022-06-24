chan_c_args = [
  '-Wno-macro-redefined',
]
chan_lib = static_library('chan', 
    '../../../submodules/chan/src/chan.c',
    '../../../submodules/chan/src/queue.c',
    install: false, 
    dependencies: [
    ], 
    include_directories: [
        inc,
        '../../../submodules/chan/src',
    ],
    c_args: chan_c_args,
)
chan_dep = declare_dependency(
    include_directories: [
      inc,
    ], 
    link_with: chan_lib,
)
