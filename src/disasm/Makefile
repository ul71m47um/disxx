include ../../common.mk

BUILDDIR=./build
DEPENDENCIESDIR=$(BUILDDIR)/dependencies
PRECOMPILEDDIR=$(BUILDDIR)/precompiled
OBJECTSDIR=$(BUILDDIR)/objects

CXXFLAGS+=\
	-O3 -fPIC -fprebuilt-module-path=$(PRECOMPILEDDIR) -DNDEBUG \
	-Wno-weak-vtables -Wno-c++98-compat -Wno-padded -Wno-c++98-c++11-compat-binary-literal \
	-Wno-c++98-compat-pedantic -Wno-unused-command-line-argument -Wno-poison-system-directories \
	-Wno-reserved-module-identifier -Wno-reserved-identifier -Wno-exit-time-destructors

LFLAGS+=-O2 -L$(DEPENDENCIESDIR) -ldisxx-utility
ifeq ($(OS), Darwin)
	LFLAGS+=-dylib -S -install_name @executable_path/../Frameworks/libdisxx-disasm.$(DYLIB) -rpath .
else
	ifneq ($(OS), Windows_NT)
		LFLAGS+=-shared -rpath $$ORIGIN/libdisxx-disasm.$(DYLIB)
	endif
endif

MODULES=\
	$(LIBCXX) \
	../modules/utility/public/trait/disxx.utility.trait.Cloneable.cppm \
	../modules/utility/private/error/disxx.utility.error.DisassemblyError.cppm \
	../modules/utility/private/error/disxx.utility.error.NullPointerError.cppm \
	../modules/utility/private/pointer/disxx.utility.pointer.DefaultDeleter.cppm \
	../modules/utility/public/pointer/disxx.utility.pointer.NonNull.cppm \
	./utility/bits/disxx.disasm.utility.bits.cppm \
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
	./decoder/abstract/disxx.disasm.decoder.abstract.SubDecoder.cppm \
	./decoder/abstract/disxx.disasm.decoder.abstract.Decoder.cppm \
	./decoder/DataProcessingRegister/SubDecoder/disxx.disasm.decoder.DataProcessingRegister.EvaluateIntoFlags.SubDecoder.cppm \
	./decoder/DataProcessingRegister/SubDecoder/disxx.disasm.decoder.DataProcessingRegister.ConditionalCompareImmediate.SubDecoder.cppm \
	./decoder/DataProcessingRegister/SubDecoder/disxx.disasm.decoder.DataProcessingRegister.AddSubstractCheckedPointer.SubDecoder.cppm \
	./decoder/DataProcessingRegister/SubDecoder/disxx.disasm.decoder.DataProcessingRegister.ConditionalSelect.SubDecoder.cppm \
	./decoder/DataProcessingRegister/SubDecoder/disxx.disasm.decoder.DataProcessingRegister.DataProcessing1Source.SubDecoder.cppm \
	./decoder/DataProcessingRegister/SubDecoder/disxx.disasm.decoder.DataProcessingRegister.DataProcessing3Source.SubDecoder.cppm \
	./decoder/DataProcessingRegister/SubDecoder/disxx.disasm.decoder.DataProcessingRegister.ConditionalCompareRegister.SubDecoder.cppm \
	./decoder/DataProcessingRegister/SubDecoder/disxx.disasm.decoder.DataProcessingRegister.AddSubstractWithCarry.SubDecoder.cppm \
	./decoder/DataProcessingRegister/SubDecoder/disxx.disasm.decoder.DataProcessingRegister.RotateRightIntoFlags.SubDecoder.cppm \
	./decoder/DataProcessingRegister/SubDecoder/disxx.disasm.decoder.DataProcessingRegister.LogicalShiftedRegister.SubDecoder.cppm \
	./decoder/DataProcessingRegister/SubDecoder/disxx.disasm.decoder.DataProcessingRegister.AddSubstractShiftedRegister.SubDecoder.cppm \
	./decoder/DataProcessingRegister/SubDecoder/disxx.disasm.decoder.DataProcessingRegister.DataProcessing2Source.SubDecoder.cppm \
	./decoder/DataProcessingRegister/SubDecoder/disxx.disasm.decoder.DataProcessingRegister.AddSubstractExtendedRegister.SubDecoder.cppm \
	./decoder/DataProcessingRegister/disxx.disasm.decoder.DataProcessingRegister.Decoder.cppm \
	./decoder/DataProcessingImmediate/SubDecoder/disxx.disasm.decoder.DataProcessingImmediate.MinMaxImmediate.SubDecoder.cppm \
	./decoder/DataProcessingImmediate/SubDecoder/disxx.disasm.decoder.DataProcessingImmediate.Bitfield.SubDecoder.cppm \
	./decoder/DataProcessingImmediate/SubDecoder/disxx.disasm.decoder.DataProcessingImmediate.LogicalImmediate.SubDecoder.cppm \
	./decoder/DataProcessingImmediate/SubDecoder/disxx.disasm.decoder.DataProcessingImmediate.AddSubstractImmediate.SubDecoder.cppm \
	./decoder/DataProcessingImmediate/SubDecoder/disxx.disasm.decoder.DataProcessingImmediate.DataProcessing1SourceImmediate.SubDecoder.cppm \
	./decoder/DataProcessingImmediate/SubDecoder/disxx.disasm.decoder.DataProcessingImmediate.PCRelAddressing.SubDecoder.cppm \
	./decoder/DataProcessingImmediate/SubDecoder/disxx.disasm.decoder.DataProcessingImmediate.AddSubstractImmediateWithTags.SubDecoder.cppm \
	./decoder/DataProcessingImmediate/SubDecoder/disxx.disasm.decoder.DataProcessingImmediate.MoveWideImmediate.SubDecoder.cppm \
	./decoder/DataProcessingImmediate/SubDecoder/disxx.disasm.decoder.DataProcessingImmediate.Extract.SubDecoder.cppm \
	./decoder/DataProcessingImmediate/disxx.disasm.decoder.DataProcessingImmediate.Decoder.cppm \
	./decoder/Reserved/SubDecoder/disxx.disasm.decoder.Reserved.UDF.SubDecoder.cppm \
	./decoder/Reserved/disxx.disasm.decoder.Reserved.Decoder.cppm \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDModifiedImmediate.SubDecoder.cppm \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDScalarThreeSameExtra.SubDecoder.cppm \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDVectorXIndexedElement.SubDecoder.cppm \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.CryptographicThreeRegisterSHA512.SubDecoder.cppm \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDThreeSame.SubDecoder.cppm \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.ConversionBetweenFloatingPointAndFixedPoint.SubDecoder.cppm \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDScalarThreeDifferent.SubDecoder.cppm \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDCopy.SubDecoder.cppm \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.FloatingPointConditionalCompare.SubDecoder.cppm \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDScalarShiftByImmediate.SubDecoder.cppm \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.FloatingPointDataProcessing2Source.SubDecoder.cppm \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDThreeRegisterExtension.SubDecoder.cppm \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.FloatingPointImmediate.SubDecoder.cppm \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.XAR.SubDecoder.cppm \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDScalarThreeSameFP16.SubDecoder.cppm \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.CryptographicTwoRegisterSHA512.SubDecoder.cppm \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.CryptographicThreeRegisterSHA.SubDecoder.cppm \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDThreeSameFP16.SubDecoder.cppm \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDThreeDifferent.SubDecoder.cppm \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDAcrossLanes.SubDecoder.cppm \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDScalarCopy.SubDecoder.cppm \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDShiftByImmediate.SubDecoder.cppm \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDScalarPairwise.SubDecoder.cppm \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDScalarXIndexedElement.SubDecoder.cppm \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDScalarTwoRegisterMiscellaneousFP16.SubDecoder.cppm \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.CryptographicTwoRegisterSHA.SubDecoder.cppm \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.FloatingPointConditionalSelect.SubDecoder.cppm \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDPermute.SubDecoder.cppm \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDScalarThreeSame.SubDecoder.cppm \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDScalarTwoRegisterMiscellaneous.SubDecoder.cppm \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.ConversionBetweenFloatingPointAndInteger.SubDecoder.cppm \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDTwoRegisterMiscellaneous.SubDecoder.cppm \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDExtract.SubDecoder.cppm \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.CryptographicAES.SubDecoder.cppm \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDTableLookup.SubDecoder.cppm \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.FloatingPointDataProcessing3Source.SubDecoder.cppm \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDTwoRegisterMiscellaneousFP16.SubDecoder.cppm \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.CryptographicThreeRegisterImm2.SubDecoder.cppm \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.CryptographicFourRegister.SubDecoder.cppm \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.FloatingPointCompare.SubDecoder.cppm \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.FloatingPointDataProcessing1Source.SubDecoder.cppm \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.Decoder.cppm \
	./decoder/LoadsAndStores/disxx.disasm.decoder.LoadsAndStores.Decoder.cppm \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.ExclusiveRegister.SubDecoder.cppm \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.NoAllocatePairOffset.SubDecoder.cppm \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.OneHundredAndTwentyEightBitAtomicMemoryOperations.SubDecoder.cppm \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.GCS.SubDecoder.cppm \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.AtomicMemoryOperations.SubDecoder.cppm \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.SIMDSingleStructurePostIndexed.SubDecoder.cppm \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.RegisterPairPostIndexed.SubDecoder.cppm \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.RegisterPAC.SubDecoder.cppm \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.CompareAndSwapPairUnprivileged.SubDecoder.cppm \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.LDAPRSTLRSIMDAndFP.SubDecoder.cppm \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.CompareAndSwapUnprivileged.SubDecoder.cppm \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.RegisterUnscaledImmediate.SubDecoder.cppm \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.RegisterPairPreIndexed.SubDecoder.cppm \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.SIMDMultipleStructures.SubDecoder.cppm \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.LDAPRSTLRWriteback.SubDecoder.cppm \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.RegisterUnprivileged.SubDecoder.cppm \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.CompareAndSwapPair.SubDecoder.cppm \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.AtomicMemoryOperationsUnprivileged.SubDecoder.cppm \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.ExclusiveRegisterUnprivileged.SubDecoder.cppm \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.MemoryCopyAndMemorySet.SubDecoder.cppm \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.Ordered.SubDecoder.cppm \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.RegisterImmediatePreIndexed.SubDecoder.cppm \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.RegisterPairOffset.SubDecoder.cppm \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.RegisterLiteral.SubDecoder.cppm \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.LDAPRSTLRUnscaledImmediate.SubDecoder.cppm \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.LDIAPPSTILP.SubDecoder.cppm \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.SIMDSingleStructure.SubDecoder.cppm \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.RegisterUnsignedImmediate.SubDecoder.cppm \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.SIMDMultipleStructuresPostIndexed.SubDecoder.cppm \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.RCWCompareAndSwapPair.SubDecoder.cppm \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.CompareAndSwap.SubDecoder.cppm \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.RCWCompareAndSwap.SubDecoder.cppm \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.MemoryTags.SubDecoder.cppm \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.RegisterImmediatePostIndexed.SubDecoder.cppm \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.ExclusivePair.SubDecoder.cppm \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.RegisterOffset.SubDecoder.cppm \
	./decoder/BranchesExceptionsAndSystemInstructions/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.Decoder.cppm \
	./decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.SystemInstructionIDsWithRegisterArgument.SubDecoder.cppm \
	./decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.SystemRegisterPairMove.SubDecoder.cppm \
	./decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.ExceptionGeneration.SubDecoder.cppm \
	./decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.UnconditionalBranchRegister.SubDecoder.cppm \
	./decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.CompareAndBranchImmediate.SubDecoder.cppm \
	./decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.CompareBytesHalfwordsInRegisterAndBranch.SubDecoder.cppm \
	./decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.CompareRegisterWithImmediateAndBranch.SubDecoder.cppm \
	./decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.Hints.SubDecoder.cppm \
	./decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.TestAndBranchImmediate.SubDecoder.cppm \
	./decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.CompareRegistersAndBranch.SubDecoder.cppm \
	./decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.SystemPairInstructionIDs.SubDecoder.cppm \
	./decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.MiscellaneousBranchImmediate.SubDecoder.cppm \
	./decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.Barriers.SubDecoder.cppm \
	./decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.SystemInstructionIDs.SubDecoder.cppm \
	./decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.UnconditionalBranchImmediate.SubDecoder.cppm \
	./decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.PSTATE.SubDecoder.cppm \
	./decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.SystemWithResult.SubDecoder.cppm \
	./decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.ConditionalBranchImmediate.SubDecoder.cppm \
	./decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.SystemRegisterMove.SubDecoder.cppm \
	./decoder/DecoderFactory/disxx.disasm.decoder.DecoderFactory.cppm \
    ./decoder/DecoderFactory/disxx.disasm.decoder.DecoderFactory-PseudoDecoder.cppm \
	../modules/disasm/private/disxx.disasm.Address.cppm \
	../modules/disasm/private/disxx.disasm.Bytes.cppm \
	../modules/disasm/private/disxx.disasm.Instruction.cppm \
	../modules/disasm/public/disxx.disasm.Disassembler.cppm \
	../modules/disasm/public/disxx.disasm.Printer.cppm

