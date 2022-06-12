uuid4_lib = static_library('uuid4', 
    meson_deps_dir+'/submodules/uuid4/src/uuid4.c', 
    install: false, dependencies: [], 
    include_directories: [
      inc,
    ]
)

uuid4_dep = declare_dependency(include_directories: [
        inc,
    ], link_with: uuid4_lib
)

