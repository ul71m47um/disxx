ifeq ($(shell echo %OS%), Windows_NT)
	include ..\\common.mk
else
	include ../common.mk
endif

BUILDDIR=.$(PATHSEP)build
DEPENDENCIESDIR=$(BUILDDIR)$(PATHSEP)dependencies
PRECOMPILEDDIR=$(BUILDDIR)$(PATHSEP)precompiled
OBJECTSDIR=$(BUILDDIR)$(PATHSEP)objects

CXXFLAGS+=\
	-O3 -fPIE -fprebuilt-module-path=$(PRECOMPILEDDIR) -DGL_SILENCE_DEPRECATION -DBACKEND_CTX_GLUT -DNDEBUG -I..$(PATHSEP)third-party \
	-Wno-unused-command-line-argument -Wno-c99-extensions -Wno-global-constructors -Wno-exit-time-destructors \
	-Wno-reserved-identifier -Wno-switch-enum -Wno-reserved-macro-identifier -Wno-writable-strings -Wno-weak-vtables \
	-Wno-non-virtual-dtor -Wno-covered-switch-default -Wno-padded -Wno-sign-conversion -Wno-c++98-compat -Wno-c++98-compat-pedantic \
	-Wno-implicit-int-float-conversion -Wno-disabled-macro-expansion -Wno-cast-function-type-strict -Wno-compound-token-split-by-macro \
	-Wno-poison-system-directories -Wno-cast-function-type-mismatch -Wno-decls-in-multiple-modules
ifneq ($(OS),Darwin)
	CXXFLAGS+=-I$(shell ruby ..$(PATHSEP)..$(PATHSEP)misc$(PATHSEP)config.rb)
endif

LFLAGS+=-O2 -pie -L$(DEPENDENCIESDIR) -ldisxx-util -ldisxx-ui -ldisxx-disasm -ldisxx-macho
ifeq ($(OS),Darwin)
	LFLAGS+=-S -framework Ruby -framework GLUT
else
	LFLAGS+=-lruby*.so* -lglut
endif

