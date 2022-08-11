
deps-test-includes:
	@$(GREP) '^#include.*"' deps-test/deps-test.c|cut -d'"' -f2|$(SORT) -u
deps-test-includes-paths:
	@$(MAKE) deps-test-includes|while read -r f; do\
		if [[ -f "$$f" ]]; then echo "$$f"; \
		elif [[ -f "submodules/$$f" ]]; then echo "submodules/$$f"; \
		elif [[ -f "submodules/c_deps/submodules/c_$(ANSI)/$$f" ]]; then echo "submodules/c_deps/submodules/c_$(ANSI)/$$f"; \
		elif [[ -f "submodules/c_deps/submodules/c_darwin/$$f" ]]; then echo "submodules/c_deps/submodules/c_darwin/$$f"; \
		else $(ANSI) --red "$$f" >&2; fi \
	done | $(GREP) "^submodules/"|gsed "s|^submodules/||g"|$(SORT) -u

ls-greatest:
	@$(GREP) -H GREATEST_MAIN_DEF *-test/*.c|cut -d: -f1|$(SORT) -u|xargs -I % basename % .c|$(SORT) -u
deps-test-ls-tests:
	@eval build/deps-test/deps-test -l
deps-test-ls-suites:
	@eval build/deps-test/deps-test -L
greatest-suites:
	@($(MAKE) test-file-names | while read -r f; do timeout .5 $(PASSH) ./build/$$f/$$f -l -v; done) |$(GREP) '^* Suite '|cut -d: -f1|cut -d' ' -f3
greatest-suite-tests:
	@$(PASSH)  ./build/exec-$(FZF)-test/exec-$(FZF)-test -l -v -s s_$(FZF)_basic|$(GREP) '^* Suite ' -A 999|$(GREP) '^[[:space:]]'|tr -d ' '|cut -d' ' -f1

run-binary:
	@clear; $(MAKE) meson-binaries | $(ENV) FZF_DEFAULT_COMMAND= \
        $(FZF) --reverse \
            --preview-window='follow,wrap,right,80%' \
            --bind 'ctrl-b:preview($(MESON) meson-build)' \
            --preview='$(ENV) bash -c {} -v -a' \
            --ansi --border \
            --cycle \
            --header='Select Test Binary' \
            --height='100%' \
    | xargs -I % $(ENV) bash -c "./%"
run-binary-nodemon:
	@$(MAKE) meson-binaries | $(FZF) --reverse | xargs -I % nodemon -w build --delay 1000 -x $(PASSH) "./%"
meson-tests-list:
	@$(MESON) test -C build --list
meson-tests-preview-header:
	@printf "%s\n"   " $(shell $(ANSI) --green --bold "Keybinds") "
	@printf "         |-----------------------------------------------------------------|"
	@printf "\n"
	@printf "         |"
	@printf "\n"
	@printf "         |%s"   " $(shell $(ANSI) --green --bold "Menu") "
	@printf "\n"
	@printf "         |       - Menu Keybinds               :   %s" "$(shell $(ANSI) --yellow-intense "control+space")"
	@printf "\n"
	@printf "         |%s"   " $(shell $(ANSI) --green --bold "Layout") "
	@printf "\n"
	@printf "         |       - Adjust Vertical Layout      :   %s" "$(shell $(ANSI) --yellow-intense "control+\\")"
	@printf "\n"
	@printf "         |       - Adjust Horizontal Layout    :   %s" "$(shell $(ANSI) --yellow-intense "control+/")"
	@printf "\n"
	@printf "         |%s"   " $(shell $(ANSI) --green --bold "Source Code") "
	@printf "\n"
	@printf "         |       - Build                       :   %s" "$(shell $(ANSI) --blue-intense "control+b")"
	@printf "\n"
	@printf "         |       - Clean                       :   %s" "$(shell $(ANSI) --blue-intense "control+k")"
	@printf "\n"
	@printf "         |       - Tidy                        :   %s" "$(shell $(ANSI) --blue-intense "control+g")"
	@printf "\n"
	@printf "         |       - List Sources                :   %s" "$(shell $(ANSI) --blue-intense "control+p")"
	@printf "\n"
	@printf "         |       - Inspect Includes            :   %s" "$(shell $(ANSI) --red-intense "control+a")"
	@printf "\n"
	@printf "         |%s"   " $(shell $(ANSI) --green --bold "Dependencies") "
	@printf "\n"
	@printf "         |       - Unconfigured Dependencies   :   %s" "$(shell $(ANSI) --cyan-intense "control+w")"
	@printf "\n"
	@printf "         |       - Configured Dependencies     :   %s" "$(shell $(ANSI) --cyan-intense "control+]")"
	@printf "\n"
	@printf "         |       - Subprojects Status          :   %s" "$(shell $(ANSI) --cyan-intense "control+i")"
	@printf "\n"
	@printf "         |%s"   " $(shell $(ANSI) --green --bold "Meson Project") "
	@printf "\n"
	@printf "         |       - Project Options             :   %s" "$(shell $(ANSI) --cyan-intense "control+x")"
	@printf "\n"
	@printf "         |       - Wrap Status                 :   %s" "$(shell $(ANSI) --cyan-intense "control+i")"
	@printf "\n"
	@printf "         |       - Build Files                 :   %s" "$(shell $(ANSI) --cyan-intense "control+j")"
	@printf "\n"
	@printf "         |       - Tests                       :   %s" "$(shell $(ANSI) --cyan-intense "control+o")"
	@printf "\n"
	@printf "         |%s"   " $(shell $(ANSI) --green --bold "GIT") "
	@printf "\n"
	@printf "         |       - Git Status                  :   %s" "$(shell $(ANSI) --green-intense "control+e")"
	@printf "\n"
	@printf "         |%s"   " $(shell $(ANSI) --green --bold "Tests") "
	@printf "\n"
	@printf "         |       - Inspect Test Functions      :   %s" "$(shell $(ANSI) --red-intense "control+t")"
	@printf "\n"
	@printf "         |       - Inspect Suite Functions     :   %s" "$(shell $(ANSI) --red-intense "control+s")"
	@printf "\n"
	@printf "         |       - Inspect Tests               :   %s" "$(shell $(ANSI) --red-intense "control+z")"
	@printf "\n"
	@printf "         |       - Inspect Suites              :   %s" "$(shell $(ANSI) --red-intense "control+d")"
	@printf "\n"
	@printf "         |       - Test Execution              :   %s" "$(shell $(ANSI) --red-intense "control+v")"
	@printf "\n"
	@printf "         |%s"   " $(shell $(ANSI) --green --bold "Preview Window") "
	@printf "\n"
	@printf "         |       - Scroll Preview Top          :   %s" "$(shell $(ANSI) --magenta-intense "home")"
	@printf "\n"
	@printf "         |       - Scroll Preview Bottom       :   %s" "$(shell $(ANSI) --magenta-intense "end")"
	@printf "\n"
	@printf "         |       - Scroll Preview Up           :   %s" "$(shell $(ANSI) --magenta-intense "page-up")"
	@printf "\n"
	@printf "         |       - Scroll Preview Down         :   %s" "$(shell $(ANSI) --magenta-intense "page-down")"
	@printf "\n"
	@printf "         |-----------------------------------------------------------------|"
	@printf "\n"
menu: meson-tests
MENU_PALETTE=base16-equilibrium
meson-tests:
	@{ $(ENV)|$(GREP) -q KITTY_PID && kitty @set-tab-title "Meson Menu"; } || vterm-ctrl title "Meson Menu"
	@$(ANSI) --save-palette
	@kfc -p $(MENU_PALETTE) 2>/dev/null
	@\
	{ $(MAKE) meson-tests-list; } \
  	  |$(FZF) \
		--border=sharp\
		--margin=0,0,0,0 --padding=0,0,0,0 \
		--no-info \
        --reverse --ansi --no-multi --cycle --info=inline \
        --preview='$(MAKE) meson-tests-preview-header'\
        --preview-window='follow,nowrap,right,75%' \
        --header='Control Space For Menu'\
        --header-lines='0' \
        --height='100%'\
		--bind 'tab:ignore'\
		--bind 'home:preview-top'\
        --bind 'end:preview-bottom'\
		--bind 'pgup:preview-half-page-up'\
        --bind 'pgdn:preview-half-page-down'\
        --bind 'ctrl-/:change-preview-window(right,50%|right,60%|right,70%|right,80%|right,90%)'\
        --bind 'ctrl-\:change-preview-window(down,50%|down,60%|down,70%|down,80%|down,90%)' \
        --bind 'ctrl-space:preview($(MAKE) meson-tests-preview-header)'\
        --bind 'ctrl-e:preview($(PASSH) git status)' \
        --bind 'ctrl-g:preview($(PASSH) $(MAKE) tidy)' \
        --bind 'ctrl-i:preview($(PASSH) $(MESON) wrap status)' \
		--bind 'ctrl-x:preview($(PASSH) muon info options)'\
        --bind 'ctrl-w:preview(submodules/c_deps/meson/ls_unconfigured_submodules.sh)' \
       	--bind 'ctrl-]:preview(submodules/c_deps/meson/ls_configured_submodules.sh)' \
		--bind 'ctrl-a:change-prompt(Build Includes > )'\
			--bind 'ctrl-a:+change-preview(bat -f --theme gruvbox-dark submodules/{})'\
			--bind 'ctrl-a:+change-preview-window(nofollow,nowrap)'\
			--bind 'ctrl-a:+reload($(MAKE) deps-test-includes-paths)'\
		--bind 'ctrl-j:change-prompt(Build Files > )'\
			--bind 'ctrl-j:+change-preview-window(nofollow,wrap)'\
        	--bind 'ctrl-j:+change-preview($(ENV) bat -f --theme gruvbox-dark {})'\
        	--bind 'ctrl-j:+reload($(MAKE) meson-introspect-build-files)'\
        --bind 'ctrl-k:preview($(MAKE) clean meson-build)'\
			--bind 'ctrl-k:+change-preview-window(follow,wrap)'\
		--bind 'ctrl-b:preview($(PASSH) $(MAKE) build)' \
			--bind 'ctrl-b:+change-preview-window(follow,wrap)'\
		--bind 'ctrl-p:change-prompt(Source Files > )'\
			--bind 'ctrl-p:+change-preview(bat --color always --italic-text always --decorations always --theme "Monokai Extended" {})'\
			--bind 'ctrl-p:+change-preview-window(nofollow,nowrap,~5,+{2}+5/2)'\
			--bind 'ctrl-p:+reload($(MAKE) meson-get-source-files)'\
		--bind 'ctrl-o:change-prompt(Meson Tests > )'\
			--bind 'ctrl-o:+change-preview($(MESON) test --num-processes 1 -C build -v --no-stdsplit --print-errorlogs {} || build/{}/{})' \
			--bind 'ctrl-o:+change-preview-window(follow,nowrap)'\
			--bind 'ctrl-o:+reload($(MAKE) meson-tests-list)' \
		--bind 'ctrl-t:change-prompt(Tests > )'\
			--bind 'ctrl-t:+change-preview(submodules/c_deps/scripts/deps-test-view-test.sh {} && $(ENV) $(PASSH) $(ENV) bash -x -c "build/deps-test/deps-test -a -v -e -t {}")'\
			--bind 'ctrl-t:+change-preview-window(nofollow,nowrap,~5,+{2}+5/2)'\
			--bind 'ctrl-t:+reload($(MAKE) deps-test-ls-tests -B)'\
		--bind 'ctrl-s:change-prompt(Suites > )'\
			--bind 'ctrl-s:+change-preview(submodules/c_deps/scripts/deps-test-view-suite.sh {} && $(PASSH) $(ENV) bash -x -c "build/deps-test/deps-test -a -v -e -s {}")'\
			--bind 'ctrl-s:+change-preview-window(follow,wrap,~4,+{2}+4/2)'\
			--bind 'ctrl-s:+reload($(MAKE) deps-test-ls-suites -B)'\
		--bind 'ctrl-z:change-prompt(Inspect Tests > )'\
			--bind 'ctrl-z:+change-preview-window(follow,wrap,~4,+{2}+4/2)'\
			--bind 'ctrl-z:+change-preview(submodules/c_deps/scripts/list-test-tests.sh {})'\
			--bind 'ctrl-z:+reload($(MAKE) meson-binaries)'\
		--bind 'ctrl-d:change-prompt(Inspect Suites > )'\
			--bind 'ctrl-d:+change-preview(submodules/c_deps/scripts/list-test-suites.sh {})'\
			--bind 'ctrl-d:+change-preview-window(nofollow,nowrap,~5,+{2}+5/2)'\
			--bind 'ctrl-d:+reload($(MAKE) meson-binaries)'\
		--bind 'ctrl-v:change-prompt(Run Test > )'\
			--bind 'ctrl-v:+change-preview(./build/{}/{} -v -a)'\
			--bind 'ctrl-v:+reload($(MAKE) meson-binaries)'\
		||true
	@$(ANSI) --restore-palette
	@{ $(ENV)|$(GREP) -q KITTY_PID && kitty @set-tab-title "$(shell pwd)"; } || vterm-ctrl title "$(shell pwd)"

