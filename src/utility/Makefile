ifeq ($(shell echo %OS%), Windows_NT)
	include ..\\common.mk
else
	include ../common.mk
endif

BUILDDIR=.$(PATHSEP)build
PRECOMPILEDDIR=$(BUILDDIR)$(PATHSEP)precompiled
OBJECTSDIR=$(BUILDDIR)$(PATHSEP)objects

ASMFLAGS=-c -arch arm64

CFLAGS=-c -std=c99 -Weverything -Werror -Wno-misleading-indentation \
	-Wno-sign-conversion -O3 -DNDEBUG -isysroot $(shell xcrun --show-sdk-path)

CXXFLAGS+=\
	-O3 -fprebuilt-module-path=$(PRECOMPILEDDIR) -fprebuilt-module-path=$(PRECOMPILEDDIR) -DNDEBUG -I..$(PATHSEP)include \
	-Wno-reserved-module-identifier -Wno-unused-command-line-argument -Wno-c++98-compat \
	-Wno-c++98-compat-pedantic -Wno-reserved-identifier -Wno-weak-vtables \
	-Wno-decls-in-multiple-modules

LFLAGS+=-dylib -O2 -S
ifeq ($(OS),Darwin)
	LFLAGS+=-install_name @executable_path/../Frameworks/libdisxx-util.$(DYLIB)
else
	ifne ($(OS), Windows_NT)
		LDFLAGS+=-install_name $$ORIGIN/libdisxx-util.$(DYLIB)
endif

ifeq ($(OS), Darwin)
	ifeq ($(ARCH), arm64)
		MAPIMPL=.$(PATHSEP)file$(PATHSEP)mapped.s
		IMPLEXT=s
		MAPIMPLC=$(ASM)
		MAPIMPLFLAGS=$(ASMFLAGS)
	else
		MAPIMPL=.$(PATHSEP)file$(PATHSEP)mapped.c
		IMPLEXT=c
		MAPIMPLC=$(CC)
		MAPIMPLFLAGS=$(CFLAGS)
	endif
else
	MAPIMPL=.$(PATHSEP)file$(PATHSEP)mapped.c
	IMPLEXT=c
	MAPIMPLC=$(CC)
	MAPIMPLFLAGS=$(CFLAGS)
endif

BASEPATH=..$(PATHSEP)modules$(PATHSEP)utility$(PATHSEP)

MODULES=\
	$(LIBCXX) \
	$(BASEPATH)public$(PATHSEP)trait$(PATHSEP)disxx.utility.trait.Cloneable.cppm \
	$(BASEPATH)private$(PATHSEP)error$(PATHSEP)disxx.utility.error.DisassemblyError.cppm \
	$(BASEPATH)private$(PATHSEP)error$(PATHSEP)disxx.utility.error.NullPointerError.cppm \
	$(BASEPATH)private$(PATHSEP)error$(PATHSEP)disxx.utility.error.ParserError.cppm \
	$(BASEPATH)private$(PATHSEP)pointer$(PATHSEP)disxx.utility.pointer.DefaultDeleter.cppm \
	$(BASEPATH)private$(PATHSEP)ini$(PATHSEP)disxx.utility.ini.BaseParser.cppm \
	$(BASEPATH)private$(PATHSEP)ini$(PATHSEP)disxx.utility.ini.Reader.cppm \
	$(BASEPATH)private$(PATHSEP)ini$(PATHSEP)disxx.utility.ini.Writer.cppm \
	$(BASEPATH)public$(PATHSEP)pointer$(PATHSEP)disxx.utility.pointer.NonNull.cppm \
	$(BASEPATH)public$(PATHSEP)ini$(PATHSEP)disxx.utility.ini.Parser.cppm \
	$(BASEPATH)public$(PATHSEP)file$(PATHSEP)disxx.utility.file.MappedFile.cppm

SOURCES=\
	.$(PATHSEP)error$(PATHSEP)disxx.utility.error.NullPointerError.cpp \
	.$(PATHSEP)error$(PATHSEP)disxx.utility.error.DisassemblyError.cpp \
	.$(PATHSEP)error$(PATHSEP)disxx.utility.error.ParserError.cpp \
	.$(PATHSEP)ini$(PATHSEP)disxx.utility.ini.BaseParser.cpp \
	.$(PATHSEP)ini$(PATHSEP)disxx.utility.ini.Reader.cpp \
	.$(PATHSEP)ini$(PATHSEP)disxx.utility.ini.Writer.cpp \
	.$(PATHSEP)ini$(PATHSEP)disxx.utility.ini.Parser.cpp \
	.$(PATHSEP)file$(PATHSEP)disxx.utility.file.MappedFile.cpp

PRECOMPILED=$(addprefix $(PRECOMPILEDDIR)$(PATHSEP), $(notdir $(MODULES:.cppm=.pcm)))
MOBJECTS=$(PRECOMPILED:.pcm=.o)
OBJECTS=$(addprefix $(OBJECTSDIR)$(PATHSEP), $(notdir $(SOURCES:.cpp=.o)))

.PHONY: all
all: $(BUILDDIR)$(PATHSEP)libdisxx-util.$(DYLIB)

vpath %.cppm $(sort $(dir $(MODULES)))
vpath %.cpp $(sort $(dir $(SOURCES)))
vpath %.pcm $(sort $(dir $(PRECOMPILED)))

$(PRECOMPILEDDIR):
	$(MKDIR) $@
$(OBJECTSDIR):
	$(MKDIR) $@
$(PRECOMPILED): $(PRECOMPILEDDIR)$(PATHSEP)%.pcm: %.cppm | $(PRECOMPILEDDIR)$(PATHSEP)
	$(CXX) $(CXXFLAGS:-c=--precompile) $< -o $@
$(MOBJECTS): $(PRECOMPILEDDIR)$(PATHSEP)%.o: $(PRECOMPILEDDIR)$(PATHSEP)%.pcm | $(PRECOMPILEDDIR)$(PATHSEP)
	$(CXX) $(CXXFLAGS) $< -o $@
$(OBJECTS): $(OBJECTSDIR)$(PATHSEP)%.o: %.cpp | $(OBJECTSDIR)$(PATHSEP)
	$(CXX) $(CXXFLAGS) $< -o $@
$(OBJECTSDIR)$(PATHSEP)$(notdir $(MAPIMPL:.$(IMPLEXT)=.o)): $(MAPIMPL)
	$(MAPIMPLC) $(MAPIMPLFLAGS) $< -o $@
OBJECTS+=$(OBJECTSDIR)$(PATHSEP)$(notdir $(MAPIMPL:.$(IMPLEXT)=.o))
$(BUILDDIR)$(PATHSEP)libdisxx-util.$(DYLIB): $(MOBJECTS) $(OBJECTS)
	$(LD) $(LFLAGS) $^ -o $@

clean:
	$(RMDIR) $(BUILDDIR)
