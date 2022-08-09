#!/usr/bin/env bash
set -eou pipefail
cd "$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
[[ -d .cache ]] || mkdir .cache
GIT_API_ENABLED=1
MAX_QTY=15

ls_submodules(){
    ./ls_submodules.sh|sort -u
}

main(){
    CUR_QTY=0
    while read -r repo; do
            ansi --red " - $repo"
            if [[ -f "../submodules/$repo/.git" ]]; then
                git="$(cat ../submodules/$repo/.git|grep ^gitdir:|cut -d' ' -f2)"
                if [[ -f "deps/$git/config" ]]; then
                    gc="$(cat "deps/$git/config"|grep 'url ='|cut -d= -f2|tr -d ' '\
                        |gsed 's|ssh://git@|https://|g'\
                        |gsed 's|git@|https://|g'\
                        |gsed 's|\.git$||g'\
                        |gsed 's|github.com:|github.com/|g'\
                        )"
                    git_user="$(echo -e "$gc"|cut -d'/' -f4)"
                    git_repo="$(echo -e "$gc"|cut -d'/' -f5)"
                    git_url="https://api.github.com/search/repositories?q=$git_repo+user:$git_user"
                    git_hash="$(pwd)/.cache/git-repo-$(date +%Y-%m)-$(echo -e "$git_url"|md5sum|cut -d' ' -f1).json"

                    if [[ "$GIT_API_ENABLED" == 1 ]]; then
                        if [[ ! -f "$git_hash" ]]; then
                            curl -s "$git_url" > $git_hash
                            CUR_QTY=$(($CUR_QTY+1))
                        fi
                    fi 
                    ansi -n --yellow " $gc  "
                    ansi -n --blue " [$git_user]"
                    ansi -n --magenta " <$git_repo>"
                    #ansi -n --green " $git_hash"
                    if [[ -f "$git_hash" ]]; then
                        if grep -q 'API rate limit exceeded' $git_hash; then
                            unlink $git_hash
                            GIT_API_ENABLED=0
                        elif grep -q description $git_hash; then
                            git_desc="$(cat $git_hash|jq '.items[0].description' -Mrc)"
                            echo
                            ansi --green "      $git_desc"
                        fi
                    fi
                    echo
                fi


            fi
    done < <(ls_submodules)
}

main
