muon-clean:
	@rm -rf build-muon .cache
meson-clean: 
	@rm -rf build 

clean: meson-clean muon-clean