MODULES=\
	$(LIBCXX) \
	..$(PATHSEP)modules$(PATHSEP)utility$(PATHSEP)public$(PATHSEP)trait$(PATHSEP)disxx.utility.trait.Cloneable.cppm \
	..$(PATHSEP)modules$(PATHSEP)utility$(PATHSEP)private$(PATHSEP)error$(PATHSEP)disxx.utility.error.DisassemblyError.cppm \
	..$(PATHSEP)modules$(PATHSEP)utility$(PATHSEP)private$(PATHSEP)error$(PATHSEP)disxx.utility.error.NullPointerError.cppm \
	..$(PATHSEP)modules$(PATHSEP)utility$(PATHSEP)private$(PATHSEP)error$(PATHSEP)disxx.utility.error.ParserError.cppm \
	..$(PATHSEP)modules$(PATHSEP)utility$(PATHSEP)private$(PATHSEP)pointer$(PATHSEP)disxx.utility.pointer.DefaultDeleter.cppm \
	..$(PATHSEP)modules$(PATHSEP)utility$(PATHSEP)private$(PATHSEP)ini$(PATHSEP)disxx.utility.ini.BaseParser.cppm \
	..$(PATHSEP)modules$(PATHSEP)utility$(PATHSEP)private$(PATHSEP)ini$(PATHSEP)disxx.utility.ini.Reader.cppm \
	..$(PATHSEP)modules$(PATHSEP)utility$(PATHSEP)private$(PATHSEP)ini$(PATHSEP)disxx.utility.ini.Writer.cppm \
	..$(PATHSEP)modules$(PATHSEP)utility$(PATHSEP)public$(PATHSEP)pointer$(PATHSEP)disxx.utility.pointer.NonNull.cppm \
	..$(PATHSEP)modules$(PATHSEP)utility$(PATHSEP)public$(PATHSEP)ini$(PATHSEP)disxx.utility.ini.Parser.cppm \
	..$(PATHSEP)modules$(PATHSEP)utility$(PATHSEP)public$(PATHSEP)file$(PATHSEP)disxx.utility.file.MappedFile.cppm \
	..$(PATHSEP)modules$(PATHSEP)disasm$(PATHSEP)private$(PATHSEP)disxx.disasm.InstructionIdentifier.cppm \
	..$(PATHSEP)modules$(PATHSEP)disasm$(PATHSEP)public$(PATHSEP)operand$(PATHSEP)disxx.disasm.operand.IOperand.cppm \
	..$(PATHSEP)modules$(PATHSEP)disasm$(PATHSEP)public$(PATHSEP)operand$(PATHSEP)disxx.disasm.operand.Register-VectorArrangementSpecifier.cppm \
	..$(PATHSEP)modules$(PATHSEP)disasm$(PATHSEP)public$(PATHSEP)operand$(PATHSEP)disxx.disasm.operand.Register.cppm \
	..$(PATHSEP)modules$(PATHSEP)disasm$(PATHSEP)public$(PATHSEP)operand$(PATHSEP)disxx.disasm.operand.Immediate.cppm \
	..$(PATHSEP)modules$(PATHSEP)disasm$(PATHSEP)public$(PATHSEP)operand$(PATHSEP)disxx.disasm.operand.Extension.cppm \
	..$(PATHSEP)modules$(PATHSEP)disasm$(PATHSEP)public$(PATHSEP)operand$(PATHSEP)disxx.disasm.operand.PState.cppm \
	..$(PATHSEP)modules$(PATHSEP)disasm$(PATHSEP)public$(PATHSEP)operand$(PATHSEP)disxx.disasm.operand.Shift.cppm \
	..$(PATHSEP)modules$(PATHSEP)disasm$(PATHSEP)public$(PATHSEP)operand$(PATHSEP)disxx.disasm.operand.LoadsAndStoresAddress.cppm \
	..$(PATHSEP)modules$(PATHSEP)disasm$(PATHSEP)public$(PATHSEP)operand$(PATHSEP)disxx.disasm.operand.PrefetchOperand.cppm \
	..$(PATHSEP)modules$(PATHSEP)disasm$(PATHSEP)public$(PATHSEP)operand$(PATHSEP)disxx.disasm.operand.SystemOperand.cppm \
	..$(PATHSEP)modules$(PATHSEP)disasm$(PATHSEP)public$(PATHSEP)operand$(PATHSEP)disxx.disasm.operand.MemoryBarrier.cppm \
	..$(PATHSEP)modules$(PATHSEP)disasm$(PATHSEP)public$(PATHSEP)operand$(PATHSEP)disxx.disasm.operand.Condition.cppm \
	..$(PATHSEP)modules$(PATHSEP)disasm$(PATHSEP)public$(PATHSEP)disxx.disasm.Address.cppm \
	..$(PATHSEP)modules$(PATHSEP)disasm$(PATHSEP)public$(PATHSEP)disxx.disasm.Bytes.cppm \
	..$(PATHSEP)modules$(PATHSEP)disasm$(PATHSEP)public$(PATHSEP)disxx.disasm.Instruction.cppm \
	..$(PATHSEP)modules$(PATHSEP)disasm$(PATHSEP)public$(PATHSEP)disxx.disasm.Disassembler.cppm \
	..$(PATHSEP)modules$(PATHSEP)disasm$(PATHSEP)public$(PATHSEP)disxx.disasm.Printer.cppm \
	..$(PATHSEP)modules$(PATHSEP)ui$(PATHSEP)private$(PATHSEP)utility$(PATHSEP)disxx.ui.utility.Vec.cppm \
	..$(PATHSEP)modules$(PATHSEP)ui$(PATHSEP)private$(PATHSEP)utility$(PATHSEP)disxx.ui.utility.Vertex.cppm \
	..$(PATHSEP)modules$(PATHSEP)ui$(PATHSEP)private$(PATHSEP)utility$(PATHSEP)disxx.ui.utility.ColorTag.cppm \
	..$(PATHSEP)modules$(PATHSEP)ui$(PATHSEP)utility$(PATHSEP)disxx.ui.utility.Renderable.cppm \
	..$(PATHSEP)modules$(PATHSEP)ui$(PATHSEP)utility$(PATHSEP)disxx.ui.utility.Text.cppm \
	..$(PATHSEP)modules$(PATHSEP)ui$(PATHSEP)utility$(PATHSEP)disxx.ui.utility.Shape.cppm \
	..$(PATHSEP)modules$(PATHSEP)ui$(PATHSEP)private$(PATHSEP)backend$(PATHSEP)disxx.ui.backend.IRenderer.cppm \
	..$(PATHSEP)modules$(PATHSEP)ui$(PATHSEP)private$(PATHSEP)backend$(PATHSEP)disxx.ui.backend.GLRenderer.cppm \
	..$(PATHSEP)modules$(PATHSEP)ui$(PATHSEP)private$(PATHSEP)backend$(PATHSEP)disxx.ui.backend.IContext.cppm \
	..$(PATHSEP)modules$(PATHSEP)ui$(PATHSEP)private$(PATHSEP)backend$(PATHSEP)disxx.ui.backend.GLUTContext.cppm \
	..$(PATHSEP)modules$(PATHSEP)ui$(PATHSEP)public$(PATHSEP)disxx.ui.Widget.cppm \
	..$(PATHSEP)modules$(PATHSEP)ui$(PATHSEP)public$(PATHSEP)disxx.ui.Frame.cppm \
	..$(PATHSEP)modules$(PATHSEP)ui$(PATHSEP)public$(PATHSEP)disxx.ui.Button.cppm \
	..$(PATHSEP)modules$(PATHSEP)ui$(PATHSEP)public$(PATHSEP)disxx.ui.Label.cppm \
	..$(PATHSEP)modules$(PATHSEP)ui$(PATHSEP)private$(PATHSEP)disxx.ui.MenuEntry.cppm \
	..$(PATHSEP)modules$(PATHSEP)ui$(PATHSEP)public$(PATHSEP)disxx.ui.Menu.cppm \
	..$(PATHSEP)modules$(PATHSEP)ui$(PATHSEP)public$(PATHSEP)disxx.ui.SourceEditor.cppm \
	..$(PATHSEP)modules$(PATHSEP)ui$(PATHSEP)private$(PATHSEP)disxx.ui.Tab.cppm \
	..$(PATHSEP)modules$(PATHSEP)ui$(PATHSEP)public$(PATHSEP)disxx.ui.TabbedPane.cppm \
	..$(PATHSEP)modules$(PATHSEP)ui$(PATHSEP)public$(PATHSEP)disxx.ui.TextInput.cppm \
	..$(PATHSEP)modules$(PATHSEP)ui$(PATHSEP)public$(PATHSEP)disxx.ui.MainWindow.cppm \
	 ..$(PATHSEP)modules$(PATHSEP)ui$(PATHSEP)public$(PATHSEP)disxx.ui.MessageBox.cppm \
	..$(PATHSEP)modules$(PATHSEP)loader$(PATHSEP)private$(PATHSEP)utility$(PATHSEP)disxx.loader.utility.BinaryInfo.cppm \
	..$(PATHSEP)modules$(PATHSEP)loader$(PATHSEP)private$(PATHSEP)executable$(PATHSEP)disxx.loader.executable.Label.cppm \
	..$(PATHSEP)modules$(PATHSEP)loader$(PATHSEP)private$(PATHSEP)executable$(PATHSEP)disxx.loader.executable.Section.cppm \
	..$(PATHSEP)modules$(PATHSEP)loader$(PATHSEP)public$(PATHSEP)executable$(PATHSEP)disxx.loader.executable.ExecutableFile.cppm \
	..$(PATHSEP)modules$(PATHSEP)loader$(PATHSEP)public$(PATHSEP)disxx.loader.macho.Loader.cppm \
	.$(PATHSEP)ScriptEngine$(PATHSEP)ScriptEngine.cppm \
	.$(PATHSEP)Core$(PATHSEP)DisLog.cppm \
	.$(PATHSEP)FileInput$(PATHSEP)FileInput.cppm \
	.$(PATHSEP)Core$(PATHSEP)Application.cppm

