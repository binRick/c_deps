NODEMON_WATCHED_FILES=$(addprefix -w ,$(TIDIED_FILES))

do-nodemon:
	@$(NODEMON) \
		-I \
		--delay .3 \
		$(NODEMON_WATCHED_FILES) \
		-w '*/meson.build' -w 'meson/deps/*/meson.build' -w 'meson.build' \
		-w Makefile \
		-i submodules -i meson-muon -i .cache -i subprojects \
		-i '*/embeds/*' -i 'subprojects/*/' -i submodules -i 'build/*' \
		-i confirm1/confirm1.h -i flinch/new.h -i multi_select/multi_select.h \
		-i multi_select0/multi_select0.h -i multi_select1/multi_select1.h \
		-i select_description1/select_description1.h \
		-i build \
		-i build-muon \
		-i .cache \
		-i .git \
		-i submodules \
			-e Makefile,tpl,build,sh,c,h,Makefile \
			-x env -- bash --norc --noprofile -c 'clear;make||true'

nodemon: do-nodemon
