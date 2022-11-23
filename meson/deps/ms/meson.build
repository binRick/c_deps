
ms_inc = [
    inc,
]
ms_lib_static =static_library('ms', 
  c_deps_dir + '/submodules/ms/ms.c',
  install: false, 
  dependencies: [
    asprintf_dep,
  ], 
  include_directories: ms_inc,
)
ms_lib =shared_library('ms', 
  c_deps_dir + '/submodules/ms/ms.c',
  install: false, 
  dependencies: [
    asprintf_dep,
  ], 
  include_directories: ms_inc,
)
ms_dep = declare_dependency(
  include_directories: ms_inc,
  link_with: ms_lib,
)
