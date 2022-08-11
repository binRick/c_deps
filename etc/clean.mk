muon-clean:
	@$(RM) -rf build-muon .cache
meson-clean: 
	@$(RM) -rf build 

clean: meson-clean muon-clean
