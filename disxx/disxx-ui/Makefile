include ../common.mk

MODULESPATH=./modules

BUILDDIR=../../build/disxx-ui
DEPENDENCIESDIR=$(BUILDDIR)/dependencies
PRECOMPILEDDIR=$(BUILDDIR)/precompiled
OBJECTSDIR=$(BUILDDIR)/objects

CXXFLAGS+=\
	-fPIC -fprebuilt-module-path=$(PRECOMPILEDDIR) -DGL_SILENCE_DEPRECATION -DBACKEND_CTX_GLUT \
	-Wno-writable-strings -Wno-unused-command-line-argument -Wno-c99-extensions -Wno-global-constructors \
	-Wno-exit-time-destructors -Wno-reserved-identifier -Wno-non-virtual-dtor -Wno-switch-enum \
	-Wno-reserved-macro-identifier -Wno-writable-strings -Wno-weak-vtables -Wno-undefined-func-template \
	-Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-covered-switch-default -Wno-padded -Wno-sign-conversion \
	-Wno-float-conversion -Wno-implicit-int-float-conversion -Wno-poison-system-directories

LFLAGS+=-L$(DEPENDENCIESDIR) -ldisxx-utility
ifeq ($(OS),Darwin)
	LFLAGS+=-dylib -S -install_name @executable_path/../Frameworks/libdisxx-ui.$(DYLIB) \
		-framework OpenGL -framework GLUT
else
	LFLAGS+=-shared -lGL -lGLU -lglut
	ifneq ($(OS),Windows_NT)
		LFLAGS+=-rpath $$ORIGIN/libdisxx-ui.$(DYLIB)
	endif
endif

MODULES=\
	$(LIBCXX) \
	../disxx-utility/modules/public/disxx.utility.Overload.cppm \
	../disxx-utility/modules/public/trait/disxx.utility.trait.IClone.cppm \
	../disxx-utility/modules/private/error/disxx.utility.error.NullPointerError.cppm \
	../disxx-utility/modules/private/pointer/disxx.utility.pointer.Pointer.cppm \
	../disxx-utility/modules/private/pointer/disxx.utility.pointer.Weak.cppm \
	../disxx-utility/modules/private/pointer/disxx.utility.pointer.DefaultDeleter.cppm \
	../disxx-utility/modules/public/pointer/disxx.utility.pointer.NonNull.cppm \
	$(MODULESPATH)/private/utility/disxx.ui.utility.ColorTag.cppm \
	$(MODULESPATH)/private/utility/disxx.ui.utility.Vec.cppm \
	$(MODULESPATH)/private/utility/disxx.ui.utility.Vertex.cppm \
	$(MODULESPATH)/private/renderable/disxx.ui.renderable.Renderable.cppm \
	$(MODULESPATH)/private/renderable/disxx.ui.renderable.Text.cppm \
	$(MODULESPATH)/private/renderable/disxx.ui.renderable.Shape.cppm \
	$(MODULESPATH)/private/renderable/disxx.ui.renderable.Triangle.cppm \
	$(MODULESPATH)/private/renderable/disxx.ui.renderable.Rectangle.cppm \
	$(MODULESPATH)/private/backend/event/disxx.ui.backend.event.MouseButton.cppm \
	$(MODULESPATH)/private/backend/event/disxx.ui.backend.event.MouseMotion.cppm \
	$(MODULESPATH)/private/backend/event/disxx.ui.backend.event.Keyboard.cppm \
	$(MODULESPATH)/private/backend/event/disxx.ui.backend.event.Reshape.cppm \
	$(MODULESPATH)/private/backend/event/disxx.ui.backend.event.Queue.cppm \
	$(MODULESPATH)/private/backend/abstract/disxx.ui.backend.abstract.IRenderer.cppm \
	$(MODULESPATH)/private/backend/opengl/disxx.ui.backend.opengl.Renderer.cppm \
	$(MODULESPATH)/private/backend/abstract/disxx.ui.backend.abstract.IManager.cppm \
	$(MODULESPATH)/private/backend/abstract/disxx.ui.backend.abstract.Window.cppm \
	$(MODULESPATH)/private/backend/glut/disxx.ui.backend.glut.Manager.cppm \
	$(MODULESPATH)/private/backend/glut/disxx.ui.backend.glut.Window.cppm \
	$(MODULESPATH)/private/backend/abstract/disxx.ui.backend.abstract.IContext.cppm \
	$(MODULESPATH)/private/backend/glut/disxx.ui.backend.glut.Context.cppm \
	$(MODULESPATH)/public/disxx.ui.Widget.cppm \
	$(MODULESPATH)/public/disxx.ui.BoxLayout.cppm \
	$(MODULESPATH)/public/disxx.ui.TextView.cppm \
	$(MODULESPATH)/public/disxx.ui.Frame.cppm \
	$(MODULESPATH)/private/disxx.ui.Tab.cppm \
	$(MODULESPATH)/public/disxx.ui.TabWidget.cppm \
	$(MODULESPATH)/private/disxx.ui.MenuEntry.cppm \
	$(MODULESPATH)/public/disxx.ui.Button.cppm \
	$(MODULESPATH)/private/disxx.ui.TreeItem.cppm \
	$(MODULESPATH)/private/disxx.ui.Tree.cppm \
	$(MODULESPATH)/public/disxx.ui.Label.cppm \
	$(MODULESPATH)/private/disxx.ui.Menu.cppm \
	$(MODULESPATH)/public/disxx.ui.MenuBar.cppm \
	$(MODULESPATH)/public/disxx.ui.TextInput.cppm \
	$(MODULESPATH)/public/disxx.ui.MainWindow.cppm \
	$(MODULESPATH)/public/disxx.ui.MessageBox.cppm

