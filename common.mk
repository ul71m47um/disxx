OS=$(shell echo %OS%)
ifeq ($(OS), Windows_NT)
	PATHSEP=\\
	ARCH=$(shell echo %PROCESSORARCHITECTURE%)
else
	OS=$(shell uname -s)
	PATHSEP=/
	ARCH=$(shell uname -m)
endif

CXXFLAGS=\
	-c -std=c++26 -stdlib=libc++ -Weverything -Werror -fno-implicit-modules -fno-implicit-module-maps \
	-ftrapv -fmodules -fcxx-modules -fvisibility=hidden -Xclang -fmodules-local-submodule-visibility \
	-fstack-protector-all -fstrict-aliasing -fcheck-new -fcolor-diagnostics -fdata-sections \
	-fsafe-buffer-usage-suggestions

LFLAGS=-lc++ -lc++abi -lc -lm -demangle

# Check if the OS is Windows, or else
# treat this system as UNIX
ifeq ($(OS), Windows_NT)
	# Script for assembling all the binaries together
	MKAPP=.$(PATHSEP)mkapp.bat

	# C++ standart library module
	LIBCXX=$(shell echo %VCToolsInstallDir%)$(PATHSEP)modules$(PATHSEP)std.ixx
	
	# File extensions
	DYLIB=dll

	# Build tools
	ASM=$(shell where clang 2>NUL)
	LD=$(shell where link 2>NUL)
	CC=$(shell where clang 2>NUL)
	CXX=$(shell where clang++ 2>NUL)
	RUBY=$(shell where ruby 2>NUL)

	# Check if they haven't just been found
	ifeq ($(ASM),)
		$(error Unable to find an assembler)
	endif
	ifeq ($(LD),)
		$(error Unable to find a linker)
	endif
	ifeq ($(CC),)
		$(error Unable to find a C compiler)
	endif
	ifeq ($(CXX),)
		$(error Unable to find a C++ compiler)
	endif
	ifeq ($(RUBY),)
		$(error Unable to find Ruby interpreter)
	endif

	# Base commands
	MKDIR=mkdir -p
	MOVE=move /Y
	RMDIR=rmdir /s /q
	RM=def /f
else
	# Script for assembling all the binaries together
	MKAPP=.$(PATHSEP)mkapp.sh

	ifeq ($(OS), Darwin)
		CXXFLAGS+=\
			-isysroot $(shell xcrun --show-sdk-path) -arch $(ARCH) \
			-fexperimental-bounds-safety-attributes -fchecked-pointer-arithmetic \
			-fbounds-safety-bringup-missing-checks

		LFLAGS+=\
			-syslibroot $(shell xcrun --show-sdk-path) -arch $(ARCH) \
			-lSystem

		# C++ standart library module
		LIBCXX=/usr/share/libc++/v1/std.cppm

		# File extensions
		DYLIB=dylib

		ASM=$(shell xcrun --find as 2>/dev/null)
		LD=$(shell xcrun --find ld 2>/dev/null)
		CC=$(shell xcrun --find clang 2>/dev/null)
		CXX=$(shell xcrun --find clang++ 2>/dev/null)
		RUBY=$(shell xcrun --find ruby 2>/dev/null)
	else
		CXXFLAGS+=-isysroot $(shell llvm-config --includedir)
		LFLAGS+=-L$(dir $(shell clang++ -print-file-name=libc++.so))

		# C++ standart library module
		LIBCXX=$(shell llvm-config --prefix)$(PATHSEP)share$(PATHSEP)libc++$(PATHSEP)v1$(PATHSEP)std.cppm

		# File extensions
		DYLIB=so

		ASM=$(shell command -v as)
		LD=$(shell command -v clang++) -fuse-ld=lld
		CC=$(shell command -v clang)
		CXX=$(shell command -v clang++)
		RUBY=$(shell command -v ruby)
	endif

	# Check if they haven't just been found
	ifeq ($(ASM),)
		$(error Unable to find an assembler)
	endif
	ifeq ($(LD),)
		$(error Unable to find a linker)
	endif
	ifeq ($(CC),)
		$(error Unable to find a C compiler)
	endif
	ifeq ($(CXX),)
		$(error Unable to find a C++ compiler)
	endif
	ifeq ($(RUBY),)
		$(error Unable to find Ruby interpreter)
	endif

	# Base commands (I infer they always should be in the current OS)
	MKDIR=mkdir -p
	MOVE=mv
	RMDIR=rm -rf
	RM=rm -f
endif

ECHO=echo
