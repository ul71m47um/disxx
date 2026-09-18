include ../common.mk

BUILDDIR=../../build/disxx-reporter
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
	../disxx-utility/modules/public/disxx.utility.Overload.cppm \
	../disxx-utility/modules/public/trait/disxx.utility.trait.IClone.cppm \
	../disxx-utility/modules/private/error/disxx.utility.error.NullPointerError.cppm \
	../disxx-utility/modules/private/error/disxx.utility.error.ParserError.cppm \
	../disxx-utility/modules/private/ini/disxx.utility.ini.BaseParser.cppm \
	../disxx-utility/modules/private/ini/disxx.utility.ini.Reader.cppm \
	../disxx-utility/modules/private/ini/disxx.utility.ini.Writer.cppm \
	../disxx-utility/modules/private/pointer/disxx.utility.pointer.DefaultDeleter.cppm \
	../disxx-utility/modules/public/pointer/disxx.utility.pointer.NonNull.cppm \
	../disxx-utility/modules/public/pointer/disxx.utility.pointer.Pointer.cppm \
	../disxx-utility/modules/public/pointer/disxx.utility.pointer.Weak.cppm \
	../disxx-utility/modules/public/ini/disxx.utility.ini.Parser.cppm \
	../disxx-ui/modules/private/utility/disxx.ui.utility.Vec.cppm \
	../disxx-ui/modules/private/utility/disxx.ui.utility.Vertex.cppm \
	../disxx-ui/modules/private/utility/disxx.ui.utility.ColorTag.cppm \
	../disxx-ui/modules/private/renderable/disxx.ui.renderable.Renderable.cppm \
	../disxx-ui/modules/private/renderable/disxx.ui.renderable.Text.cppm \
	../disxx-ui/modules/private/renderable/disxx.ui.renderable.Shape.cppm \
	../disxx-ui/modules/private/renderable/disxx.ui.renderable.Triangle.cppm \
	../disxx-ui/modules/private/renderable/disxx.ui.renderable.Rectangle.cppm \
	../disxx-ui/modules/private/backend/event/disxx.ui.backend.event.MouseMotion.cppm \
	../disxx-ui/modules/private/backend/event/disxx.ui.backend.event.MouseButton.cppm \
	../disxx-ui/modules/private/backend/event/disxx.ui.backend.event.Keyboard.cppm \
	../disxx-ui/modules/private/backend/event/disxx.ui.backend.event.Reshape.cppm \
	../disxx-ui/modules/private/backend/event/disxx.ui.backend.event.Queue.cppm \
	../disxx-ui/modules/private/backend/abstract/disxx.ui.backend.abstract.IRenderer.cppm \
	../disxx-ui/modules/private/backend/abstract/disxx.ui.backend.abstract.IManager.cppm \
	../disxx-ui/modules/private/backend/abstract/disxx.ui.backend.abstract.IContext.cppm \
	../disxx-ui/modules/private/backend/abstract/disxx.ui.backend.abstract.Window.cppm \
	../disxx-ui/modules/private/backend/opengl/disxx.ui.backend.opengl.Renderer.cppm \
	../disxx-ui/modules/private/backend/glut/disxx.ui.backend.glut.Manager.cppm \
	../disxx-ui/modules/private/backend/glut/disxx.ui.backend.glut.Window.cppm \
	../disxx-ui/modules/private/backend/glut/disxx.ui.backend.glut.Context.cppm \
	../disxx-ui/modules/public/disxx.ui.Widget.cppm \
	../disxx-ui/modules/public/disxx.ui.Button.cppm \
	../disxx-ui/modules/public/disxx.ui.Label.cppm \
	../disxx-ui/modules/private/disxx.ui.MenuEntry.cppm \
	../disxx-ui/modules/private/disxx.ui.Menu.cppm \
	../disxx-ui/modules/public/disxx.ui.MenuBar.cppm \
	../disxx-ui/modules/public/disxx.ui.TextView.cppm \
	../disxx-ui/modules/public/disxx.ui.MainWindow.cppm \
	./src/FailHandler/FailHandler.cppm

SOURCES=\
	./src/FailHandler/FailHandler.cpp \
	./src/main.cpp

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
	make -C ../disxx-utility/
	$(MOVE) ../../build/disxx-utility/$(notdir $@) $@
$(DEPENDENCIESDIR)/libdisxx-ui.$(DYLIB): | $(DEPENDENCIESDIR)
	make -C ../disxx-ui/
	$(MOVE) ../../build/disxx-ui/$(notdir $@) $@
$(BUILDDIR)/reporter: $(MOBJECTS) $(OBJECTS) | $(DYLIBS)
	$(LD) $(LFLAGS) $^ -o $@

clean:
	$(RMDIR) $(BUILDDIR)