SOURCES=\
	.$(PATHSEP)ScriptEngine$(PATHSEP)ScriptEngine.cpp \
	.$(PATHSEP)Core$(PATHSEP)DisLog.cpp \
	.$(PATHSEP)FileInput$(PATHSEP)FileInput.cpp \
	.$(PATHSEP)Core$(PATHSEP)Application.cpp \
	.$(PATHSEP)main.cpp

PRECOMPILED=$(addprefix $(PRECOMPILEDDIR)$(PATHSEP), $(notdir $(MODULES:.cppm=.pcm)))
MOBJECTS=$(PRECOMPILED:.pcm=.o)
OBJECTS=$(addprefix $(OBJECTSDIR)$(PATHSEP), $(notdir $(SOURCES:.cpp=.o)))

__DYLIBS=libdisxx-util.$(DYLIB) libdisxx-ui.$(DYLIB) libdisxx-macho.$(DYLIB) libdisxx-disasm.$(DYLIB)
DYLIBS=$(addprefix $(DEPENDENCIESDIR)$(PATHSEP), $(__DYLIBS))

.PHONY: all
all: $(BUILDDIR)$(PATHSEP)dis++

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
	$(CXX) $(CXXFLAGS:-c=--precompile) $< -o $@
$(MOBJECTS): $(PRECOMPILEDDIR)$(PATHSEP)%.o: $(PRECOMPILEDDIR)$(PATHSEP)%.pcm | $(PRECOMPILEDDIR)
	$(CXX) $(CXXFLAGS) $< -o $@
