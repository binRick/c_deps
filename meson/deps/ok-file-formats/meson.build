ok_file_formats_srcs = [files(
  '../../../submodules/ok-file-formats/ok_csv.c',
  '../../../submodules/ok-file-formats/ok_csv.h',
  '../../../submodules/ok-file-formats/ok_fnt.c',
  '../../../submodules/ok-file-formats/ok_fnt.h',
  '../../../submodules/ok-file-formats/ok_jpg.c',
  '../../../submodules/ok-file-formats/ok_jpg.h',
  '../../../submodules/ok-file-formats/ok_mo.c',
  '../../../submodules/ok-file-formats/ok_mo.h',
  '../../../submodules/ok-file-formats/ok_png.c',
  '../../../submodules/ok-file-formats/ok_png.h',
  '../../../submodules/ok-file-formats/ok_png_write.c',
  '../../../submodules/ok-file-formats/ok_png_write.h',
  '../../../submodules/ok-file-formats/ok_wav.c',
  '../../../submodules/ok-file-formats/ok_wav.h',
)]

ok_file_formats_dirs = [
  '../../../submodules/ok-file-formats',
  inc,
]

ok_file_formats_deps = [

]

ok_file_formats_lib = both_libraries('ok-file-formats',
  ok_file_formats_srcs,
  install: false,
  dependencies: ok_file_formats_deps,
  include_directories: ok_file_formats_dirs,
)

ok_file_formats_dep = declare_dependency(
  include_directories: ok_file_formats_dirs,
  link_with: ok_file_formats_lib,
)
