
deps-test-includes:
	@$(GREP) '^#include.*"' deps-test/deps-test.c|$(CUT) -d'"' -f2|$(SORT) -u
deps-test-includes-paths:
	@$(MAKE) -B deps-test-includes|while read -r f; do\
		if [[ -f "$$f" ]]; then echo "$$f"; \
		elif [[ -f "submodules/$$f" ]]; then echo "submodules/$$f"; \
		elif [[ -f "submodules/c_deps/submodules/c_$(ANSI)/$$f" ]]; then echo "submodules/c_deps/submodules/c_$(ANSI)/$$f"; \
		elif [[ -f "submodules/c_deps/submodules/c_darwin/$$f" ]]; then echo "submodules/c_deps/submodules/c_darwin/$$f"; \
		else $(ANSI) --red "$$f" >&2; fi \
	done | $(GREP) "^submodules/"|$(SED) "s|^submodules/||g"|$(SORT) -u

ls-greatest:
	@$(GREP) -H GREATEST_MAIN_DEF *-test/*.c|$(CUT) -d: -f1|$(SORT) -u|$(XARGS) -I % $(BASENAME) % .c|$(SORT) -u
deps-test-ls-tests:
	@eval build/deps-test/deps-test -l
deps-test-ls-suites:
	@eval build/deps-test/deps-test -L
greatest-suites:
	@($(MAKE) -B test-file-names | while read -r f; do $(TIMEOUT) .5 $(PASSH) ./build/$$f/$$f -l -v; done) |$(GREP) '^* Suite '|$(CUT) -d: -f1|$(CUT) -d' ' -f3
greatest-suite-tests:
	@$(PASSH)  ./build/exec-$(FZF)-test/exec-$(FZF)-test -l -v -s s_$(FZF)_basic|$(GREP) '^* Suite ' -A 999|$(GREP) '^[[:space:]]'|tr -d ' '|$(CUT) -d' ' -f1

run-binary:
	@$(CLEAR); $(MAKE) -B meson-binaries | $(ENV) FZF_DEFAULT_COMMAND= \
        $(FZF) --reverse \
            --preview-window='follow,wrap,right,80%' \
            --bind 'ctrl-b:preview($(MESON) meson-build)' \
            --preview='$(ENV) bash -c {} -v -a' \
            --ansi --border \
            --cycle \
            --header='Select Test Binary' \
            --height='100%' \
    | $(XARGS) -I % $(ENV) bash -c "./%"
run-binary-nodemon:
	@$(MAKE) -B meson-binaries | $(FZF) --reverse | $(XARGS) -I % $(NODEMON) -w build --delay 1000 -x $(PASSH) "./%"
meson-tests-list:
	@$(MESON) test -C build --list
meson-tests-preview-header:
	@printf "%s\n"   " $(shell $(ANSI) --green --bold "Keybinds") "
	@printf "         |-----------------------------------------------------------------|\n"
	@printf "         |%s\n"   " $(shell $(ANSI) --green --bold "Menu") "
	@printf "         |       - Menu Keybinds               :   %s\n" "$(shell $(ANSI) --yellow-intense "control+space")"
	@printf "         |%s\n"   " $(shell $(ANSI) --green --bold "Layout") "
	@printf "         |       - Adjust Vertical Layout      :   %s\n" "$(shell $(ANSI) --yellow-intense "control+\\")"
	@printf "         |       - Adjust Horizontal Layout    :   %s\n" "$(shell $(ANSI) --yellow-intense "control+/")"
	@printf "         |%s\n"   " $(shell $(ANSI) --green --bold "Source Code") "
	@printf "         |       - Build                       :   %s\n" "$(shell $(ANSI) --blue-intense "control+b")"
	@printf "         |       - Clean                       :   %s\n" "$(shell $(ANSI) --blue-intense "control+k")"
	@printf "         |       - Tidy                        :   %s\n" "$(shell $(ANSI) --blue-intense "control+g")"
	@printf "         |       - List Sources                :   %s\n" "$(shell $(ANSI) --blue-intense "control+p")"
	@printf "         |       - Inspect Includes            :   %s\n" "$(shell $(ANSI) --blue-intense "control+a")"
	@printf "         |       - SCC Report                  :   %s\n" "$(shell $(ANSI) --blue-intense "control+u")"
	@printf "         |%s\n"   " $(shell $(ANSI) --green --bold "Dependencies") "
	@printf "         |       - Unconfigured Dependencies   :   %s\n" "$(shell $(ANSI) --cyan-intense "control+w")"
	@printf "         |       - Configured Dependencies     :   %s\n" "$(shell $(ANSI) --cyan-intense "control+]")"
	@printf "         |       - Subprojects Status          :   %s\n" "$(shell $(ANSI) --cyan-intense "control+i")"
	@printf "         |%s\n"   " $(shell $(ANSI) --green --bold "Meson Project") "
	@printf "         |       - Project Options             :   %s\n" "$(shell $(ANSI) --cyan-intense "control+x")"
	@printf "         |       - Wrap Status                 :   %s\n" "$(shell $(ANSI) --cyan-intense "control+i")"
	@printf "         |       - Build Files                 :   %s\n" "$(shell $(ANSI) --cyan-intense "control+j")"
	@printf "         |       - Tests                       :   %s\n" "$(shell $(ANSI) --cyan-intense "control+o")"
	@printf "         |%s\n"   " $(shell $(ANSI) --green --bold "GIT") "
	@printf "         |       - Git Status                  :   %s\n" "$(shell $(ANSI) --green-intense "control+e")"
	@printf "         |%s\n"   " $(shell $(ANSI) --green --bold "Tests") "
	@printf "         |       - Inspect Test Functions      :   %s\n" "$(shell $(ANSI) --red-intense "control+t")"
	@printf "         |       - Inspect Suite Functions     :   %s\n" "$(shell $(ANSI) --red-intense "control+s")"
	@printf "         |       - Inspect Tests               :   %s\n" "$(shell $(ANSI) --red-intense "control+z")"
	@printf "         |       - Inspect Suites              :   %s\n" "$(shell $(ANSI) --red-intense "control+d")"
	@printf "         |       - Test Execution              :   %s\n" "$(shell $(ANSI) --red-intense "control+v")"
	@printf "         |%s\n"   " $(shell $(ANSI) --green --bold "Preview Window") "
	@printf "         |       - Scroll Preview Top          :   %s\n" "$(shell $(ANSI) --magenta-intense "home")"
	@printf "         |       - Scroll Preview Bottom       :   %s\n" "$(shell $(ANSI) --magenta-intense "end")"
	@printf "         |       - Scroll Preview Up           :   %s\n" "$(shell $(ANSI) --magenta-intense "page-up")"
	@printf "         |       - Scroll Preview Down         :   %s\n" "$(shell $(ANSI) --magenta-intense "page-down")"
	@printf "         |-----------------------------------------------------------------|\n"
menu: meson-tests
MENU_PALETTE=base16-equilibrium
meson-tests:
	@{ $(ENV)|$(GREP) -q KITTY_PID && $(KITTY) @set-tab-title "$(shell basename $(shell pwd)) Menu"; } || $(VTERM_CTRL) title "Meson Menu"
	@$(ANSI) --save-palette
	@$(KFC) -p $(MENU_PALETTE) 2>/dev/null
	@\
	{ $(MAKE) -B meson-tests-list; } \
  	  |$(FZF) \
		--border=sharp\
		--margin=0,0,0,0 --padding=0,0,0,0 \
		--no-info \
        --reverse --ansi --no-multi --cycle --info=inline \
        --preview='$(MAKE) -B meson-tests-preview-header'\
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
        --bind 'ctrl-space:preview($(MAKE) -B meson-tests-preview-header)'\
        --bind 'ctrl-e:preview($(PASSH) $(GIT) status --ignore-submodules)' \
        --bind 'ctrl-g:preview($(PASSH) $(MAKE) -B tidy)' \
        --bind 'ctrl-i:preview($(PASSH) $(MESON) wrap status)' \
		--bind 'ctrl-x:preview($(PASSH) $(MUON) info options)'\
        --bind 'ctrl-w:preview(submodules/c_deps/meson/ls_unconfigured_submodules.sh)' \
       	--bind 'ctrl-]:preview(submodules/c_deps/meson/ls_configured_submodules.sh)' \
        --bind 'ctrl-u:preview($(MAKE) scc)'\
		--bind 'ctrl-a:change-prompt(Build Includes > )'\
			--bind 'ctrl-a:+change-preview($(BAT) -f --theme gruvbox-dark submodules/{})'\
			--bind 'ctrl-a:+change-preview-window(nofollow,nowrap)'\
			--bind 'ctrl-a:+reload($(MAKE) deps-test-includes-paths)'\
		--bind 'ctrl-j:change-prompt(Build Files > )'\
			--bind 'ctrl-j:+change-preview-window(nofollow,wrap)'\
        	--bind 'ctrl-j:+change-preview($(ENV) $(BAT) -f --theme gruvbox-dark {})'\
        	--bind 'ctrl-j:+reload($(MAKE) meson-introspect-build-files)'\
        --bind 'ctrl-k:preview($(MAKE) clean meson-build)'\
			--bind 'ctrl-k:+change-preview-window(follow,wrap)'\
		--bind 'ctrl-b:preview($(PASSH) $(MAKE) build)' \
			--bind 'ctrl-b:+change-preview-window(follow,wrap)'\
		--bind 'ctrl-p:change-prompt(Source Files > )'\
			--bind 'ctrl-p:+change-preview($(BAT) --color always --italic-text always --decorations always --theme "Monokai Extended" {})'\
			--bind 'ctrl-p:+change-preview-window(nofollow,nowrap,~5,+{2}+5/2)'\
			--bind 'ctrl-p:+reload($(MAKE) meson-get-source-files)'\
		--bind 'ctrl-o:change-prompt(Meson Tests > )'\
			--bind 'ctrl-o:+change-preview($(PASSH) $(MESON) test --num-processes 1 -C build -v --no-stdsplit --print-errorlogs {} || build/{}/{})' \
			--bind 'ctrl-o:+change-preview-window(follow,nowrap)'\
			--bind 'ctrl-o:+reload($(MAKE) meson-tests-list)' \
		--bind 'ctrl-t:change-prompt(Tests > )'\
			--bind 'ctrl-t:+change-preview(submodules/c_deps/scripts/deps-test-view-test.sh {} && $(ENV) $(PASSH) $(ENV) bash -x -c "build/deps-test/deps-test -a -v -e -t {}")'\
			--bind 'ctrl-t:+change-preview-window(nofollow,nowrap,~5,+{2}+5/2)'\
			--bind 'ctrl-t:+reload($(MAKE) deps-test-ls-tests)'\
		--bind 'ctrl-s:change-prompt(Suites > )'\
			--bind 'ctrl-s:+change-preview(submodules/c_deps/scripts/deps-test-view-suite.sh {} && $(PASSH) $(ENV) bash -x -c "build/deps-test/deps-test -a -v -e -s {}")'\
			--bind 'ctrl-s:+change-preview-window(follow,wrap,~4,+{2}+4/2)'\
			--bind 'ctrl-s:+reload($(MAKE) deps-test-ls-suites)'\
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
	@{ $(ENV)|$(GREP) -q KITTY_PID && $(KITTY) @set-tab-title "$(shell pwd)"; } || $(VTERM_CTRL) title "$(shell pwd)"

m: menu
