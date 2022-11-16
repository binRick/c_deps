variation_ui_srcs = [files(
)]

variation_ui_dirs = [
  '../../../submodules/variation-ui',
  '../../../submodules/variation-ui/src',
  '../../../submodules/variation-ui/src/lib',
  inc,
]

variation_ui_deps = [

]

variation_ui_lib =library('variation-ui',
  variation_ui_srcs,
  install: false,
  dependencies: variation_ui_deps,
  include_directories: variation_ui_dirs,
)

variation_ui_dep = declare_dependency(
  include_directories: variation_ui_dirs,
  link_with: variation_ui_lib,
)
