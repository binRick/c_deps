c_embed_lib = library('c_embed', 
'../../../submodules/c_embed/loader/include/embeds.h',
install: false, dependencies: [
  asprintf_dep,
  ], 
  include_directories: [
    inc,
  ]
)
c_embed_dep = declare_dependency(include_directories: [inc],
link_with: c_embed_lib)
