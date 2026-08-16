ifeq ($(shell echo %OS%),Windows_NT)
	include .\\common.mk
else
	include ./common.mk
endif

all: mvlibs mvapps
.PHONY: all

BINDIR=.$(PATHSEP)dis++
LIBDIR=.$(PATHSEP)dis++
ifeq ($(OS),Darwin)
	BINDIR+=.app$(PATHSEP)Contents$(PATHSEP)MacOS
	LIBDIR+=.app$(PATHSEP)Contents$(PATHSEP)Frameworks
endif

BINDIR:
	$(MKDIR) $@
LIBDIR:
	$(MKDIR) $@

mvapps: | $(BINDIR)
	$(MAKE) -C .$(PATHSEP)src$(PATHSEP)dis++
	$(MAKE) -C .$(PATHSEP)src$(PATHSEP)reporter
	$(MOVE) .$(PATHSEP)src$(PATHSEP)dis++$(PATHSEP)build$(PATHSEP)dis++ $(BINDIR)$(PATHSEP)dis++
	$(MOVE) .$(PATHSEP)src$(PATHSEP)reporter$(PATHSEP)build$(PATHSEP)reporter $(BINDIR)$(PATHSEP)reporter
	ifeq ($(OS),Darwin)
		$(MOVE) .$(PATHSEP)misc$(PATHSEP)Info.plist .$(PATHSEP)dis++.app$(PATHSEP)Contents$(PATHSEP)Info.plist
		$(MOVE) .$(PATHSEP)misc$(PATHSEP)PkgInfo .$(PATHSEP)dis++.app$(PATHSEP)Contents$(PATHSEP)PkgInfo
	endif
mvlibs: | $(LIBDIR)
	$(MOVE) .$(PATHSEP)src$(PATHSEP)dis++$(PATHSEP)build$(PATHSEP)dependencies$(PATHSEP)libdisxx-util.$(DYLIB) $(LIBDIR)$(PATHSEP)libdisxx-util.$(DYLIB)
	$(MOVE) .$(PATHSEP)src$(PATHSEP)dis++$(PATHSEP)build$(PATHSEP)dependencies$(PATHSEP)libdisxx-ui.$(DYLIB) $(LIBDIR)$(PATHSEP)libdisxx-ui.$(DYLIB)
	$(MOVE) .$(PATHSEP)src$(PATHSEP)dis++$(PATHSEP)build$(PATHSEP)dependencies$(PATHSEP)libdisxx-macho.$(DYLIB) $(LIBDIR)$(PATHSEP)libdisxx-macho.$(DYLIB)
	$(MOVE) .$(PATHSEP)src$(PATHSEP)dis++$(PATHSEP)build$(PATHSEP)dependencies$(PATHSEP)libdisxx-disasm.$(DYLIB) $(LIBDIR)$(PATHSEP)libdisxx-disasm.$(DYLIB)
