include ../../common.mk

MODULESPATH=../modules/ui

BUILDDIR=../../../build/ui
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
	../modules/utility/public/trait/disxx.utility.trait.Cloneable.cppm \
	../modules/utility/private/error/disxx.utility.error.NullPointerError.cppm \
	../modules/utility/private/pointer/disxx.utility.pointer.DefaultDeleter.cppm \
	../modules/utility/public/pointer/disxx.utility.pointer.NonNull.cppm \
	$(MODULESPATH)/private/utility/disxx.ui.utility.ColorTag.cppm \
	$(MODULESPATH)/private/utility/disxx.ui.utility.Vec.cppm \
	$(MODULESPATH)/private/utility/disxx.ui.utility.Vertex.cppm \
	$(MODULESPATH)/private/utility/disxx.ui.utility.Renderable.cppm \
	$(MODULESPATH)/private/utility/disxx.ui.utility.Text.cppm \
	$(MODULESPATH)/private/utility/disxx.ui.utility.Shape.cppm \
	$(MODULESPATH)/private/backend/disxx.ui.backend.IRenderer.cppm \
	$(MODULESPATH)/private/backend/disxx.ui.backend.GLRenderer.cppm \
	$(MODULESPATH)/private/backend/disxx.ui.backend.IContext.cppm \
	$(MODULESPATH)/private/backend/disxx.ui.backend.GLUTContext.cppm \
	$(MODULESPATH)/public/disxx.ui.Widget.cppm \
	$(MODULESPATH)/public/disxx.ui.SourceEditor.cppm \
	$(MODULESPATH)/public/disxx.ui.Frame.cppm \
	$(MODULESPATH)/private/disxx.ui.Tab.cppm \
	$(MODULESPATH)/public/disxx.ui.TabbedPane.cppm \
	$(MODULESPATH)/private/disxx.ui.Menu-MenuEntry.cppm \
	$(MODULESPATH)/public/disxx.ui.Button.cppm \
	$(MODULESPATH)/public/disxx.ui.Label.cppm \
	$(MODULESPATH)/public/disxx.ui.Menu.cppm \
	$(MODULESPATH)/public/disxx.ui.MenuBar.cppm \
	$(MODULESPATH)/public/disxx.ui.TextInput.cppm \
	$(MODULESPATH)/public/disxx.ui.MainWindow.cppm \
	$(MODULESPATH)/public/disxx.ui.MessageBox.cppm

SOURCES=\
	./utility/disxx.ui.utility.ColorTag.cpp \
	./utility/disxx.ui.utility.Renderable.cpp \
	./utility/disxx.ui.utility.Text.cpp \
	./utility/disxx.ui.utility.Shape.cpp \
	./backend/disxx.ui.backend.GLRenderer.cpp \
	./backend/disxx.ui.backend.GLUTContext.cpp \
	./disxx.ui.Widget.cpp \
	./disxx.ui.Frame.cpp \
	./disxx.ui.Tab.cpp \
	./disxx.ui.TabbedPane.cpp \
	./disxx.ui.Button.cpp \
	./disxx.ui.Label.cpp \
	./disxx.ui.Menu-MenuEntry.cpp \
	./disxx.ui.Menu.cpp \
	./disxx.ui.MenuBar.cpp \
	./disxx.ui.TextInput.cpp \
	./disxx.ui.SourceEditor.cpp \
	./disxx.ui.MainWindow.cpp \
	./disxx.ui.MessageBox.cpp

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
	make -C ../utility
	$(MOVE) ../../../build/utility/libdisxx-utility.$(DYLIB) $@
$(BUILDDIR)/libdisxx-ui.$(DYLIB): $(MOBJECTS) $(OBJECTS) | $(DEPENDENCIES)
	$(LD) $(LFLAGS) $^ -o $@

clean:
	$(RMDIR) $(BUILDDIR)
