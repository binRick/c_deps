whereami_system_headers = [

]
whereami_local_headers = [
  'whereami/src/whereami.h',
]
whereami_srcs = [
  '../../../submodules/whereami/src/whereami.c',
]

whereami_dirs = [
  '../../../submodules/whereami',
  '../../../submodules/whereami/_gnu-make',
  '../../../submodules/whereami/_ios-xcode',
  '../../../submodules/whereami/_mac-xcode',
  '../../../submodules/whereami/src',
  inc,
]

whereami_c_args = [
]

whereami_deps = [

]

if whereami_srcs.length() > 0
  whereami_lib = library('whereami',
    files(whereami_srcs),
    install: false,
    dependencies: whereami_deps,
    include_directories: whereami_dirs,
    c_args: whereami_c_args,
  )
  whereami_links = [whereami_lib]
else
  whereami_links = []
endif

whereami_dep = declare_dependency(
  include_directories: whereami_dirs,
  link_with: whereami_links,
)
