#reproc_dep_mode = 'system'
reproc_dep_mode = 'source'
#reproc_source_mode = 'shared'
#reproc_source_mode = 'library'
#reproc_source_mode = 'both_libraries'
reproc_source_mode = 'static'
reproc_dep_deps = [
  ]
reproc_dep_dirs = [
    '../../../submodules/reproc/reproc/include',
    '../../../submodules/reproc/reproc/include/reproc',
    '../../../submodules/reproc/reproc',
    '../../../submodules/reproc/reproc/src',
    '../../../submodules/reproc',
    inc,
    ]
reproc_dep_srcs = [files(
    '../../../submodules/reproc/reproc/src/clock.posix.c',
    '../../../submodules/reproc/reproc/src/drain.c',
    '../../../submodules/reproc/reproc/src/error.posix.c',
    '../../../submodules/reproc/reproc/src/handle.posix.c',
    '../../../submodules/reproc/reproc/src/init.posix.c',
    '../../../submodules/reproc/reproc/src/options.c',
    '../../../submodules/reproc/reproc/src/pipe.posix.c',
    '../../../submodules/reproc/reproc/src/process.posix.c',
    '../../../submodules/reproc/reproc/src/redirect.c',
    '../../../submodules/reproc/reproc/src/redirect.posix.c',
    '../../../submodules/reproc/reproc/src/reproc.c',
    '../../../submodules/reproc/reproc/src/run.c',
    '../../../submodules/reproc/reproc/src/strv.c',
    '../../../submodules/reproc/reproc/src/utf.posix.c',
    )]

if reproc_dep_mode == 'system'
  reproc_dep = dependency('reproc', required: true)
elif reproc_dep_mode == 'source'
    if reproc_source_mode == 'static'
      reproc_lib =library('reproc',reproc_dep_srcs,
        install: false, 
        dependencies: [reproc_dep_deps],
        include_directories: reproc_dep_dirs,
      )
    elif reproc_source_mode == 'library'
      reproc_lib = library('reproc',reproc_dep_srcs,
        install: false, 
        dependencies: [reproc_dep_deps],
        include_directories: reproc_dep_dirs,
      )
    endif
  reproc_dep = declare_dependency(include_directories: reproc_dep_dirs, link_with: reproc_lib)
endif


