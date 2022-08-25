project('c_deps',['c','cpp'],
  default_options:['warning_level=0','c_std=gnu99','default_library=static'],
  version: '0.0.1',
  subproject_dir: 'subprojects',
  )
#############################################################
go_program = find_program('go', required : true)
gofmt_program = find_program('gofmt', required : true)
goimports_program = find_program('goimports', required : true)
unlink_program = find_program('unlink', required : true)
passh_program = find_program('passh', required : true)
sqlite3_program = find_program('sqlite3', required : true)
sh_program = find_program('sh', required : true)
wg_program = find_program('wg', required : true)
passh_program = find_program('passh', required : true)
timeout_bin = find_program('timeout', required : true)
sudo_bin = find_program('sudo', required : true)
git = find_program('git', required: true)
#############################################################
fs = import('fs')
cc = meson.get_compiler('c', native: true)
cpp = meson.get_compiler('cpp', native: true)
c_deps_dir = meson.current_source_dir()
#############################################################
if fs.is_dir('.git')
    git_rev_parse = run_command(git, 'rev-parse', '--short', '@', check: true)
    git_sha = git_rev_parse.stdout().strip()
else
    git_sha = ''
endif
go_version = run_command(go_program,'version', check:true).stdout().strip().split(' ')[2].replace('go','')
#############################################################
version_info = configuration_data()
version_info.set('version', meson.project_version())
version_info.set('go_version', go_version)
version_info.set('vcs_tag', git_sha)
#############################################################
summary({'version': meson.project_version(),
        'vcs_tag': git_sha,
        'go_version': go_version,
        }, section: 'Options')
pwd = c_deps_dir
#############################################################
inc = [
  include_directories('.'),
  include_directories('submodules'),
  include_directories('submodules/reproc'),
  include_directories('submodules/reproc/reproc'),
  include_directories('submodules/reproc/reproc/include'),
  include_directories('submodules/reproc/reproc/src'),
  include_directories('submodules/progress.c'),
  include_directories('submodules/list/src'),
  include_directories('submodules/c_ansi/ansi-codes'),
  include_directories('submodules/debug_print_h/src', 'submodules/debug_print_h/include'),
  include_directories('submodules/progressbar/include/progressbar'),
  include_directories('submodules/generic-print'),
  include_directories('submodules/cgif/inc'),
  include_directories('submodules/str-replace.c/src'),
  include_directories('submodules/dbg.h'),
  include_directories('submodules/SDL_DBGP'),
  include_directories('submodules/c_darwin'),
  include_directories('submodules/c_darwin/kitty'),
  include_directories('submodules/c_sdl/sdl-app-fonts'),
  include_directories('submodules/c_darwin/app-utils', 'submodules/c_darwin/active-app'),
  include_directories('submodules/c_darwin/window-utils'),
  include_directories('submodules/c_ansi'),
  include_directories('submodules/c_pick'),
  include_directories('submodules/sqxclib/sqxc'),
  include_directories(
    'submodules/c_deps/submodules/iowow/src',
  'submodules/c_deps/submodules/iowow/src/kv',
  'submodules/c_deps/submodules/iowow/src/fs',
  'submodules/c_deps/submodules/iowow/src/log',
  'submodules/c_deps/submodules/iowow/src/json',
  'submodules/c_deps/submodules/iowow/src/platform',
  'submodules/c_deps/submodules/iowow'),
]  
###########################################
install_subdir('etc/sounds', install_dir: meson.current_build_dir(), install_tag:'build')
install_subdir('etc/images', install_dir: meson.current_build_dir(), install_tag:'build')
###########################################
subdir('meson')
subdir('submodules')
#subdir('meson/deps/libtermkey')
###########################################
subdir('deps')
subdir('ctable')
subdir('exec-fzf')
subdir('tests-table')
subdir('introspect')
subdir('introspect-repos')
#subdir('meson/deps/json-c')
#subdir('meson/deps/sqxclib')
subdir('meson/deps/wireguard-tools')
subdir('wg')
subdir('hs')
#subdir('c-meson-utils')
#subdir('c-meson-utils-cli')
###########################################
subdir('tmt-test')
subdir('list-test')
subdir('fort-test')
#//subdir('gumbo-test')
#subdir('term-tests')
subdir('deps-test')
#subdir('term-tests-test')
subdir('tinydir-test')
subdir('cgif-test')
#subdir('dbgp-test')
subdir('ee-test')
subdir('chan-test')
subdir('reproc-test')
subdir('introspect-test')
subdir('subprocess-test')
subdir('introspect-repos-test')
#subdir('sqxc-test')
#subdir('reflect-test')
subdir('sqldb-test')
subdir('submodules/c_sdl/sdl-app-test')
subdir('wg-test')
subdir('hs-test')
subdir('kgflags-test')
###########################################
#subdir('c-meson-utils-test')
subdir('exec-fzf-test')
subdir('blocks-test')
subdir('new-case-test')
subdir('new-case1-test')
subdir('roscha-test')
subdir('filecopy-test')
subdir('iowow-test')
subdir('passh-test')
###########################################
subdir('multiselect-long1')
subdir('select_description1')
subdir('multi_select')
subdir('multi_select0')
subdir('multi_select1')
#subdir('multiselect-long0')
subdir('confirm1')
