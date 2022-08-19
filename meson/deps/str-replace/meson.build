str_replace_lib = static_library('str-replace', 
  '../../../submodules/str-replace.c/src/str-replace.c',
  install: false, 
  dependencies: [
    occurrences_dep,
  ], 
  include_directories: [
    inc,
    '../../../submodules/str-replace.c/src',
    '../../../submodules/occurrences',
  ]
)
str_replace_dep = declare_dependency(include_directories: ['../../../submodules/str-replace.c/src'], link_with: str_replace_lib)
