variation_ui_srcs = [
]

variation_ui_dirs = [
  '../../../submodules/variation-ui',
  '../../../submodules/variation-ui/src',
  '../../../submodules/variation-ui/src/lib',
  inc,
]

variation_ui_deps = [

]
variation_ui_libs = []

if variation_ui_srcs.length() > 0
variation_ui_lib =shared_library('variation-ui',
  variation_ui_srcs,
  install: false,
  dependencies: variation_ui_deps,
  include_directories: variation_ui_dirs,
)
variation_ui_libs += variation_ui_lib
endif

variation_ui_dep = declare_dependency(
  include_directories: variation_ui_dirs,
  link_with: variation_ui_libs,
)