SOURCES=\
	./utility/bits/disxx.disasm.utility.bits.cpp \
	./operand/disxx.disasm.operand.Register.cpp \
	./operand/disxx.disasm.operand.Extension.cpp \
	./operand/disxx.disasm.operand.PState.cpp \
	./operand/disxx.disasm.operand.LoadsAndStoresAddress.cpp \
	./operand/disxx.disasm.operand.PrefetchOperand.cpp \
	./operand/disxx.disasm.operand.SystemOperand.cpp \
	./operand/disxx.disasm.operand.MemoryBarrier.cpp \
	./operand/disxx.disasm.operand.Shift.cpp \
	./operand/disxx.disasm.operand.Condition.cpp \
	./decoder/abstract/disxx.disasm.decoder.abstract.SubDecoder.cpp \
	./decoder/abstract/disxx.disasm.decoder.abstract.Decoder.cpp \
	./decoder/DataProcessingRegister/SubDecoder/disxx.disasm.decoder.DataProcessingRegister.AddSubstractShiftedRegister.SubDecoder.cpp \
	./decoder/DataProcessingRegister/SubDecoder/disxx.disasm.decoder.DataProcessingRegister.LogicalShiftedRegister.SubDecoder.cpp \
	./decoder/DataProcessingRegister/SubDecoder/disxx.disasm.decoder.DataProcessingRegister.DataProcessing2Source.SubDecoder.cpp \
	./decoder/DataProcessingRegister/SubDecoder/disxx.disasm.decoder.DataProcessingRegister.DataProcessing3Source.SubDecoder.cpp \
	./decoder/DataProcessingRegister/SubDecoder/disxx.disasm.decoder.DataProcessingRegister.AddSubstractWithCarry.SubDecoder.cpp \
	./decoder/DataProcessingRegister/SubDecoder/disxx.disasm.decoder.DataProcessingRegister.AddSubstractExtendedRegister.SubDecoder.cpp \
	./decoder/DataProcessingRegister/SubDecoder/disxx.disasm.decoder.DataProcessingRegister.ConditionalCompareImmediate.SubDecoder.cpp \
	./decoder/DataProcessingRegister/SubDecoder/disxx.disasm.decoder.DataProcessingRegister.EvaluateIntoFlags.SubDecoder.cpp \
	./decoder/DataProcessingRegister/SubDecoder/disxx.disasm.decoder.DataProcessingRegister.RotateRightIntoFlags.SubDecoder.cpp \
	./decoder/DataProcessingRegister/SubDecoder/disxx.disasm.decoder.DataProcessingRegister.ConditionalSelect.SubDecoder.cpp \
	./decoder/DataProcessingRegister/SubDecoder/disxx.disasm.decoder.DataProcessingRegister.DataProcessing1Source.SubDecoder.cpp \
	./decoder/DataProcessingRegister/SubDecoder/disxx.disasm.decoder.DataProcessingRegister.ConditionalCompareRegister.SubDecoder.cpp \
	./decoder/DataProcessingRegister/SubDecoder/disxx.disasm.decoder.DataProcessingRegister.AddSubstractCheckedPointer.SubDecoder.cpp \
	./decoder/DataProcessingRegister/disxx.disasm.decoder.DataProcessingRegister.Decoder.cpp \
	./decoder/DataProcessingImmediate/SubDecoder/disxx.disasm.decoder.DataProcessingImmediate.MoveWideImmediate.SubDecoder.cpp \
	./decoder/DataProcessingImmediate/SubDecoder/disxx.disasm.decoder.DataProcessingImmediate.Bitfield.SubDecoder.cpp \
	./decoder/DataProcessingImmediate/SubDecoder/disxx.disasm.decoder.DataProcessingImmediate.Extract.SubDecoder.cpp \
	./decoder/DataProcessingImmediate/SubDecoder/disxx.disasm.decoder.DataProcessingImmediate.DataProcessing1SourceImmediate.SubDecoder.cpp \
	./decoder/DataProcessingImmediate/SubDecoder/disxx.disasm.decoder.DataProcessingImmediate.MinMaxImmediate.SubDecoder.cpp \
	./decoder/DataProcessingImmediate/SubDecoder/disxx.disasm.decoder.DataProcessingImmediate.AddSubstractImmediateWithTags.SubDecoder.cpp \
	./decoder/DataProcessingImmediate/SubDecoder/disxx.disasm.decoder.DataProcessingImmediate.PCRelAddressing.SubDecoder.cpp \
	./decoder/DataProcessingImmediate/SubDecoder/disxx.disasm.decoder.DataProcessingImmediate.AddSubstractImmediate.SubDecoder.cpp \
	./decoder/DataProcessingImmediate/SubDecoder/disxx.disasm.decoder.DataProcessingImmediate.LogicalImmediate.SubDecoder.cpp \
	./decoder/DataProcessingImmediate/disxx.disasm.decoder.DataProcessingImmediate.Decoder.cpp \
	./decoder/Reserved/SubDecoder/disxx.disasm.decoder.Reserved.UDF.SubDecoder.cpp \
	./decoder/Reserved/disxx.disasm.decoder.Reserved.Decoder.cpp \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.FloatingPointCompare.SubDecoder.cpp \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.FloatingPointDataProcessing3Source.SubDecoder.cpp \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDThreeSameFP16.SubDecoder.cpp \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.ConversionBetweenFloatingPointAndFixedPoint.SubDecoder.cpp \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDScalarThreeSameExtra.SubDecoder.cpp \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDScalarTwoRegisterMiscellaneousFP16.SubDecoder.cpp \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.FloatingPointConditionalSelect.SubDecoder.cpp \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDTableLookup.SubDecoder.cpp \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDAcrossLanes.SubDecoder.cpp \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDScalarPairwise.SubDecoder.cpp \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.FloatingPointDataProcessing2Source.SubDecoder.cpp \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDTwoRegisterMiscellaneous.SubDecoder.cpp \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.CryptographicAES.SubDecoder.cpp \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDThreeSame.SubDecoder.cpp \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDModifiedImmediate.SubDecoder.cpp \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.CryptographicTwoRegisterSHA.SubDecoder.cpp \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.CryptographicTwoRegisterSHA512.SubDecoder.cpp \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDScalarThreeDifferent.SubDecoder.cpp \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDExtract.SubDecoder.cpp \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDPermute.SubDecoder.cpp \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDThreeDifferent.SubDecoder.cpp \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDScalarTwoRegisterMiscellaneous.SubDecoder.cpp \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDScalarXIndexedElement.SubDecoder.cpp \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDScalarCopy.SubDecoder.cpp \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.CryptographicThreeRegisterSHA.SubDecoder.cpp \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.CryptographicThreeRegisterImm2.SubDecoder.cpp \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDVectorXIndexedElement.SubDecoder.cpp \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.CryptographicFourRegister.SubDecoder.cpp \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDScalarThreeSameFP16.SubDecoder.cpp \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDTwoRegisterMiscellaneousFP16.SubDecoder.cpp \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.FloatingPointConditionalCompare.SubDecoder.cpp \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDScalarThreeSame.SubDecoder.cpp \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.ConversionBetweenFloatingPointAndInteger.SubDecoder.cpp \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.FloatingPointImmediate.SubDecoder.cpp \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.XAR.SubDecoder.cpp \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.FloatingPointDataProcessing1Source.SubDecoder.cpp \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDShiftByImmediate.SubDecoder.cpp \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDThreeRegisterExtension.SubDecoder.cpp \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDScalarShiftByImmediate.SubDecoder.cpp \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDCopy.SubDecoder.cpp \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.CryptographicThreeRegisterSHA512.SubDecoder.cpp \
	./decoder/DataProcessingScalarFPAndAdvancedSIMD/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.Decoder.cpp \
	./decoder/DecoderFactory/disxx.disasm.decoder.DecoderFactory.cpp \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.LDAPRSTLRWriteback.SubDecoder.cpp \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.MemoryCopyAndMemorySet.SubDecoder.cpp \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.CompareAndSwapUnprivileged.SubDecoder.cpp \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.CompareAndSwapPairUnprivileged.SubDecoder.cpp \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.CompareAndSwap.SubDecoder.cpp \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.OneHundredAndTwentyEightBitAtomicMemoryOperations.SubDecoder.cpp \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.GCS.SubDecoder.cpp \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.AtomicMemoryOperationsUnprivileged.SubDecoder.cpp \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.RegisterImmediatePostIndexed.SubDecoder.cpp \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.LDIAPPSTILP.SubDecoder.cpp \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.RegisterPairPreIndexed.SubDecoder.cpp \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.RegisterImmediatePreIndexed.SubDecoder.cpp \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.NoAllocatePairOffset.SubDecoder.cpp \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.SIMDSingleStructurePostIndexed.SubDecoder.cpp \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.SIMDSingleStructure.SubDecoder.cpp \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.LDAPRSTLRSIMDAndFP.SubDecoder.cpp \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.SIMDMultipleStructures.SubDecoder.cpp \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.RCWCompareAndSwapPair.SubDecoder.cpp \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.RegisterPairOffset.SubDecoder.cpp \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.RegisterPairPostIndexed.SubDecoder.cpp \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.AtomicMemoryOperations.SubDecoder.cpp \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.Ordered.SubDecoder.cpp \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.CompareAndSwapPair.SubDecoder.cpp \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.RegisterLiteral.SubDecoder.cpp \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.SIMDMultipleStructuresPostIndexed.SubDecoder.cpp \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.RCWCompareAndSwap.SubDecoder.cpp \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.ExclusiveRegisterUnprivileged.SubDecoder.cpp \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.RegisterUnprivileged.SubDecoder.cpp \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.RegisterPAC.SubDecoder.cpp \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.RegisterUnsignedImmediate.SubDecoder.cpp \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.LDAPRSTLRUnscaledImmediate.SubDecoder.cpp \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.ExclusivePair.SubDecoder.cpp \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.ExclusiveRegister.SubDecoder.cpp \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.MemoryTags.SubDecoder.cpp \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.RegisterOffset.SubDecoder.cpp \
	./decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.RegisterUnscaledImmediate.SubDecoder.cpp \
	./decoder/LoadsAndStores/disxx.disasm.decoder.LoadsAndStores.Decoder.cpp \
	./decoder/BranchesExceptionsAndSystemInstructions/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.Decoder.cpp \
	./decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.TestAndBranchImmediate.SubDecoder.cpp \
	./decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.UnconditionalBranchRegister.SubDecoder.cpp \
	./decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.Barriers.SubDecoder.cpp \
	./decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.SystemRegisterMove.SubDecoder.cpp \
	./decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.UnconditionalBranchImmediate.SubDecoder.cpp \
	./decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.ConditionalBranchImmediate.SubDecoder.cpp \
	./decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.CompareRegisterWithImmediateAndBranch.SubDecoder.cpp \
	./decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.SystemRegisterPairMove.SubDecoder.cpp \
	./decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.SystemInstructionIDs.SubDecoder.cpp \
	./decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.CompareAndBranchImmediate.SubDecoder.cpp \
	./decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.SystemWithResult.SubDecoder.cpp \
	./decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.SystemPairInstructionIDs.SubDecoder.cpp \
	./decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.SystemInstructionIDsWithRegisterArgument.SubDecoder.cpp \
	./decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.CompareBytesHalfwordsInRegisterAndBranch.SubDecoder.cpp \
	./decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.Hints.SubDecoder.cpp \
	./decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.PSTATE.SubDecoder.cpp \
	./decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.CompareRegistersAndBranch.SubDecoder.cpp \
	./decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.MiscellaneousBranchImmediate.SubDecoder.cpp \
	./decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.ExceptionGeneration.SubDecoder.cpp \
	./disxx.disasm.Address.cpp \
	./disxx.disasm.Instruction.cpp \
	./disxx.disasm.Disassembler.cpp

