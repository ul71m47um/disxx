ifeq ($(shell echo %OS%), Windows_NT)
	include ..\\common.mk
else
	include ../common.mk
endif

MODULESPATH=..$(PATHSEP)modules$(PATHSEP)loader$(PATHSEP)

BUILDDIR=.$(PATHSEP)build
DEPENDENCIESDIR=$(BUILDDIR)$(PATHSEP)dependencies
PRECOMPILEDDIR=.$(PATHSEP)build$(PATHSEP)precompiled
OBJECTSDIR=.$(PATHSEP)build$(PATHSEP)objects

CXXFLAGS+=\
	-O3 -fPIC -fprebuilt-module-path=$(PRECOMPILEDDIR) -I..$(PATHSEP)third-party -DNDEBUG \
	-Wno-c99-extensions -Wno-global-constructors -Wno-exit-time-destructors -Wno-reserved-identifier -Wno-non-virtual-dtor \
	-Wno-switch-enum -Wno-reserved-macro-identifier -Wno-writable-strings -Wno-weak-vtables -Wno-undefined-func-template \
	-Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-covered-switch-default -Wno-padded -Wno-sign-conversion \
	-Wno-unused-command-line-argument -Wno-decls-in-multiple-modules -Wno-poison-system-directories

LFLAGS+=-O2 -L$(DEPENDENCIESDIR) -ldisxx-util
ifeq ($(OS),Darwin)
	LFLAGS+=-dylib -S -install_name @executable_path/../Frameworks/libdisxx-macho.$(DYLIB)
else
	ifneq ($(OS),Windows_NT)
		LFLAGS+=-rpath $$ORIGIN/libdisxx-macho.$(DYLIB)
	endif
endif

MODULES=\
	$(LIBCXX) \
	..$(PATHSEP)modules$(PATHSEP)utility$(PATHSEP)public$(PATHSEP)file$(PATHSEP)disxx.utility.file.MappedFile.cppm \
	$(MODULESPATH)private$(PATHSEP)utility$(PATHSEP)disxx.loader.utility.BinaryInfo.cppm \
	$(MODULESPATH)private$(PATHSEP)executable$(PATHSEP)disxx.loader.executable.Label.cppm \
	$(MODULESPATH)private$(PATHSEP)executable$(PATHSEP)disxx.loader.executable.Section.cppm \
	$(MODULESPATH)public$(PATHSEP)executable$(PATHSEP)disxx.loader.executable.ExecutableFile.cppm \
	$(MODULESPATH)public$(PATHSEP)disxx.loader.macho.Loader.cppm

SOURCES=\
	.$(PATHSEP)utility$(PATHSEP)disxx.loader.utility.BinaryInfo.cpp \
	.$(PATHSEP)executable$(PATHSEP)disxx.loader.executable.Label.cpp \
	.$(PATHSEP)executable$(PATHSEP)disxx.loader.executable.Section.cpp \
	.$(PATHSEP)executable$(PATHSEP)disxx.loader.executable.ExecutableFile.cpp \
	.$(PATHSEP)disxx.loader.macho.Loader.cpp

all: $(BUILDDIR)$(PATHSEP)libdisxx-macho.$(DYLIB)

UTILITIES=$(DEPENDENCIESDIR)$(PATHSEP)libdisxx-util.$(DYLIB)
DEPENDENCIES=$(UTILITIES)

PRECOMPILED=$(addprefix $(PRECOMPILEDDIR)$(PATHSEP), $(notdir $(MODULES:.cppm=.pcm)))
MOBJECTS=$(PRECOMPILED:.pcm=.o)
OBJECTS=$(addprefix $(OBJECTSDIR)$(PATHSEP), $(notdir $(SOURCES:.cpp=.o)))

vpath %.cppm $(sort $(dir $(MODULES)))
vpath %.cpp $(sort $(dir $(SOURCES)))
vpath %.pcm $(sort $(dir $(PRECOMPILED)))

$(DEPENDENCIESDIR):
	$(MKDIR) $@
$(PRECOMPILEDDIR):
	$(MKDIR) $@
$(OBJECTSDIR):
	$(MKDIR) $@
$(PRECOMPILED): $(PRECOMPILEDDIR)$(PATHSEP)%.pcm: %.cppm | $(PRECOMPILEDDIR)
	$(CXX) -c $(CXXFLAGS:-c=--precompile) $< -o $@
$(MOBJECTS): $(PRECOMPILEDDIR)$(PATHSEP)%.o: $(PRECOMPILEDDIR)$(PATHSEP)%.pcm | $(PRECOMPILEDDIR)
	$(CXX) -c $(CXXFLAGS) $< -o $@
$(OBJECTS): $(OBJECTSDIR)$(PATHSEP)%.o: %.cpp | $(OBJECTSDIR)
	$(CXX) -c $(CXXFLAGS) $< -o $@
$(UTILITIES): | $(DEPENDENCIESDIR)
	make -C ..$(PATHSEP)utility
	$(MOVE) ..$(PATHSEP)utility$(PATHSEP)build$(PATHSEP)libdisxx-util.$(DYLIB) $@
$(BUILDDIR)$(PATHSEP)libdisxx-macho.$(DYLIB): $(MOBJECTS) $(OBJECTS) | $(DEPENDENCIES)
	$(LD) $(LFLAGS) $^ -o $@

clean:
	$(RMDIR) $(BUILDDIR)
