
ls-greatest:
	@grep -H GREATEST_MAIN_DEF *-test/*.c|cut -d: -f1|sort -u|xargs -I % basename % .c|sort -u
deps-test-ls-tests:
	@eval build/deps-test/deps-test -l
deps-test-ls-suites:
	@eval build/deps-test/deps-test -L
greatest-suites:
	@(make test-file-names | while read -r f; do timeout .5 passh ./build/$$f/$$f -l -v; done) |grep '^* Suite '|cut -d: -f1|cut -d' ' -f3
greatest-suite-tests:
	@passh  ./build/exec-fzf-test/exec-fzf-test -l -v -s s_fzf_basic|grep '^* Suite ' -A 999|grep '^[[:space:]]'|tr -d ' '|cut -d' ' -f1

run-binary:
	@clear; make meson-binaries | env FZF_DEFAULT_COMMAND= \
        fzf --reverse \
            --preview-window='follow,wrap,right,80%' \
            --bind 'ctrl-b:preview(make meson-build)' \
            --preview='env bash -c {} -v -a' \
            --ansi --border \
            --cycle \
            --header='Select Test Binary' \
            --height='100%' \
    | xargs -I % env bash -c "./%"
run-binary-nodemon:
	@make meson-binaries | fzf --reverse | xargs -I % nodemon -w build --delay 1000 -x passh "./%"
meson-tests-list:
	@meson test -C build --list
meson-tests-preview-header:
	@printf "%s\n"   " $(shell ansi --green --bold "Keybinds") "
	@printf "         |-----------------------------------------------------------------|"
	@printf "\n"
	@printf "         |"
	@printf "\n"
	@printf "         |%s"   " $(shell ansi --green --bold "Layout") "
	@printf "\n"
	@printf "         |       - Meson Test Suites           :   %s" "$(shell ansi --cyan --italic "control+s")"
	@printf "\n"
	@printf "         |%s"   " $(shell ansi --green --bold "Source Code") "
	@printf "\n"
	@printf "         |       - Build                       :   %s" "$(shell ansi --red-intense "control+b")"
	@printf "\n"
	@printf "         |       - Clean                       :   %s" "$(shell ansi --red-intense "control+k")"
	@printf "\n"
	@printf "         |       - Tidy                        :   %s" "$(shell ansi --red-intense "control+g")"
	@printf "\n"
	@printf "         |       - List Sources                :   %s" "$(shell ansi --red-intense "control+p")"
	@printf "\n"
	@printf "         |%s"   " $(shell ansi --green --bold "Dependencies") "
	@printf "\n"
	@printf "         |%s"   " $(shell ansi --green --bold "Meson Project") "
	@printf "\n"
	@printf "         |       - Project Options             :   %s" "$(shell ansi --red-intense "control+x")"
	@printf "\n"
	@printf "         |       - Wrap Status                 :   %s" "$(shell ansi --red-intense "control+i")"
	@printf "\n"
	@printf "         |       - Build Files                 :   %s" "$(shell ansi --red-intense "control+j")"
	@printf "\n"
	@printf "         |%s"   " $(shell ansi --green --bold "GIT") "
	@printf "\n"
	@printf "         |       - Git Status                  :   %s" "$(shell ansi --red-intense "control+e")"
	@printf "\n"
	@printf "         |%s"   " $(shell ansi --green --bold "Test Binaries") "
	@printf "\n"
	@printf "         |       - Inspect Tests               :   %s" "$(shell ansi --red-intense "control+z")"
	@printf "\n"
	@printf "         |       - Execute Suites              :   %s" "$(shell ansi --red-intense "control+d")"
	@printf "\n"
	@printf "         |       - Execute Test                :   %s" "$(shell ansi --red-intense "control+v")"
	@printf "\n"
	@printf "         |%s"   " $(shell ansi --green --bold "Preview Window") "
	@printf "\n"
	@printf "         |       - Scroll Preview Up           :   %s" "$(shell ansi --red-intense "control+y")"
	@printf "\n"
	@printf "         |       - Scroll Preview Down         :   %s" "$(shell ansi --red-intense "control+u")"
	@printf "\n"
	@printf "         |       - Adjust Vertical Layout      :   %s" "$(shell ansi --red-intense "control+n")"
	@printf "\n"
	@printf "         |                                     :   %s" "$(shell ansi --red-intense "control+m")"
	@printf "\n"
	@printf "         |       - Adjust Horizontal Layout    :   %s" "$(shell ansi --red-intense "control+/")"
	@printf "\n"
	@printf "         |%s"   " $(shell ansi --green --bold "Misc") "
	@printf "\n"
	@printf "         |       - Tests                       :   %s" "$(shell ansi --yellow-intense --italic "control+t")"
	@printf "\n"
	@printf "         |-----------------------------------------------------------------|"
	@printf "\n"
menu: meson-tests
MENU_PALETTE=base16-equilibrium
meson-tests:
	@vterm-ctrl title "Meson Menu"
	@ansi --save-palette
	@kfc -p $(MENU_PALETTE) 2>/dev/null
	@\
	{ \
	make meson-tests-list; } \
  	  |fzf \
		--border=sharp\
		--margin=0,0,0,0 --padding=0,0,0,0 \
		--no-info \
        --reverse --ansi --no-multi --cycle --info=inline \
        --preview='make meson-tests-preview-header'\
        --preview-window='follow,wrap,right,75%' \
        --header='Control Space For Menu'\
        --header-lines='0' \
        --height='100%'\
        --bind 'ctrl-y:preview-half-page-up'\
        --bind 'ctrl-u:preview-half-page-down'\
        --bind 'ctrl-w:preview(submodules/c_deps/meson/ls_unconfigured_submodules.sh)' \
        --bind 'ctrl-]:preview(submodules/c_deps/meson/ls_configured_submodules.sh)' \
        --bind 'ctrl-space:preview(make meson-tests-preview-header)'\
        --bind 'ctrl-e:preview(passh git status)' \
        --bind 'ctrl-g:preview(passh make tidy)' \
        --bind 'ctrl-i:preview(passh meson wrap status)' \
        --bind 'ctrl-/:change-preview-window(right,80%|right,70%)'\
        --bind 'ctrl-l:change-preview-window(right,60%|right,50%)'\
        --bind 'ctrl-m:change-preview-window(down,80%|down,70%)' \
        --bind 'ctrl-n:change-preview-window(down,60%|down,50%)' \
		--bind 'ctrl-j:change-prompt(Build Files > )'\
			--bind 'ctrl-j:+change-preview-window(nofollow,wrap)'\
        	--bind 'ctrl-j:+change-preview(bat --color always --italic-text always --decorations always --theme "Monokai Extended" {})'\
        	--bind 'ctrl-j:+reload(make meson-introspect-build-files)'\
        --bind 'ctrl-k:preview(make clean meson-build)'\
			--bind 'ctrl-k:+change-preview-window(follow,wrap)'\
		--bind 'ctrl-x:preview(passh muon info options)'\
		--bind 'ctrl-b:preview(passh make build)' \
			--bind 'ctrl-b:+change-preview-window(follow,wrap)'\
		--bind 'ctrl-p:change-prompt(Source Files > )'\
			--bind 'ctrl-p:+change-preview(make bat --color always --italic-text always --decorations always --theme "Monokai Extended" {})'\
			--bind 'ctrl-p:+change-preview-window(nofollow,nowrap,~5,+{2}+5/2)'\
			--bind 'ctrl-p:+reload(make meson-get-source-files)'\
		--bind 'ctrl-o:change-prompt(Meson Tests > )'\
				--bind 'ctrl-o:+change-preview(meson test --num-processes 1 -C build -v --no-stdsplit --print-errorlogs {} || build/{}/{})' \
				--bind 'ctrl-o:+change-preview-window(follow,nowrap)'\
				--bind 'ctrl-o:+reload(make meson-tests-list)' \
		--bind 'ctrl-t:change-prompt(Tests -> ctrl+h to run > )'\
				--bind 'ctrl-t:+change-preview(submodules/c_deps/scripts/deps-test-view-test.sh {})'\
				--bind 'ctrl-t:+reload(make deps-test-ls-tests -B)'\
				--bind 'ctrl-t:+change-preview-window(nofollow,nowrap,~5,+{2}+5/2)'\
		--bind 'ctrl-s:change-prompt(Suites -> ctrl+j to run > )'\
				--bind 'ctrl-s:+change-preview(submodules/c_deps/scripts/deps-test-view-suite.sh {})'\
					--bind 'ctrl-s:+reload(make deps-test-ls-suites -B)'\
				--bind 'ctrl-s:+change-preview-window(nofollow,nowrap,~5,+{2}+5/2)'\
		--bind 'ctrl-z:change-prompt(Inspect Tests > )'\
				--bind 'ctrl-z:+change-preview-window(nofollow,nowrap,~5,+{2}+5/2)'\
				--bind 'ctrl-z:+change-preview(submodules/c_deps/scripts/list-test-tests.sh {})'\
				--bind 'ctrl-z:+reload(make meson-binaries)'\
		--bind 'ctrl-d:change-prompt(Inspect Suites > )'\
					--bind 'ctrl-d:+change-preview(submodules/c_deps/scripts/list-test-suites.sh {})'\
				--bind 'ctrl-d:+change-preview-window(nofollow,nowrap,~5,+{2}+5/2)'\
				--bind 'ctrl-d:+reload(make meson-binaries)'\
		--bind 'ctrl-v:change-prompt(Run Test > )'\
				--bind 'ctrl-v:+change-preview(./build/{}/{} -v -a)'\
				--bind 'ctrl-v:+reload(make meson-binaries)'\
		||true
	@ansi --restore-palette

