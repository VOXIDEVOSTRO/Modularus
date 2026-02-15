BuildDirectory := ../.Build
EFIRoot        := $(BuildDirectory)/sysroot/EFI
ImgSysMirror   := .Build
ModulesDirectory := $(BuildDirectory)/sysroot/modules

SubMake := $(shell find . -name Makefile \
    -not -path './Makefile')

.PHONY: \
	all \
	clean \
	BuildModules

all: \
	BuildModules

BuildModules:
	@for mk in $(SubMake); do \
		echo ">>> Building in $$(dirname $$mk)"; \
		$(MAKE) -C $$(dirname $$mk); \
	done
	@mkdir -p $(ModulesDirectory)
	@cp */.Build/*.ko $(ModulesDirectory)
	
clean:
	@for mk in $(SubMake); do \
		$(MAKE) -C $$(dirname $$mk) clean; \
	done