include ./common.mk

APPDIR=./dis++
all: $(APPDIR)
.PHONY: all

EXECDIR=./dis++
LIBDIR=./dis++

PLIST=./misc/Info.plist
PKGINFO=./misc/PkgInfo

ifeq ($(OS),Darwin)
	APPDIR+=.app

	EXECDIR=./dis++.app/Contents/MacOS
	LIBDIR=./dis++.app/Contents/Frameworks

	PLIST=./dis++.app/Contents/Info.plist
	PKGINFO=./dis++.app/Contents/PkgInfo
endif

# Dynamic libraries
UTILITY=$(LIBDIR)/libdisxx-utility.$(DYLIB)
UI=$(LIBDIR)/libdisxx-ui.$(DYLIB)
MACHO=$(LIBDIR)/libdisxx-macho.$(DYLIB)
DISASM=$(LIBDIR)/libdisxx-disasm.$(DYLIB)

# Executable files
REPORTER=$(EXECDIR)/reporter
DISXX=$(EXECDIR)/dis++

$(LIBDIR):
	$(MKDIR) $@
$(EXECDIR):
	$(MKDIR) $@
$(UTILITY): | $(LIBDIR)
	make -C ./src/utility/
	$(MOVE) ./src/utility/build/$(notdir $@) $@
$(UI): | $(LIBDIR)
	make -C ./src/ui/
	$(MOVE) ./src/ui/build/$(notdir $@) $@
$(MACHO): | $(LIBDIR)
	make -C ./src/loader/
	$(MOVE) ./src/loader/build/$(notdir $@) $@
$(DISASM): | $(LIBDIR)
	make -C ./src/disasm
	$(MOVE) ./src/disasm/build/$(notdir $@) $@
$(REPORTER): | $(EXECDIR)
	make -C ./src/reporter/
	$(MOVE) ./src/reporter/build/$(notdir $@) $@
$(DISXX): | $(EXECDIR)
	make -C ./src/dis++/
	$(MOVE) ./src/dis++/build/$(notdir $@) $@
$(PLIST):
	$(COPY) ./misc/$(notdir $@) $@
$(PKGINFO):
	$(COPY) ./misc/$(notdir $@) $@
$(APPDIR): | \
	$(UTILITY) $(UI) \
	$(MACHO) $(DISASM) \
	$(REPORTER) $(DISXX) \
	$(PLIST) $(PKGINFO)