$(OBJECTS): $(OBJECTSDIR)$(PATHSEP)%.o: %.cpp | $(OBJECTSDIR)
	$(CXX) $(CXXFLAGS) $< -o $@
$(DEPENDENCIESDIR)$(PATHSEP)libdisxx-util.$(DYLIB): | $(DEPENDENCIESDIR)
	make -C ..$(PATHSEP)utility
	$(MOVE) ..$(PATHSEP)utility$(PATHSEP)build$(PATHSEP)$(notdir $@) $@
$(DEPENDENCIESDIR)$(PATHSEP)libdisxx-ui.$(DYLIB): | $(DEPENDENCIESDIR)
	make -C ..$(PATHSEP)ui
	$(MOVE) ..$(PATHSEP)ui$(PATHSEP)build$(PATHSEP)$(notdir $@) $@
$(DEPENDENCIESDIR)$(PATHSEP)libdisxx-macho.$(DYLIB): | $(DEPENDENCIESDIR)
	make -C ..$(PATHSEP)loader
	$(MOVE) ..$(PATHSEP)loader$(PATHSEP)build$(PATHSEP)$(notdir $@) $@
$(DEPENDENCIESDIR)$(PATHSEP)libdisxx-disasm.$(DYLIB): | $(DEPENDENCIESDIR)
	make -C ..$(PATHSEP)disasm
	$(MOVE) ..$(PATHSEP)disasm$(PATHSEP)build$(PATHSEP)$(notdir $@) $@
$(BUILDDIR)$(PATHSEP)dis++: $(MOBJECTS) $(OBJECTS) | $(DYLIBS)
	$(LD) $(LFLAGS) $^ -o $@

clean:
	$(RMDIR) $(BUILDDIR)
