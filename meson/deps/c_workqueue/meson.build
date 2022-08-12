c_workqueue_inc = [
  '../../../submodules/c_workqueue/include',
  '../../../submodules/c_workqueue/src',
  '../../../submodules/c_workqueue',
  inc,
]
c_workqueue_lib = both_libraries('c_workqueue', 
  '../../../submodules/c_workqueue/src/workqueue.c',
  install: false, 
  dependencies: [
  ], 
  include_directories: c_workqueue_inc,
)
c_workqueue_dep = declare_dependency(
  include_directories: c_workqueue_inc,
  link_with: c_workqueue_lib,
)
