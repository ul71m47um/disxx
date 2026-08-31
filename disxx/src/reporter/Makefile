include ../../common.mk

BUILDDIR=../../../build/reporter
DEPENDENCIESDIR=$(BUILDDIR)/dependencies
PRECOMPILEDDIR=$(BUILDDIR)/precompiled
OBJECTSDIR=$(BUILDDIR)/objects

CXXFLAGS+=\
	-fprebuilt-module-path=$(PRECOMPILEDDIR) -DGL_SILENCE_DEPRECATION -DBACKEND_CTX_GLUT \
	-Wno-non-virtual-dtor -Wno-c99-extensions -Wno-unused-command-line-argument -Wno-writable-strings \
	-Wno-reserved-macro-identifier -Wno-c++98-compat -Wno-weak-vtables -Wno-reserved-identifier \
	-Wno-poison-system-directories -Wno-padded -Wno-implicit-int-float-conversion -Wno-undef

LFLAGS+=-pie -L$(DEPENDENCIESDIR) -ldisxx-utility -ldisxx-ui
ifeq ($(OS),Darwin)
	LFLAGS+=-S -framework GLUT
else
	LFLAGS+=-lglut -rpath .
endif

MODULES=\
	$(LIBCXX) \
	../modules/utility/public/trait/disxx.utility.trait.Cloneable.cppm \
	../modules/utility/private/error/disxx.utility.error.NullPointerError.cppm \
	../modules/utility/private/error/disxx.utility.error.ParserError.cppm \
	../modules/utility/private/ini/disxx.utility.ini.BaseParser.cppm \
	../modules/utility/private/ini/disxx.utility.ini.Reader.cppm \
	../modules/utility/private/ini/disxx.utility.ini.Writer.cppm \
	../modules/utility/private/pointer/disxx.utility.pointer.DefaultDeleter.cppm \
	../modules/utility/public/pointer/disxx.utility.pointer.NonNull.cppm \
	../modules/utility/public/ini/disxx.utility.ini.Parser.cppm \
	../modules/ui/private/utility/disxx.ui.utility.Vec.cppm \
	../modules/ui/private/utility/disxx.ui.utility.Vertex.cppm \
	../modules/ui/private/utility/disxx.ui.utility.ColorTag.cppm \
	../modules/ui/private/renderable/disxx.ui.renderable.Renderable.cppm \
	../modules/ui/private/renderable/disxx.ui.renderable.Text.cppm \
	../modules/ui/private/renderable/disxx.ui.renderable.Shape.cppm \
	../modules/ui/private/renderable/disxx.ui.renderable.Triangle.cppm \
	../modules/ui/private/renderable/disxx.ui.renderable.Rectangle.cppm \
	../modules/ui/private/backend/disxx.ui.backend.IRenderer.cppm \
	../modules/ui/private/backend/disxx.ui.backend.GLRenderer.cppm \
	../modules/ui/private/backend/disxx.ui.backend.IContext.cppm \
	../modules/ui/private/backend/disxx.ui.backend.GLUTContext.cppm \
	../modules/ui/public/disxx.ui.Widget.cppm \
	../modules/ui/public/disxx.ui.Button.cppm \
	../modules/ui/public/disxx.ui.Label.cppm \
	../modules/ui/private/disxx.ui.MenuEntry.cppm \
	../modules/ui/private/disxx.ui.Menu.cppm \
	../modules/ui/public/disxx.ui.MenuBar.cppm \
	../modules/ui/public/disxx.ui.SourceEditor.cppm \
	../modules/ui/public/disxx.ui.MainWindow.cppm \
	./FailHandler/FailHandler.cppm

SOURCES=\
	./FailHandler/FailHandler.cpp \
	./main.cpp

PRECOMPILED=$(addprefix $(PRECOMPILEDDIR)/, $(notdir $(MODULES:.cppm=.pcm)))
MOBJECTS=$(PRECOMPILED:.pcm=.o)
OBJECTS=$(addprefix $(OBJECTSDIR)/, $(notdir $(SOURCES:.cpp=.o)))

__DYLIBS=libdisxx-utility.$(DYLIB) libdisxx-ui.$(DYLIB)
DYLIBS=$(addprefix $(DEPENDENCIESDIR)/, $(__DYLIBS))

.PHONY: all
all: $(BUILDDIR)/reporter

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
	$(CXX) $(CXXFLAGS:-c=--precompile) $< -o $@
$(MOBJECTS): $(PRECOMPILEDDIR)/%.o: $(PRECOMPILEDDIR)/%.pcm | $(PRECOMPILEDDIR)
	$(CXX) $(CXXFLAGS) $< -o $@
$(OBJECTS): $(OBJECTSDIR)/%.o: %.cpp | $(OBJECTSDIR)
	$(CXX) $(CXXFLAGS) $< -o $@
$(DEPENDENCIESDIR)/libdisxx-utility.$(DYLIB): | $(DEPENDENCIESDIR)
	make -C ../utility/
	$(MOVE) ../../../build/utility/$(notdir $@) $@
$(DEPENDENCIESDIR)/libdisxx-ui.$(DYLIB): | $(DEPENDENCIESDIR)
	make -C ../ui/
	$(MOVE) ../../../build/ui/$(notdir $@) $@
$(BUILDDIR)/reporter: $(MOBJECTS) $(OBJECTS) | $(DYLIBS)
	$(LD) $(LFLAGS) $^ -o $@

clean:
	$(RMDIR) $(BUILDDIR)
