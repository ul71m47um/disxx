include ../../common.mk

BUILDDIR=./build
DEPENDENCIESDIR=$(BUILDDIR)/dependencies
PRECOMPILEDDIR=$(BUILDDIR)/precompiled
OBJECTSDIR=$(BUILDDIR)/objects

CXXFLAGS+=\
	-O3 -fPIE -fprebuilt-module-path=$(PRECOMPILEDDIR) -DGL_SILENCE_DEPRECATION -DBACKEND_CTX_GLUT -DNDEBUG -I../third-party \
	-Wno-unused-command-line-argument -Wno-reserved-identifier -Wno-weak-vtables -Wno-non-virtual-dtor -Wno-padded -Wno-c++98-compat \
	-Wno-c++98-compat-pedantic -Wno-poison-system-directories -Wno-cast-function-type-mismatch -Wno-decls-in-multiple-modules
ifneq ($(OS),Darwin)
	CXXFLAGS+=\
		$(shell $(RUBY) ../../misc/config.rb --cflags) \
		-Wno-missing-include-dirs
endif

LFLAGS+=-O2 -pie -L$(DEPENDENCIESDIR) -ldisxx-utility -ldisxx-ui -ldisxx-disasm -ldisxx-macho
ifeq ($(OS),Darwin)
	LFLAGS+=-S -framework Ruby -framework GLUT
else
	LFLAGS+=\
		$(shell $(RUBY) ../../misc/config.rb --ldflags) \
		-lglut -rpath .
endif

MODULES=\
	$(LIBCXX) \
	../modules/utility/public/trait/disxx.utility.trait.Cloneable.cppm \
	../modules/utility/private/error/disxx.utility.error.DisassemblyError.cppm \
	../modules/utility/private/error/disxx.utility.error.NullPointerError.cppm \
	../modules/utility/private/error/disxx.utility.error.ParserError.cppm \
	../modules/utility/private/pointer/disxx.utility.pointer.DefaultDeleter.cppm \
	../modules/utility/private/ini/disxx.utility.ini.BaseParser.cppm \
	../modules/utility/private/ini/disxx.utility.ini.Reader.cppm \
	../modules/utility/private/ini/disxx.utility.ini.Writer.cppm \
	../modules/utility/public/pointer/disxx.utility.pointer.NonNull.cppm \
	../modules/utility/public/ini/disxx.utility.ini.Parser.cppm \
	../modules/utility/public/file/disxx.utility.file.MappedFile.cppm \
	../modules/disasm/private/disxx.disasm.InstructionIdentifier.cppm \
	../modules/disasm/private/operand/disxx.disasm.operand.IOperand.cppm \
	../modules/disasm/private/operand/disxx.disasm.operand.Register-VectorArrangementSpecifier.cppm \
	../modules/disasm/private/operand/disxx.disasm.operand.Register.cppm \
	../modules/disasm/private/operand/disxx.disasm.operand.Immediate.cppm \
	../modules/disasm/private/operand/disxx.disasm.operand.Extension.cppm \
	../modules/disasm/private/operand/disxx.disasm.operand.PState.cppm \
	../modules/disasm/private/operand/disxx.disasm.operand.Shift.cppm \
	../modules/disasm/private/operand/disxx.disasm.operand.LoadsAndStoresAddress.cppm \
	../modules/disasm/private/operand/disxx.disasm.operand.PrefetchOperand.cppm \
	../modules/disasm/private/operand/disxx.disasm.operand.SystemOperand.cppm \
	../modules/disasm/private/operand/disxx.disasm.operand.MemoryBarrier.cppm \
	../modules/disasm/private/operand/disxx.disasm.operand.Condition.cppm \
	../modules/disasm/private/disxx.disasm.Address.cppm \
	../modules/disasm/private/disxx.disasm.Bytes.cppm \
	../modules/disasm/private/disxx.disasm.Instruction.cppm \
	../modules/disasm/public/disxx.disasm.Disassembler.cppm \
	../modules/disasm/public/disxx.disasm.Printer.cppm \
	../modules/ui/private/utility/disxx.ui.utility.Vec.cppm \
	../modules/ui/private/utility/disxx.ui.utility.Vertex.cppm \
	../modules/ui/private/utility/disxx.ui.utility.ColorTag.cppm \
	../modules/ui/utility/disxx.ui.utility.Renderable.cppm \
	../modules/ui/utility/disxx.ui.utility.Text.cppm \
	../modules/ui/utility/disxx.ui.utility.Shape.cppm \
	../modules/ui/private/backend/disxx.ui.backend.IRenderer.cppm \
	../modules/ui/private/backend/disxx.ui.backend.GLRenderer.cppm \
	../modules/ui/private/backend/disxx.ui.backend.IContext.cppm \
	../modules/ui/private/backend/disxx.ui.backend.GLUTContext.cppm \
	../modules/ui/public/disxx.ui.Widget.cppm \
	../modules/ui/public/disxx.ui.Frame.cppm \
	../modules/ui/public/disxx.ui.Button.cppm \
	../modules/ui/public/disxx.ui.Label.cppm \
	../modules/ui/private/disxx.ui.MenuEntry.cppm \
	../modules/ui/public/disxx.ui.Menu.cppm \
	../modules/ui/public/disxx.ui.SourceEditor.cppm \
	../modules/ui/private/disxx.ui.Tab.cppm \
	../modules/ui/public/disxx.ui.TabbedPane.cppm \
	../modules/ui/public/disxx.ui.TextInput.cppm \
	../modules/ui/public/disxx.ui.MainWindow.cppm \
	 ../modules/ui/public/disxx.ui.MessageBox.cppm \
	../modules/loader/private/utility/disxx.loader.utility.BinaryInfo.cppm \
	../modules/loader/private/executable/disxx.loader.executable.Label.cppm \
	../modules/loader/private/executable/disxx.loader.executable.Section.cppm \
	../modules/loader/public/executable/disxx.loader.executable.ExecutableFile.cppm \
	../modules/loader/public/disxx.loader.macho.Loader.cppm \
	./ScriptEngine/ScriptEngine.cppm \
	./Core/DisLog.cppm \
	./FileInput/FileInput.cppm \
	./Core/Application.cppm

SOURCES=\
	./ScriptEngine/ScriptEngine.cpp \
	./Core/DisLog.cpp \
	./FileInput/FileInput.cpp \
	./Core/Application.cpp \
	./main.cpp

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
	make -C ../utility/
	$(MOVE) ../utility/build/$(notdir $@) $@
$(DEPENDENCIESDIR)/libdisxx-ui.$(DYLIB): | $(DEPENDENCIESDIR)
	make -C ../ui/
	$(MOVE) ../ui/build/$(notdir $@) $@
$(DEPENDENCIESDIR)/libdisxx-macho.$(DYLIB): | $(DEPENDENCIESDIR)
	make -C ../loader/
	$(MOVE) ../loader/build/$(notdir $@) $@
$(DEPENDENCIESDIR)/libdisxx-disasm.$(DYLIB): | $(DEPENDENCIESDIR)
	make -C ../disasm/
	$(MOVE) ../disasm/build/$(notdir $@) $@
$(BUILDDIR)/dis++: $(MOBJECTS) $(OBJECTS) | $(DYLIBS)
	$(LD) $(LFLAGS) $^ -o $@

clean:
	$(RMDIR) $(BUILDDIR)
