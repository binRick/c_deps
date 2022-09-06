project('c_deps',['c','cpp'],
  default_options:['warning_level=2','c_std=gnu99','default_library=static'],
  version: '0.0.1',
  subproject_dir: 'subprojects',
  )
#############################################################
subdir('meson/programs')
subdir('meson/programs/go')
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
    'submodules/c_deps/submodules/iowow'
  ),
]  
###########################################
install_subdir('etc/sounds', install_dir: meson.current_build_dir(), install_tag:'build')
install_subdir('etc/images', install_dir: meson.current_build_dir(), install_tag:'build')
###########################################
subdir('meson')
subdir('submodules')
###########################################
subdir('deps')
subdir('ctable')
subdir('exec-fzf')
subdir('tests-table')
subdir('introspect')
subdir('introspect-repos')
subdir('meson/deps/wireguard-tools')
subdir('wg')
subdir('hs')
subdir('tmt-test')
subdir('list-test')
subdir('fort-test')
subdir('tinydir-test')
subdir('cgif-test')
subdir('ee-test')
subdir('chan-test')
subdir('reproc-test')
subdir('introspect-test')
subdir('subprocess-test')
subdir('introspect-repos-test')
subdir('sqldb-test')
subdir('submodules/c_sdl/sdl-app-test')
subdir('wg-test')
subdir('kgflags-test')
subdir('exec-fzf-test')
subdir('blocks-test')
subdir('roscha-test')
subdir('filecopy-test')
subdir('iowow-test')
subdir('passh-test')
subdir('multiselect-long1')
subdir('multi_select')
subdir('multi_select0')
subdir('multi_select1')
subdir('confirm1')
subdir('c-go-interface')
subdir('hash-test')
subdir('rrdtool-test')
subdir('get-next-line-test')
subdir('alloc-or-die-test')
subdir('librnd-test')
subdir('base64-test')
subdir('smaz-test')
subdir('uptime-test')
subdir('font-test')
subdir('spin-test')
subdir('movewin-test')
subdir('layout-test')
subdir('socket99-test')
subdir('wildcardcmp-test')
subdir('http-get-test')
subdir('slug-test')
subdir('which-test')
subdir('chfreq-test')
subdir('genpassword-test')
subdir('levenshtein-test')
subdir('libtrycatch-test')
subdir('dotenv-test')
subdir('murmurhash-test')
subdir('microtar-test')
subdir('occurrences-test')
subdir('str-replace-test')
subdir('md5-test')
subdir('str-truncate-test')
subdir('tiny-regex-test')
subdir('bitfield-test')
subdir('minmax-test')
subdir('path-normalize-test')
subdir('path-module-test')
subdir('str-flatten-test')
subdir('is-number-test')
subdir('url-test')
subdir('querystring-test')
subdir('url-router-test')
subdir('semver-test')
subdir('generic-print-test')
subdir('fancy-progress-test')
subdir('debug-print-test')
subdir('closefrom-test')
subdir('panic-test')
subdir('uuid4-test')
subdir('base64-simple-test')
subdir('parson-test')
subdir('clamp-test')
subdir('libutf8-test')
subdir('stp_print-test')
subdir('libspinner-test')
subdir('sha256-test')
subdir('libmonitors-test')
subdir('totp-test')
subdir('go-libproc-test')
subdir('wcwidth-test')
subdir('libdefer-test')
subdir('expboff-test')
subdir('eventemitter-test')
subdir('msgbox-test')
subdir('msgpack-test')
subdir('hexify-test')
subdir('confuse-test')
subdir('bestline-test')
subdir('httpserver-test')
subdir('log-test')
subdir('siphash-test')
