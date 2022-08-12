python-venv: do-python-venv python-venv-meson
do-python-venv:
	@[[ -f $(VENV_DIR)/bin/activate ]] ||  { $(PYTHON3) -m venv $(VENV_DIR) && $(SOURCE_VENV_CMD) && $(PYTHON3) -m pip install pip -U; }
	@true
python-venv-meson:
	@[[ -e $(MESON) ]] || { $(SOURCE_VENV_CMD) && $(PYTHON3) -m pip install meson -U; }
	@[[ -e $(NINJA) ]] || { $(SOURCE_VENV_CMD) && $(PYTHON3) -m pip install ninja -U; }
