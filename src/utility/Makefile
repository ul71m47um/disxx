include ../../common.mk

BUILDDIR=./build
PRECOMPILEDDIR=$(BUILDDIR)/precompiled
OBJECTSDIR=$(BUILDDIR)/objects

ASMFLAGS=-c -arch arm64

CFLAGS=-c -fPIC -std=c99 -O3 -DNDEBUG -Weverything -Werror \
	-Wno-misleading-indentation -Wno-sign-conversion \
	-Wno-poison-system-directories -Wno-sign-compare \
	-Wno-declaration-after-statement
ifneq ($(OS),Darwin)
	CFLAGS+=-isysroot $(shell llvm-config --includedir)
endif

CXXFLAGS+=\
	-O3 -fPIC -fprebuilt-module-path=$(PRECOMPILEDDIR) -DNDEBUG \
	-Wno-reserved-module-identifier -Wno-unused-command-line-argument -Wno-c++98-compat \
	-Wno-c++98-compat-pedantic -Wno-reserved-identifier -Wno-weak-vtables \
	-Wno-decls-in-multiple-modules -Wno-poison-system-directories

LFLAGS+=-O2
ifeq ($(OS),Darwin)
	LFLAGS+=-dylib -S -install_name @executable_path/../Frameworks/libdisxx-utility.$(DYLIB)
else
	LFLAGS+=-shared -rpath $$ORIGIN/libdisxx-utility.$(DYLIB)
endif

ifeq ($(OS), Darwin)
	ifeq ($(ARCH), arm64)
		MAPIMPL=./file/mapped.s
		IMPLEXT=s
		MAPIMPLC=$(ASM)
		MAPIMPLFLAGS=$(ASMFLAGS)
	else
		MAPIMPL=./file/mapped.c
		IMPLEXT=c
		MAPIMPLC=$(CC)
		MAPIMPLFLAGS=$(CFLAGS)
	endif
else
	MAPIMPL=./file/mapped.c
	IMPLEXT=c
	MAPIMPLC=$(CC)
	MAPIMPLFLAGS=$(CFLAGS)
endif

BASEPATH=../modules/utility/

MODULES=\
	$(LIBCXX) \
	$(BASEPATH)public/trait/disxx.utility.trait.Cloneable.cppm \
	$(BASEPATH)private/error/disxx.utility.error.DisassemblyError.cppm \
	$(BASEPATH)private/error/disxx.utility.error.NullPointerError.cppm \
	$(BASEPATH)private/error/disxx.utility.error.ParserError.cppm \
	$(BASEPATH)private/pointer/disxx.utility.pointer.DefaultDeleter.cppm \
	$(BASEPATH)private/ini/disxx.utility.ini.BaseParser.cppm \
	$(BASEPATH)private/ini/disxx.utility.ini.Reader.cppm \
	$(BASEPATH)private/ini/disxx.utility.ini.Writer.cppm \
	$(BASEPATH)public/pointer/disxx.utility.pointer.NonNull.cppm \
	$(BASEPATH)public/ini/disxx.utility.ini.Parser.cppm \
	$(BASEPATH)public/file/disxx.utility.file.MappedFile.cppm

SOURCES=\
	./error/disxx.utility.error.NullPointerError.cpp \
	./error/disxx.utility.error.DisassemblyError.cpp \
	./error/disxx.utility.error.ParserError.cpp \
	./ini/disxx.utility.ini.BaseParser.cpp \
	./ini/disxx.utility.ini.Reader.cpp \
	./ini/disxx.utility.ini.Writer.cpp \
	./ini/disxx.utility.ini.Parser.cpp \
	./file/disxx.utility.file.MappedFile.cpp

PRECOMPILED=$(addprefix $(PRECOMPILEDDIR)/, $(notdir $(MODULES:.cppm=.pcm)))
MOBJECTS=$(PRECOMPILED:.pcm=.o)
OBJECTS=$(addprefix $(OBJECTSDIR)/, $(notdir $(SOURCES:.cpp=.o)))

.PHONY: all
all: $(BUILDDIR)/libdisxx-utility.$(DYLIB)

vpath %.cppm $(sort $(dir $(MODULES)))
vpath %.cpp $(sort $(dir $(SOURCES)))
vpath %.pcm $(sort $(dir $(PRECOMPILED)))

$(PRECOMPILEDDIR):
	$(MKDIR) $@
$(OBJECTSDIR):
	$(MKDIR) $@
$(PRECOMPILED): $(PRECOMPILEDDIR)/%.pcm: %.cppm | $(PRECOMPILEDDIR)
	$(CXX) $(CXXFLAGS:-c=--precompile) $< -o $@
$(MOBJECTS): $(PRECOMPILEDDIR)/%.o: $(PRECOMPILEDDIR)/%.pcm | $(PRECOMPILEDDIR)
	$(CXX) $(CXXFLAGS) $< -o $@
$(OBJECTS): $(OBJECTSDIR)/%.o: %.cpp | $(OBJECTSDIR)
	$(CXX) $(CXXFLAGS) $< -o $@
$(OBJECTSDIR)/$(notdir $(MAPIMPL:.$(IMPLEXT)=.o)): $(MAPIMPL)
	$(MAPIMPLC) $(MAPIMPLFLAGS) $< -o $@
OBJECTS+=$(OBJECTSDIR)/$(notdir $(MAPIMPL:.$(IMPLEXT)=.o))
$(BUILDDIR)/libdisxx-utility.$(DYLIB): $(MOBJECTS) $(OBJECTS)
	$(LD) $(LFLAGS) $^ -o $@

clean:
	$(RMDIR) $(BUILDDIR)