.PHONY: all clean
all: $(BUILDDIR)/libdisxx-disasm.$(DYLIB)

UTILITIES=$(DEPENDENCIESDIR)/libdisxx-utility.$(DYLIB)

PRECOMPILED=$(addprefix $(PRECOMPILEDDIR)/, $(notdir $(MODULES:.cppm=.pcm)))
MOBJECTS=$(PRECOMPILED:.pcm=.o)
OBJECTS=$(addprefix $(OBJECTSDIR)/, $(notdir $(SOURCES:.cpp=.o)))

vpath %.cppm $(sort $(dir $(MODULES)))
vpath %.cpp $(sort $(dir $(SOURCES)))
vpath %.pcm $(sort $(dir $(PRECOMPILED)))

$(DEPENDENCIESDIR):
	$(MKDIR) $@
$(PRECOMPILEDDIR):
	$(MKDIR) $@
$(OBJECTSDIR):
	$(MKDIR) $@
$(UTILITIES): | $(DEPENDENCIESDIR)
	make -C ../utility/
	$(MOVE) ../utility/build/$(notdir $@) $@
$(PRECOMPILED): $(PRECOMPILEDDIR)/%.pcm: %.cppm | $(PRECOMPILEDDIR)
	$(CXX) $(CXXFLAGS:-c=--precompile) $< -o $@
$(MOBJECTS): $(PRECOMPILEDDIR)/%.o: $(PRECOMPILEDDIR)/%.pcm | $(PRECOMPILEDDDIR)
	$(CXX) $(CXXFLAGS) $< -o $@
$(OBJECTS): $(OBJECTSDIR)/%.o: %.cpp | $(OBJECTSDIR)
	$(CXX) $(CXXFLAGS) $< -o $@
$(BUILDDIR)/libdisxx-disasm.$(DYLIB): $(MOBJECTS) $(OBJECTS) | $(UTILITIES)
	$(LD) $(LFLAGS) $^ -o $@

clean:
	$(RMDIR) $(BUILDDIR)
