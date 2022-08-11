variation_ui_srcs = [files(
  '../../../submodules/variation-ui/src/lib/vn_conf.h',
  '../../../submodules/variation-ui/src/lib/vn_ui.h',
  '../../../submodules/variation-ui/src/lib/vn_util.h',
  '../../../submodules/variation-ui/src/lib/vn_widget.h',
  '../../../submodules/variation-ui/src/vn_ui.c',
  '../../../submodules/variation-ui/src/vn_util.c',
  '../../../submodules/variation-ui/src/vn_widget.c',
  '../../../submodules/variation-ui/vn_ui.h',
)]

variation_ui_dirs = [
  '../../../submodules/variation-ui',
  '../../../submodules/variation-ui/src',
  '../../../submodules/variation-ui/src/lib',
  inc,
]

variation_ui_deps = [

]

variation_ui_lib = static_library('variation-ui',
  variation_ui_srcs,
  install: false,
  dependencies: variation_ui_deps,
  include_directories: variation_ui_dirs,
)

variation_ui_dep = declare_dependency(
  include_directories: variation_ui_dirs,
  link_with: variation_ui_lib,
)
