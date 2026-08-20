include ../../common.mk

MODULESPATH=../modules/loader/

BUILDDIR=./build
DEPENDENCIESDIR=$(BUILDDIR)/dependencies
PRECOMPILEDDIR=./build/precompiled
OBJECTSDIR=./build/objects

CXXFLAGS+=\
	-O3 -fPIC -fprebuilt-module-path=$(PRECOMPILEDDIR) -I../third-party -DNDEBUG \
	-Wno-c99-extensions -Wno-global-constructors -Wno-exit-time-destructors -Wno-reserved-identifier -Wno-non-virtual-dtor \
	-Wno-switch-enum -Wno-reserved-macro-identifier -Wno-writable-strings -Wno-weak-vtables -Wno-undefined-func-template \
	-Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-covered-switch-default -Wno-padded -Wno-sign-conversion \
	-Wno-unused-command-line-argument -Wno-decls-in-multiple-modules -Wno-poison-system-directories

LFLAGS+=-O2 -L$(DEPENDENCIESDIR) -ldisxx-utility
ifeq ($(OS),Darwin)
	LFLAGS+=-dylib -S -install_name @executable_path/../Frameworks/libdisxx-macho.$(DYLIB)
else
	LFLAGS+=-shared -rpath $$ORIGIN/libdisxx-macho.$(DYLIB)
endif

MODULES=\
	$(LIBCXX) \
	../modules/utility/public/file/disxx.utility.file.MappedFile.cppm \
	$(MODULESPATH)private/utility/disxx.loader.utility.BinaryInfo.cppm \
	$(MODULESPATH)private/executable/disxx.loader.executable.Label.cppm \
	$(MODULESPATH)private/executable/disxx.loader.executable.Section.cppm \
	$(MODULESPATH)public/executable/disxx.loader.executable.ExecutableFile.cppm \
	$(MODULESPATH)public/disxx.loader.macho.Loader.cppm

SOURCES=\
	./utility/disxx.loader.utility.BinaryInfo.cpp \
	./executable/disxx.loader.executable.Label.cpp \
	./executable/disxx.loader.executable.Section.cpp \
	./executable/disxx.loader.executable.ExecutableFile.cpp \
	./disxx.loader.macho.Loader.cpp

all: $(BUILDDIR)/libdisxx-macho.$(DYLIB)

UTILITIES=$(DEPENDENCIESDIR)/libdisxx-utility.$(DYLIB)
DEPENDENCIES=$(UTILITIES)

PRECOMPILED=$(addprefix $(PRECOMPILEDDIR)/, $(notdir $(MODULES:.cppm=.pcm)))
MOBJECTS=$(PRECOMPILED:.pcm=.o)
OBJECTS=$(addprefix $(OBJECTSDIR)/, $(notdir $(SOURCES:.cpp=.o)))

vpath %.cppm $(sort $(dir $(MODULES)))
vpath %.cpp $(sort $(dir $(SOURCES)))
vpath %.pcm $(sort $(dir $(PRECOMPILED)))

$(DEPENDENCIESDIR):
	$(MKDIR) $@
$(PRECOMPILEDDIR):
	$(MKDIR) $@
$(OBJECTSDIR):
	$(MKDIR) $@
$(PRECOMPILED): $(PRECOMPILEDDIR)/%.pcm: %.cppm | $(PRECOMPILEDDIR)
	$(CXX) -c $(CXXFLAGS:-c=--precompile) $< -o $@
$(MOBJECTS): $(PRECOMPILEDDIR)/%.o: $(PRECOMPILEDDIR)/%.pcm | $(PRECOMPILEDDIR)
	$(CXX) -c $(CXXFLAGS) $< -o $@
$(OBJECTS): $(OBJECTSDIR)/%.o: %.cpp | $(OBJECTSDIR)
	$(CXX) -c $(CXXFLAGS) $< -o $@
$(UTILITIES): | $(DEPENDENCIESDIR)
	make -C ../utility
	$(MOVE) ../utility/build/libdisxx-utility.$(DYLIB) $@
$(BUILDDIR)/libdisxx-macho.$(DYLIB): $(MOBJECTS) $(OBJECTS) | $(DEPENDENCIES)
	$(LD) $(LFLAGS) $^ -o $@

clean:
	$(RMDIR) $(BUILDDIR)
