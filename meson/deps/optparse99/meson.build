optparse99_srcs = [files(
  '../../../submodules/optparse99/optparse99.c',
)]

optparse99_dirs = [
  '../../../submodules/optparse99',
  inc,
]

optparse99_cargs = [
  '-DNDEBUG',
  '-DOPTPARSE_HELP_INDENTATION_WIDTH=2',
  '-DOPTPARSE_HELP_USAGE_STYLE=1',
  '-DOPTPARSE_HELP_LETTER_CASE=1',
  '-DOPTPARSE_HELP_MAX_DIVIDER_WIDTH=50',
  '-DOPTPARSE_HELP_FLOATING_DESCRIPTIONS=1',
  '-DOPTPARSE_HELP_MAX_LINE_WIDTH=120',
  '-DOPTPARSE_HELP_WORD_WRAP=0',
  '-DOPTPARSE_HELP_USAGE_STYLE=1',
  ]
optparse99_deps = [

]

optparse99_lib =library('optparse99',
  optparse99_srcs,
  install: false,
  dependencies: optparse99_deps,
  include_directories: optparse99_dirs,
  c_args: optparse99_cargs,
)

optparse99_dep = declare_dependency(
  include_directories: optparse99_dirs,
  link_with: optparse99_lib,
)
