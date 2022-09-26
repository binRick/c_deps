timg_system_headers = [

]
timg_local_headers = [
  'timg/src/buffered-write-sequencer.h',
  'timg/src/display-options.h',
  'timg/src/framebuffer.h',
  'timg/src/image-display.h',
  'timg/src/image-source.h',
  'timg/src/iterm2-canvas.h',
  'timg/src/jpeg-source.h',
  'timg/src/kitty-canvas.h',
  'timg/src/openslide-source.h',
  'timg/src/qoi-image-source.h',
  'timg/src/renderer.h',
  'timg/src/stb-image-source.h',
  'timg/src/term-query.h',
  'timg/src/terminal-canvas.h',
  'timg/src/termutils.h',
  'timg/src/thread-pool.h',
  'timg/src/timg-base64.h',
  'timg/src/timg-png.h',
  'timg/src/timg-time.h',
  'timg/src/timg-version.h',
  'timg/src/unicode-block-canvas.h',
  'timg/src/video-display.h',
  'timg/third_party/qoi.h',
  'timg/third_party/stb_image.h',
  'timg/third_party/stb_image_resize.h',
]
timg_srcs = [
'timg/src/buffered-write-sequencer.cc',
'timg/src/framebuffer.cc',
'timg/src/image-display.cc',
'timg/src/image-source.cc',
'timg/src/iterm2-canvas.cc',
'timg/src/jpeg-source.cc',
'timg/src/kitty-canvas.cc',
'timg/src/openslide-source.cc',
'timg/src/qoi-image-source.cc',
'timg/src/renderer.cc',
'timg/src/stb-image-source.cc',
'timg/src/term-query.cc',
'timg/src/terminal-canvas.cc',
'timg/src/termutils.cc',
'timg/src/timg-png.cc',
'timg/src/timg.cc',
'timg/src/unicode-block-canvas.cc',
'timg/src/video-display.cc',

]

timg_dirs = [
  '../../../submodules/timg',
  '../../../submodules/timg/img',
  '../../../submodules/timg/src',
  inc,
]

timg_c_args = [
]

timg_deps = [

]
timg_objects = [
'../../../submodules/timg/src/CMakeFiles/timg.dir/term-query.cc.o',
]
timg_objects1 = [
'../../../submodules/timg/src/CMakeFiles/timg.dir/buffered-write-sequencer.cc.o',
'../../../submodules/timg/src/CMakeFiles/timg.dir/framebuffer.cc.o',
'../../../submodules/timg/src/CMakeFiles/timg.dir/image-display.cc.o',
'../../../submodules/timg/src/CMakeFiles/timg.dir/image-source.cc.o',
'../../../submodules/timg/src/CMakeFiles/timg.dir/iterm2-canvas.cc.o',
'../../../submodules/timg/src/CMakeFiles/timg.dir/jpeg-source.cc.o',
'../../../submodules/timg/src/CMakeFiles/timg.dir/kitty-canvas.cc.o',
'../../../submodules/timg/src/CMakeFiles/timg.dir/qoi-image-source.cc.o',
'../../../submodules/timg/src/CMakeFiles/timg.dir/renderer.cc.o',
'../../../submodules/timg/src/CMakeFiles/timg.dir/stb-image-source.cc.o',
'../../../submodules/timg/src/CMakeFiles/timg.dir/terminal-canvas.cc.o',
'../../../submodules/timg/src/CMakeFiles/timg.dir/termutils.cc.o',
'../../../submodules/timg/src/CMakeFiles/timg.dir/timg-png.cc.o',
'../../../submodules/timg/src/CMakeFiles/timg.dir/timg.cc.o',
'../../../submodules/timg/src/CMakeFiles/timg.dir/unicode-block-canvas.cc.o',
'../../../submodules/timg/src/CMakeFiles/timg.dir/video-display.cc.o',
]
timg_links = []
  timg_lib =library('timg',
    [],
    install: false,
    dependencies: timg_deps,
    include_directories: timg_dirs,
    link_with: [],#//timg_objects,
    objects: timg_objects,
    link_language: 'cpp',
    link_whole: timg_objects,
    #objects: timg_objects,
 )


 timg_dep = declare_dependency(
  include_directories: timg_dirs,
  link_with: timg_lib,
)


if false
cmake = import('cmake')
sub_proj = cmake.subproject('timg_src')
timg_lib = sub_proj.dependency('timg')
executable(timg, ['sources'], dependencies: [timg_dep])

  #//  timg_srcs.length() > 0
  timg_links = [timg_lib]
else
endif

