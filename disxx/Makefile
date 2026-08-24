include ./common.mk

APPDIR=../build/dis++

# MacOS-specific directory
RESOURCES=../build/dis++.app/Contents/Resources

EXECDIR=../build/dis++
LIBDIR=../build/dis++

ICON=./misc/AppIcon.icon
PLIST=./misc/Info.plist
PKGINFO=./misc/PkgInfo

ifeq ($(OS),Darwin)
	APPDIR+=.app

	EXECDIR=../build/dis++.app/Contents/MacOS
	LIBDIR=../build/dis++.app/Contents/Frameworks

	DISXX=$(EXECDIR)/dis++

	ICON=../build/dis++.app/Contents/Resources/AppIcon.icns
	PLIST=../build/dis++.app/Contents/Info.plist
	PKGINFO=../build/dis++.app/Contents/PkgInfo
endif

all: $(DISXX)
.PHONY: all

# Dynamic libraries
UTILITY=$(LIBDIR)/libdisxx-utility.$(DYLIB)
UI=$(LIBDIR)/libdisxx-ui.$(DYLIB)
MACHO=$(LIBDIR)/libdisxx-macho.$(DYLIB)
DISASM=$(LIBDIR)/libdisxx-disasm.$(DYLIB)

# Executable files
DISXX=$(EXECDIR)/dis++
REPORTER=$(EXECDIR)/reporter

$(APPDIR): 
	$(MKDIR) $@
$(RESOURCES): | $(APPDIR)
	$(MKDIR) $@
$(LIBDIR): | $(APPDIR)
	$(MKDIR) $@
$(EXECDIR): | $(APPDIR)
	$(MKDIR) $@
$(UTILITY): | $(LIBDIR)
	make -C ./src/utility/
	$(MOVE) ../build/utility/$(notdir $@) $@
$(UI): | $(LIBDIR)
	make -C ./src/ui/
	$(MOVE) ../build/ui/$(notdir $@) $@
$(MACHO): | $(LIBDIR)
	make -C ./src/loader/
	$(MOVE) ../build/loader/$(notdir $@) $@
$(DISASM): | $(LIBDIR)
	make -C ./src/disasm
	$(MOVE) ../build/disasm/$(notdir $@) $@
$(REPORTER): | $(EXECDIR)
	make -C ./src/reporter/
	$(MOVE) ../build/reporter/$(notdir $@) $@
$(ICON): | $(RESOURCES)
	$(COPY) ./misc/$(notdir $@) $@
$(PLIST):
	$(COPY) ./misc/$(notdir $@) $@
$(PKGINFO):
	$(COPY) ./misc/$(notdir $@) $@
$(DISXX): | \
	$(UTILITY) $(UI) \
	$(MACHO) $(DISASM) \
	$(REPORTER) $(DISXX) \
	$(ICON) $(PLIST) \
	$(PKGINFO)
	make -C ./src/dis++/
	$(MOVE) ../build/dis++/$(notdir $@) $@

clean:
	$(RMDIR) ../build/
