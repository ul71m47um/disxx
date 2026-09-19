include ./common.mk

BUNDLE=../build/dis++

# MacOS-specific directory
RESOURCES=../build/dis++.app/Contents/Resources

BINDIR=../build/dis++
LIBDIR=../build/dis++

ICON=./misc/AppIcon.icon
PLIST=./misc/Info.plist
PKGINFO=./misc/PkgInfo

ifeq ($(OS),Darwin)
	BUNDLE=../build/dis++.app

	BINDIR=$(BUNDLE)/Contents/MacOS
	LIBDIR=$(BUNDLE)/Contents/Frameworks

	ICON=$(BUNDLE)/Contents/Resources/AppIcon.icns
	PLIST=$(BUNDLE)/Contents/Info.plist
	PKGINFO=$(BUNDLE)/Contents/PkgInfo
endif

DISXX=$(BINDIR)/dis++
REPORTER=$(BINDIR)/reporter

all: $(BUNDLE)
.PHONY: all

# Dynamic libraries
UTILITY=$(LIBDIR)/libdisxx-utility.$(DYLIB)
UI=$(LIBDIR)/libdisxx-ui.$(DYLIB)
MACHO=$(LIBDIR)/libdisxx-macho.$(DYLIB)
DISASM=$(LIBDIR)/libdisxx-disasm.$(DYLIB)

$(APPDIR): 
	$(MKDIR) $@
$(RESOURCES):
	$(MKDIR) $@
$(LIBDIR):
	$(MKDIR) $@
$(BINDIR):
	$(MKDIR) $@
$(UTILITY): | $(LIBDIR)
	make -C ./disxx-utility/
	$(MOVE) ../build/disxx-utility/$(notdir $@) $@
$(UI): | $(LIBDIR)
	make -C ./disxx-ui/
	$(MOVE) ../build/disxx-ui/$(notdir $@) $@
$(MACHO): | $(LIBDIR)
	make -C ./disxx-loader/
	$(MOVE) ../build/disxx-loader/$(notdir $@) $@
$(DISASM): | $(LIBDIR)
	make -C ./disxx-disasm/
	$(MOVE) ../build/disxx-disasm/$(notdir $@) $@
$(DISXX): | $(BINDIR)
	make -C ./disxx-app/
	$(MOVE) ../build/disxx-app/dis++ $@
$(REPORTER): | $(BINDIR)
	make -C ./disxx-reporter/
	$(MOVE) ../build/disxx-reporter/$(notdir $@) $@
$(ICON): | $(RESOURCES)
	$(COPY) ./misc/$(notdir $@) $@
$(PLIST):
	$(COPY) ./misc/$(notdir $@) $@
$(PKGINFO):
	$(COPY) ./misc/$(notdir $@) $@
$(BUNDLE): | \
	$(UTILITY) $(UI) \
	$(MACHO) $(DISASM) \
	$(REPORTER) $(DISXX) \
	$(ICON) $(PLIST) \
	$(PKGINFO)
	$(MKDIR) $@

clean:
	make clean -C ./disxx-utility/
	make clean -C ./disxx-ui/
	make clean -C ./disxx-loader/
	make clean -C ./disxx-disasm/
	make clean -C ./disxx-app/
	make clean -C ./disxx-reporter/
	$(RMDIR) ../build/
