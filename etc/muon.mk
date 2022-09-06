MUON_BUILD_DIR=build-muon
MUON_PARALLEL_COMMANDS=20
muon-setup:
	@$(MUON) setup \
		-b \
		-D buildtype=minsize \
		-D default_library=static \
		-D strip=true \
		-D warning_level=2 \
		-D debug=false \
			$(MUON_BUILD_DIR)
muon-build:
	@$(MUON) samu -C $(MUON_BUILD_DIR) -j $(MUON_PARALLEL_COMMANDS) -k 1
muon-install:
	@cd $(MUON_BUILD_DIR) && $(MUON) install
muon-test:
	@cd $(MUON_BUILD_DIR) && $(MUON) test
muon-test-verbose:
	@cd $(MUON_BUILD_DIR) && $(MUON) test -v -f -d bar -w 5
muon: 
	@make -B muon-setup muon-build
