uthash_dep = dependency('uthash', required: true, fallback: ['uthash', 'uthash_dep'])
uthash_dirs = [
  '../../../submodules/uthash',
  '../../../submodules/uthash/doc',
  '../../../submodules/uthash/src',
  inc,
]

uthash_deps = [

]

uthash_dep_submodules = declare_dependency(
  include_directories: uthash_dirs,
  link_with: [],
)
