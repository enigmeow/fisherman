SOURCES      = tags.cxx
TARGET_EXE   = tags

include ../../../src/Makefile.speed-20

FILES_TARGET=~/FILES.el

runtags:
	$(MAKE) -C . $(DEBUG_EXE)
ifeq ($(PLATFORM),windows)
	$(DEBUG_EXE) $(ROOT) $(STORMBIRDS) ~/repos/rel-191 -l "$(INCLUDE)" > $(FILES_TARGET)
else
	$(DEBUG_EXE) $(ROOT) $(STORMBIRDS) ~/repos/rel-191 -l /usr/include /usr/local/include > $(FILES_TARGET)
endif
