get_meson_deps() {
	find meson/deps/*/meson.build -type f | sort -u | xargs -I % dirname % | egrep -v 'meson_deps'
}

get_missing_meson_build_subdir_deps() {
	while read -r l; do
		if ! grep -q "^${l}$" meson.build; then
			echo -e "$l"
		fi
	done < <(get_meson_deps_subdirs)
}

get_meson_deps_subdirs() {
	while read -r d; do
		echo -e "subdir('$d')"
	done < <(get_meson_deps)
}

get_deps_fxns() {
	egrep '^[a-z].*()' scripts/deps-utils.sh | cut -d'(' -f1 | sort -u
}

add_submodule_deps() {
	while read -r cmd; do
		eval "$cmd"
	done < <(get_add_deps_cmds)
}

clone_deps() {
	while read -r cmd; do
		eval "$cmd"
	done < <(get_deps_cmds)
}

get_deps_array() {
	cat ../c_*/.gitmodules | grep '=' | cut -d= -f2 | gsed 's/^[[:space:]]//g' | paste -s -d' \n' | sort -u | grep -v 'meson_deps'
}

get_add_deps_cmds() {
	while read -r dep_dir dep_repo; do
		local cmd="$(get_add_dep_cmd "$dep_repo" "$dep_dir")"
		echo -e "$cmd"
	done < <(get_deps_array)
}

get_deps_cmds() {
	while read -r dep_dir dep_repo; do
		local cmd="$(get_dep_cmd "$dep_repo" "$dep_dir")"
		echo -e "$cmd"
	done < <(get_deps_array)
}

get_deps_du() {
	du --max-depth=1 -b submodules | sort -u | gsed 's/[[:space:]]/ /g' | uniq -u | sort -h
}

get_meson_deps_names() {
	while read -r meson_dep; do
		egrep '^[a-z].*_dep ' "$meson_dep" | cut -d' ' -f1 | sort -u
	done < <(get_meson_build_deps_meson_builds)
}

get_meson_build_deps_meson_builds() {
	while read -r meson_dep_dir; do
		local f="$meson_dep_dir/meson.build"
		echo -e "$f"
	done < <(get_meson_build_deps)
}

get_meson_build_deps() {
	egrep '^subdir\(' meson.build | cut -d"'" -f2 | grep '^meson/deps/' | sort -u
}

get_meson_build_subdirs() {
	egrep '^subdir\(' meson.build | cut -d"'" -f2 | grep '^meson/deps/' | xargs -I % basename % | sort -u
}

get_deps_props() {
	while read -r dep_dir dep_repo; do
		dep_exists=false
		dep_du=0B
		if [[ -d "$dep_dir" ]]; then
			dep_exists=true
			dep_du="$(du --max-depth=0 -b "$dep_dir" | gsed 's/[[:space:]]/ /g' | gsed 's/^[[:space:]].*//g' | cut -d' ' -f1)"
		fi
		dep_name="$(basename $dep_dir)"
		echo "name:$dep_name"
		echo "  exists:$dep_exists"
		echo "  dir:$dep_dir"
		echo "  repo:$dep_repo"
		echo "  cmd:$(get_add_dep_cmd "$dep_repo" "$dep_dir")"
		echo "  du:$dep_du"
		echo
	done < <(get_deps_array)
}

get_add_dep_cmd() {
	local REPO="$1"
	local DIR="$2"
	local CMD="[[ -d $DIR/.git ]] || git submodule add -f $REPO $DIR"
	printf "%s\n" "$CMD"
}
get_dep_cmd() {
	local REPO="$1"
	local DIR="$2"
	local CMD="[[ -d $DIR/.git ]] || git clone --recurse-submodules $REPO $DIR"
	printf "%s\n" "$CMD"
}
