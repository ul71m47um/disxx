include ../common.mk

BUILDDIR=../../build/disxx-app
DEPENDENCIESDIR=$(BUILDDIR)/dependencies
PRECOMPILEDDIR=$(BUILDDIR)/precompiled
OBJECTSDIR=$(BUILDDIR)/objects

CXXFLAGS+=\
	-fPIE -fprebuilt-module-path=$(PRECOMPILEDDIR) -DGL_SILENCE_DEPRECATION -DBACKEND_CTX_GLUT -I../include/third-party \
	-Wno-unused-command-line-argument -Wno-reserved-identifier -Wno-weak-vtables -Wno-non-virtual-dtor -Wno-padded -Wno-c++98-compat \
	-Wno-c++98-compat-pedantic -Wno-poison-system-directories -Wno-cast-function-type-mismatch -Wno-decls-in-multiple-modules
ifneq ($(OS),Darwin)
	CXXFLAGS+=\
		$(shell $(RUBY) ../../misc/config.rb --cflags) \
		-Wno-missing-include-dirs
endif

LFLAGS+=-pie -L$(DEPENDENCIESDIR) -ldisxx-utility -ldisxx-ui -ldisxx-disasm -ldisxx-macho
ifeq ($(OS),Darwin)
	LFLAGS+=-S -framework Ruby -framework GLUT
else
	LFLAGS+=\
		$(shell $(RUBY) ../../misc/config.rb --ldflags) \
		-lglut -rpath .
endif

MODULES=\
	$(LIBCXX) \
	../disxx-utility/modules/public/disxx.utility.Overload.cppm \
	../disxx-utility/modules/public/trait/disxx.utility.trait.IClone.cppm \
	../disxx-utility/modules/private/error/disxx.utility.error.DisassemblyError.cppm \
	../disxx-utility/modules/private/error/disxx.utility.error.NullPointerError.cppm \
	../disxx-utility/modules/private/error/disxx.utility.error.ParserError.cppm \
	../disxx-utility/modules/private/pointer/disxx.utility.pointer.DefaultDeleter.cppm \
	../disxx-utility/modules/private/ini/disxx.utility.ini.BaseParser.cppm \
	../disxx-utility/modules/private/ini/disxx.utility.ini.Reader.cppm \
	../disxx-utility/modules/private/ini/disxx.utility.ini.Writer.cppm \
	../disxx-utility/modules/public/pointer/disxx.utility.pointer.NonNull.cppm \
	../disxx-utility/modules/public/pointer/disxx.utility.pointer.Pointer.cppm \
	../disxx-utility/modules/public/pointer/disxx.utility.pointer.Weak.cppm \
	../disxx-utility/modules/public/ini/disxx.utility.ini.Parser.cppm \
	../disxx-utility/modules/public/file/disxx.utility.file.MappedFile.cppm \
	../disxx-disasm/modules/private/disxx.disasm.InstructionIdentifier.cppm \
	../disxx-disasm/modules/private/operand/disxx.disasm.operand.IOperand.cppm \
	../disxx-disasm/modules/private/operand/disxx.disasm.operand.Register-VectorArrangementSpecifier.cppm \
	../disxx-disasm/modules/private/operand/disxx.disasm.operand.Register.cppm \
	../disxx-disasm/modules/private/operand/disxx.disasm.operand.Immediate.cppm \
	../disxx-disasm/modules/private/operand/disxx.disasm.operand.Extension.cppm \
	../disxx-disasm/modules/private/operand/disxx.disasm.operand.PState.cppm \
	../disxx-disasm/modules/private/operand/disxx.disasm.operand.Shift.cppm \
	../disxx-disasm/modules/private/operand/disxx.disasm.operand.LoadsAndStoresAddress.cppm \
	../disxx-disasm/modules/private/operand/disxx.disasm.operand.PrefetchOperand.cppm \
	../disxx-disasm/modules/private/operand/disxx.disasm.operand.SystemOperand.cppm \
	../disxx-disasm/modules/private/operand/disxx.disasm.operand.MemoryBarrier.cppm \
	../disxx-disasm/modules/private/operand/disxx.disasm.operand.Condition.cppm \
	../disxx-disasm/modules/private/disxx.disasm.Address.cppm \
	../disxx-disasm/modules/private/disxx.disasm.Bytes.cppm \
	../disxx-disasm/modules/private/disxx.disasm.Instruction.cppm \
	../disxx-disasm/modules/public/disxx.disasm.Disassembler.cppm \
	../disxx-disasm/modules/public/disxx.disasm.Printer.cppm \
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
	../disxx-ui/modules/public/disxx.ui.BoxLayout.cppm \
	../disxx-ui/modules/public/disxx.ui.Frame.cppm \
	../disxx-ui/modules/public/disxx.ui.Button.cppm \
	../disxx-ui/modules/private/disxx.ui.TreeItem.cppm \
	../disxx-ui/modules/public/disxx.ui.Tree.cppm \
	../disxx-ui/modules/public/disxx.ui.Label.cppm \
	../disxx-ui/modules/private/disxx.ui.MenuEntry.cppm \
	../disxx-ui/modules/private/disxx.ui.Menu.cppm \
	../disxx-ui/modules/public/disxx.ui.MenuBar.cppm \
	../disxx-ui/modules/public/disxx.ui.TextView.cppm \
	../disxx-ui/modules/private/disxx.ui.Tab.cppm \
	../disxx-ui/modules/public/disxx.ui.TabWidget.cppm \
	../disxx-ui/modules/public/disxx.ui.TextInput.cppm \
	../disxx-ui/modules/public/disxx.ui.MainWindow.cppm \
	../disxx-ui/modules/public/disxx.ui.MessageBox.cppm \
	../disxx-loader/modules/private/utility/disxx.loader.utility.BinaryInfo.cppm \
	../disxx-loader/modules/private/executable/disxx.loader.executable.Label.cppm \
	../disxx-loader/modules/private/executable/disxx.loader.executable.Section.cppm \
	../disxx-loader/modules/public/executable/disxx.loader.executable.ExecutableFile.cppm \
	../disxx-loader/modules/public/disxx.loader.macho.Loader.cppm \
	./src/ScriptEngine/ScriptEngine.cppm \
	./src/ScriptWindow/ScriptWindow.cppm \
	./src/Core/DisLog.cppm \
	./src/Core/Application.cppm

