c_stringfn_dir =  'submodules/c_stringfn'
c_stringfn_srcs = [
  c_deps_dir + '/' + c_stringfn_dir + '/src/stringfn.c',
  
]
c_stringfn_inc = [
  '../../../submodules/c_stringfn',
  '../../../submodules/c_stringfn/src',
  '../../../submodules/c_stringfn/include',
  inc,
]

c_stringfn_lib =library('c_stringfn', c_stringfn_srcs,
  install: false, 
  dependencies: [
  ], 
  include_directories: c_stringfn_inc,
)

c_stringfn_dep = declare_dependency(
  include_directories: c_stringfn_inc,
  link_with: c_stringfn_lib,
)
cstringfn_dep = c_stringfn_dep