SOURCES=\
	./src/utility/disxx.ui.utility.ColorTag.cpp \
	./src/renderable/disxx.ui.renderable.Renderable.cpp \
	./src/renderable/disxx.ui.renderable.Text.cpp \
	./src/renderable/disxx.ui.renderable.Shape.cpp \
	./src/renderable/disxx.ui.renderable.Triangle.cpp \
	./src/renderable/disxx.ui.renderable.Rectangle.cpp \
	./src/backend/opengl/disxx.ui.backend.opengl.Renderer.cpp \
	./src/backend/event/disxx.ui.backend.event.MouseMotion.cpp \
	./src/backend/event/disxx.ui.backend.event.MouseButton.cpp \
	./src/backend/event/disxx.ui.backend.event.Keyboard.cpp \
	./src/backend/event/disxx.ui.backend.event.Reshape.cpp \
	./src/backend/glut/disxx.ui.backend.glut.Manager.cpp \
	./src/backend/glut/disxx.ui.backend.glut.Context.cpp \
	./src/backend/glut/disxx.ui.backend.glut.Window.cpp \
	./src/disxx.ui.Widget.cpp \
	./src/disxx.ui.BoxLayout.cpp \
	./src/disxx.ui.Frame.cpp \
	./src/disxx.ui.Tab.cpp \
	./src/disxx.ui.TabWidget.cpp \
	./src/disxx.ui.Button.cpp \
	./src/disxx.ui.TreeItem.cpp \
	./src/disxx.ui.Tree.cpp \
	./src/disxx.ui.Label.cpp \
	./src/disxx.ui.MenuEntry.cpp \
	./src/disxx.ui.Menu.cpp \
	./src/disxx.ui.MenuBar.cpp \
	./src/disxx.ui.TextInput.cpp \
	./src/disxx.ui.TextView.cpp \
	./src/disxx.ui.MainWindow.cpp \
	./src/disxx.ui.MessageBox.cpp

.PHONY: all
all: $(BUILDDIR)/libdisxx-ui.$(DYLIB)

vpath %.cppm $(sort $(dir $(MODULES)))
vpath %.cpp $(sort $(dir $(SOURCES)))
vpath %.pcm $(sort $(dir $(PRECOMPILED)))

PRECOMPILED=$(addprefix $(PRECOMPILEDDIR)/,  $(notdir $(MODULES:.cppm=.pcm)))
MOBJECTS=$(PRECOMPILED:.pcm=.o)
OBJECTS=$(addprefix $(OBJECTSDIR)/, $(notdir $(SOURCES:.cpp=.o)))

DEPENDENCIES=$(DEPENDENCIESDIR)/libdisxx-utility.$(DYLIB)

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
	make -C ../disxx-utility
	$(MOVE) ../../build/disxx-utility/libdisxx-utility.$(DYLIB) $@
$(BUILDDIR)/libdisxx-ui.$(DYLIB): $(MOBJECTS) $(OBJECTS) | $(DEPENDENCIES)
	$(LD) $(LFLAGS) $^ -o $@

clean:
	$(RMDIR) $(BUILDDIR)