SOURCES=\
	./src/ScriptEngine/ScriptEngine.cpp \
	./src/ScriptWindow/ScriptWindow.cpp \
	./src/Core/DisLog.cpp \
	./src/Core/Application.cpp \
	./src/main.cpp

PRECOMPILED=$(addprefix $(PRECOMPILEDDIR)/, $(notdir $(MODULES:.cppm=.pcm)))
MOBJECTS=$(PRECOMPILED:.pcm=.o)
OBJECTS=$(addprefix $(OBJECTSDIR)/, $(notdir $(SOURCES:.cpp=.o)))

__DYLIBS=libdisxx-utility.$(DYLIB) libdisxx-ui.$(DYLIB) libdisxx-macho.$(DYLIB) libdisxx-disasm.$(DYLIB)
DYLIBS=$(addprefix $(DEPENDENCIESDIR)/, $(__DYLIBS))

.PHONY: all
all: $(BUILDDIR)/dis++

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
$(DEPENDENCIESDIR)/libdisxx-macho.$(DYLIB): | $(DEPENDENCIESDIR)
	make -C ../disxx-loader/
	$(MOVE) ../../build/disxx-loader/$(notdir $@) $@
$(DEPENDENCIESDIR)/libdisxx-disasm.$(DYLIB): | $(DEPENDENCIESDIR)
	make -C ../disxx-disasm/
	$(MOVE) ../../build/disxx-disasm/$(notdir $@) $@
$(BUILDDIR)/dis++: $(MOBJECTS) $(OBJECTS) | $(DYLIBS)
	$(LD) $(LFLAGS) $^ -o $@

clean:
	$(RMDIR) $(BUILDDIR)
