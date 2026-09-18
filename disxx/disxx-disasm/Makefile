include ../common.mk

BUILDDIR=../../build/disxx-disasm
DEPENDENCIESDIR=$(BUILDDIR)/dependencies
PRECOMPILEDDIR=$(BUILDDIR)/precompiled
OBJECTSDIR=$(BUILDDIR)/objects

CXXFLAGS+=\
	-fPIC -fprebuilt-module-path=$(PRECOMPILEDDIR) \
	-Wno-weak-vtables -Wno-c++98-compat -Wno-padded -Wno-c++98-c++11-compat-binary-literal \
	-Wno-c++98-compat-pedantic -Wno-unused-command-line-argument -Wno-poison-system-directories \
	-Wno-reserved-module-identifier -Wno-reserved-identifier -Wno-exit-time-destructors

LFLAGS+=-O2 -L$(DEPENDENCIESDIR) -ldisxx-utility
ifeq ($(OS), Darwin)
	LFLAGS+=-dylib -S -install_name @executable_path/../Frameworks/libdisxx-disasm.$(DYLIB)
else
	ifneq ($(OS), Windows_NT)
		LFLAGS+=-shared -rpath $$ORIGIN/libdisxx-disasm.$(DYLIB)
	endif
endif

MODULES=\
	$(LIBCXX) \
	../disxx-utility/modules/public/trait/disxx.utility.trait.IClone.cppm \
	../disxx-utility/modules/private/error/disxx.utility.error.DisassemblyError.cppm \
	../disxx-utility/modules/private/error/disxx.utility.error.NullPointerError.cppm \
	../disxx-utility/modules/private/pointer/disxx.utility.pointer.DefaultDeleter.cppm \
	../disxx-utility/modules/public/pointer/disxx.utility.pointer.NonNull.cppm \
	./src/utility/bits/disxx.disasm.utility.bits.cppm \
	./modules/private/disxx.disasm.InstructionIdentifier.cppm \
	./modules/private/operand/disxx.disasm.operand.IOperand.cppm \
	./modules/private/operand/disxx.disasm.operand.Register-VectorArrangementSpecifier.cppm \
	./modules/private/operand/disxx.disasm.operand.Register.cppm \
	./modules/private/operand/disxx.disasm.operand.Immediate.cppm \
	./modules/private/operand/disxx.disasm.operand.Extension.cppm \
	./modules/private/operand/disxx.disasm.operand.PState.cppm \
	./modules/private/operand/disxx.disasm.operand.Shift.cppm \
	./modules/private/operand/disxx.disasm.operand.LoadsAndStoresAddress.cppm \
	./modules/private/operand/disxx.disasm.operand.PrefetchOperand.cppm \
	./modules/private/operand/disxx.disasm.operand.SystemOperand.cppm \
	./modules/private/operand/disxx.disasm.operand.MemoryBarrier.cppm \
	./modules/private/operand/disxx.disasm.operand.Condition.cppm \
	./src/decoder/abstract/disxx.disasm.decoder.abstract.SubDecoder.cppm \
	./src/decoder/abstract/disxx.disasm.decoder.abstract.Decoder.cppm \
	./src/decoder/DataProcessingRegister/SubDecoder/disxx.disasm.decoder.DataProcessingRegister.EvaluateIntoFlags.SubDecoder.cppm \
	./src/decoder/DataProcessingRegister/SubDecoder/disxx.disasm.decoder.DataProcessingRegister.ConditionalCompareImmediate.SubDecoder.cppm \
	./src/decoder/DataProcessingRegister/SubDecoder/disxx.disasm.decoder.DataProcessingRegister.AddSubstractCheckedPointer.SubDecoder.cppm \
	./src/decoder/DataProcessingRegister/SubDecoder/disxx.disasm.decoder.DataProcessingRegister.ConditionalSelect.SubDecoder.cppm \
	./src/decoder/DataProcessingRegister/SubDecoder/disxx.disasm.decoder.DataProcessingRegister.DataProcessing1Source.SubDecoder.cppm \
	./src/decoder/DataProcessingRegister/SubDecoder/disxx.disasm.decoder.DataProcessingRegister.DataProcessing3Source.SubDecoder.cppm \
	./src/decoder/DataProcessingRegister/SubDecoder/disxx.disasm.decoder.DataProcessingRegister.ConditionalCompareRegister.SubDecoder.cppm \
	./src/decoder/DataProcessingRegister/SubDecoder/disxx.disasm.decoder.DataProcessingRegister.AddSubstractWithCarry.SubDecoder.cppm \
	./src/decoder/DataProcessingRegister/SubDecoder/disxx.disasm.decoder.DataProcessingRegister.RotateRightIntoFlags.SubDecoder.cppm \
	./src/decoder/DataProcessingRegister/SubDecoder/disxx.disasm.decoder.DataProcessingRegister.LogicalShiftedRegister.SubDecoder.cppm \
	./src/decoder/DataProcessingRegister/SubDecoder/disxx.disasm.decoder.DataProcessingRegister.AddSubstractShiftedRegister.SubDecoder.cppm \
	./src/decoder/DataProcessingRegister/SubDecoder/disxx.disasm.decoder.DataProcessingRegister.DataProcessing2Source.SubDecoder.cppm \
	./src/decoder/DataProcessingRegister/SubDecoder/disxx.disasm.decoder.DataProcessingRegister.AddSubstractExtendedRegister.SubDecoder.cppm \
	./src/decoder/DataProcessingRegister/disxx.disasm.decoder.DataProcessingRegister.Decoder.cppm \
	./src/decoder/DataProcessingImmediate/SubDecoder/disxx.disasm.decoder.DataProcessingImmediate.MinMaxImmediate.SubDecoder.cppm \
	./src/decoder/DataProcessingImmediate/SubDecoder/disxx.disasm.decoder.DataProcessingImmediate.Bitfield.SubDecoder.cppm \
	./src/decoder/DataProcessingImmediate/SubDecoder/disxx.disasm.decoder.DataProcessingImmediate.LogicalImmediate.SubDecoder.cppm \
	./src/decoder/DataProcessingImmediate/SubDecoder/disxx.disasm.decoder.DataProcessingImmediate.AddSubstractImmediate.SubDecoder.cppm \
	./src/decoder/DataProcessingImmediate/SubDecoder/disxx.disasm.decoder.DataProcessingImmediate.DataProcessing1SourceImmediate.SubDecoder.cppm \
	./src/decoder/DataProcessingImmediate/SubDecoder/disxx.disasm.decoder.DataProcessingImmediate.PCRelAddressing.SubDecoder.cppm \
	./src/decoder/DataProcessingImmediate/SubDecoder/disxx.disasm.decoder.DataProcessingImmediate.AddSubstractImmediateWithTags.SubDecoder.cppm \
	./src/decoder/DataProcessingImmediate/SubDecoder/disxx.disasm.decoder.DataProcessingImmediate.MoveWideImmediate.SubDecoder.cppm \
	./src/decoder/DataProcessingImmediate/SubDecoder/disxx.disasm.decoder.DataProcessingImmediate.Extract.SubDecoder.cppm \
	./src/decoder/DataProcessingImmediate/disxx.disasm.decoder.DataProcessingImmediate.Decoder.cppm \
	./src/decoder/Reserved/SubDecoder/disxx.disasm.decoder.Reserved.UDF.SubDecoder.cppm \
	./src/decoder/Reserved/disxx.disasm.decoder.Reserved.Decoder.cppm \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDModifiedImmediate.SubDecoder.cppm \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDScalarThreeSameExtra.SubDecoder.cppm \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDVectorXIndexedElement.SubDecoder.cppm \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.CryptographicThreeRegisterSHA512.SubDecoder.cppm \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDThreeSame.SubDecoder.cppm \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.ConversionBetweenFloatingPointAndFixedPoint.SubDecoder.cppm \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDScalarThreeDifferent.SubDecoder.cppm \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDCopy.SubDecoder.cppm \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.FloatingPointConditionalCompare.SubDecoder.cppm \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDScalarShiftByImmediate.SubDecoder.cppm \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.FloatingPointDataProcessing2Source.SubDecoder.cppm \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDThreeRegisterExtension.SubDecoder.cppm \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.FloatingPointImmediate.SubDecoder.cppm \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.XAR.SubDecoder.cppm \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDScalarThreeSameFP16.SubDecoder.cppm \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.CryptographicTwoRegisterSHA512.SubDecoder.cppm \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.CryptographicThreeRegisterSHA.SubDecoder.cppm \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDThreeSameFP16.SubDecoder.cppm \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDThreeDifferent.SubDecoder.cppm \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDAcrossLanes.SubDecoder.cppm \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDScalarCopy.SubDecoder.cppm \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDShiftByImmediate.SubDecoder.cppm \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDScalarPairwise.SubDecoder.cppm \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDScalarXIndexedElement.SubDecoder.cppm \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDScalarTwoRegisterMiscellaneousFP16.SubDecoder.cppm \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.CryptographicTwoRegisterSHA.SubDecoder.cppm \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.FloatingPointConditionalSelect.SubDecoder.cppm \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDPermute.SubDecoder.cppm \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDScalarThreeSame.SubDecoder.cppm \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDScalarTwoRegisterMiscellaneous.SubDecoder.cppm \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.ConversionBetweenFloatingPointAndInteger.SubDecoder.cppm \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDTwoRegisterMiscellaneous.SubDecoder.cppm \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDExtract.SubDecoder.cppm \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.CryptographicAES.SubDecoder.cppm \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDTableLookup.SubDecoder.cppm \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.FloatingPointDataProcessing3Source.SubDecoder.cppm \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDTwoRegisterMiscellaneousFP16.SubDecoder.cppm \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.CryptographicThreeRegisterImm2.SubDecoder.cppm \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.CryptographicFourRegister.SubDecoder.cppm \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.FloatingPointCompare.SubDecoder.cppm \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.FloatingPointDataProcessing1Source.SubDecoder.cppm \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.Decoder.cppm \
	./src/decoder/LoadsAndStores/disxx.disasm.decoder.LoadsAndStores.Decoder.cppm \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.ExclusiveRegister.SubDecoder.cppm \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.NoAllocatePairOffset.SubDecoder.cppm \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.OneHundredAndTwentyEightBitAtomicMemoryOperations.SubDecoder.cppm \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.GCS.SubDecoder.cppm \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.AtomicMemoryOperations.SubDecoder.cppm \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.SIMDSingleStructurePostIndexed.SubDecoder.cppm \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.RegisterPairPostIndexed.SubDecoder.cppm \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.RegisterPAC.SubDecoder.cppm \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.CompareAndSwapPairUnprivileged.SubDecoder.cppm \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.LDAPRSTLRSIMDAndFP.SubDecoder.cppm \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.CompareAndSwapUnprivileged.SubDecoder.cppm \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.RegisterUnscaledImmediate.SubDecoder.cppm \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.RegisterPairPreIndexed.SubDecoder.cppm \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.SIMDMultipleStructures.SubDecoder.cppm \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.LDAPRSTLRWriteback.SubDecoder.cppm \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.RegisterUnprivileged.SubDecoder.cppm \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.CompareAndSwapPair.SubDecoder.cppm \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.AtomicMemoryOperationsUnprivileged.SubDecoder.cppm \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.ExclusiveRegisterUnprivileged.SubDecoder.cppm \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.MemoryCopyAndMemorySet.SubDecoder.cppm \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.Ordered.SubDecoder.cppm \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.RegisterImmediatePreIndexed.SubDecoder.cppm \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.RegisterPairOffset.SubDecoder.cppm \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.RegisterLiteral.SubDecoder.cppm \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.LDAPRSTLRUnscaledImmediate.SubDecoder.cppm \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.LDIAPPSTILP.SubDecoder.cppm \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.SIMDSingleStructure.SubDecoder.cppm \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.RegisterUnsignedImmediate.SubDecoder.cppm \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.SIMDMultipleStructuresPostIndexed.SubDecoder.cppm \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.RCWCompareAndSwapPair.SubDecoder.cppm \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.CompareAndSwap.SubDecoder.cppm \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.RCWCompareAndSwap.SubDecoder.cppm \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.MemoryTags.SubDecoder.cppm \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.RegisterImmediatePostIndexed.SubDecoder.cppm \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.ExclusivePair.SubDecoder.cppm \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.RegisterOffset.SubDecoder.cppm \
	./src/decoder/BranchesExceptionsAndSystemInstructions/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.Decoder.cppm \
	./src/decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.SystemInstructionIDsWithRegisterArgument.SubDecoder.cppm \
	./src/decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.SystemRegisterPairMove.SubDecoder.cppm \
	./src/decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.ExceptionGeneration.SubDecoder.cppm \
	./src/decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.UnconditionalBranchRegister.SubDecoder.cppm \
	./src/decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.CompareAndBranchImmediate.SubDecoder.cppm \
	./src/decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.CompareBytesHalfwordsInRegisterAndBranch.SubDecoder.cppm \
	./src/decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.CompareRegisterWithImmediateAndBranch.SubDecoder.cppm \
	./src/decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.Hints.SubDecoder.cppm \
	./src/decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.TestAndBranchImmediate.SubDecoder.cppm \
	./src/decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.CompareRegistersAndBranch.SubDecoder.cppm \
	./src/decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.SystemPairInstructionIDs.SubDecoder.cppm \
	./src/decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.MiscellaneousBranchImmediate.SubDecoder.cppm \
	./src/decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.Barriers.SubDecoder.cppm \
	./src/decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.SystemInstructionIDs.SubDecoder.cppm \
	./src/decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.UnconditionalBranchImmediate.SubDecoder.cppm \
	./src/decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.PSTATE.SubDecoder.cppm \
	./src/decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.SystemWithResult.SubDecoder.cppm \
	./src/decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.ConditionalBranchImmediate.SubDecoder.cppm \
	./src/decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.SystemRegisterMove.SubDecoder.cppm \
	./src/decoder/DecoderFactory/disxx.disasm.decoder.DecoderFactory.cppm \
    ./src/decoder/DecoderFactory/disxx.disasm.decoder.DecoderFactory-PseudoDecoder.cppm \
	./modules/private/disxx.disasm.Address.cppm \
	./modules/private/disxx.disasm.Bytes.cppm \
	./modules/private/disxx.disasm.Instruction.cppm \
	./modules/public/disxx.disasm.Disassembler.cppm \
	./modules/public/disxx.disasm.Printer.cppm

SOURCES=\
	./src/utility/bits/disxx.disasm.utility.bits.cpp \
	./src/operand/disxx.disasm.operand.Register.cpp \
	./src/operand/disxx.disasm.operand.Extension.cpp \
	./src/operand/disxx.disasm.operand.PState.cpp \
	./src/operand/disxx.disasm.operand.LoadsAndStoresAddress.cpp \
	./src/operand/disxx.disasm.operand.PrefetchOperand.cpp \
	./src/operand/disxx.disasm.operand.SystemOperand.cpp \
	./src/operand/disxx.disasm.operand.MemoryBarrier.cpp \
	./src/operand/disxx.disasm.operand.Shift.cpp \
	./src/operand/disxx.disasm.operand.Condition.cpp \
	./src/decoder/abstract/disxx.disasm.decoder.abstract.SubDecoder.cpp \
	./src/decoder/abstract/disxx.disasm.decoder.abstract.Decoder.cpp \
	./src/decoder/DataProcessingRegister/SubDecoder/disxx.disasm.decoder.DataProcessingRegister.AddSubstractShiftedRegister.SubDecoder.cpp \
	./src/decoder/DataProcessingRegister/SubDecoder/disxx.disasm.decoder.DataProcessingRegister.LogicalShiftedRegister.SubDecoder.cpp \
	./src/decoder/DataProcessingRegister/SubDecoder/disxx.disasm.decoder.DataProcessingRegister.DataProcessing2Source.SubDecoder.cpp \
	./src/decoder/DataProcessingRegister/SubDecoder/disxx.disasm.decoder.DataProcessingRegister.DataProcessing3Source.SubDecoder.cpp \
	./src/decoder/DataProcessingRegister/SubDecoder/disxx.disasm.decoder.DataProcessingRegister.AddSubstractWithCarry.SubDecoder.cpp \
	./src/decoder/DataProcessingRegister/SubDecoder/disxx.disasm.decoder.DataProcessingRegister.AddSubstractExtendedRegister.SubDecoder.cpp \
	./src/decoder/DataProcessingRegister/SubDecoder/disxx.disasm.decoder.DataProcessingRegister.ConditionalCompareImmediate.SubDecoder.cpp \
	./src/decoder/DataProcessingRegister/SubDecoder/disxx.disasm.decoder.DataProcessingRegister.EvaluateIntoFlags.SubDecoder.cpp \
	./src/decoder/DataProcessingRegister/SubDecoder/disxx.disasm.decoder.DataProcessingRegister.RotateRightIntoFlags.SubDecoder.cpp \
	./src/decoder/DataProcessingRegister/SubDecoder/disxx.disasm.decoder.DataProcessingRegister.ConditionalSelect.SubDecoder.cpp \
	./src/decoder/DataProcessingRegister/SubDecoder/disxx.disasm.decoder.DataProcessingRegister.DataProcessing1Source.SubDecoder.cpp \
	./src/decoder/DataProcessingRegister/SubDecoder/disxx.disasm.decoder.DataProcessingRegister.ConditionalCompareRegister.SubDecoder.cpp \
	./src/decoder/DataProcessingRegister/SubDecoder/disxx.disasm.decoder.DataProcessingRegister.AddSubstractCheckedPointer.SubDecoder.cpp \
	./src/decoder/DataProcessingRegister/disxx.disasm.decoder.DataProcessingRegister.Decoder.cpp \
	./src/decoder/DataProcessingImmediate/SubDecoder/disxx.disasm.decoder.DataProcessingImmediate.MoveWideImmediate.SubDecoder.cpp \
	./src/decoder/DataProcessingImmediate/SubDecoder/disxx.disasm.decoder.DataProcessingImmediate.Bitfield.SubDecoder.cpp \
	./src/decoder/DataProcessingImmediate/SubDecoder/disxx.disasm.decoder.DataProcessingImmediate.Extract.SubDecoder.cpp \
	./src/decoder/DataProcessingImmediate/SubDecoder/disxx.disasm.decoder.DataProcessingImmediate.DataProcessing1SourceImmediate.SubDecoder.cpp \
	./src/decoder/DataProcessingImmediate/SubDecoder/disxx.disasm.decoder.DataProcessingImmediate.MinMaxImmediate.SubDecoder.cpp \
	./src/decoder/DataProcessingImmediate/SubDecoder/disxx.disasm.decoder.DataProcessingImmediate.AddSubstractImmediateWithTags.SubDecoder.cpp \
	./src/decoder/DataProcessingImmediate/SubDecoder/disxx.disasm.decoder.DataProcessingImmediate.PCRelAddressing.SubDecoder.cpp \
	./src/decoder/DataProcessingImmediate/SubDecoder/disxx.disasm.decoder.DataProcessingImmediate.AddSubstractImmediate.SubDecoder.cpp \
	./src/decoder/DataProcessingImmediate/SubDecoder/disxx.disasm.decoder.DataProcessingImmediate.LogicalImmediate.SubDecoder.cpp \
	./src/decoder/DataProcessingImmediate/disxx.disasm.decoder.DataProcessingImmediate.Decoder.cpp \
	./src/decoder/Reserved/SubDecoder/disxx.disasm.decoder.Reserved.UDF.SubDecoder.cpp \
	./src/decoder/Reserved/disxx.disasm.decoder.Reserved.Decoder.cpp \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.FloatingPointCompare.SubDecoder.cpp \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.FloatingPointDataProcessing3Source.SubDecoder.cpp \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDThreeSameFP16.SubDecoder.cpp \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.ConversionBetweenFloatingPointAndFixedPoint.SubDecoder.cpp \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDScalarThreeSameExtra.SubDecoder.cpp \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDScalarTwoRegisterMiscellaneousFP16.SubDecoder.cpp \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.FloatingPointConditionalSelect.SubDecoder.cpp \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDTableLookup.SubDecoder.cpp \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDAcrossLanes.SubDecoder.cpp \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDScalarPairwise.SubDecoder.cpp \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.FloatingPointDataProcessing2Source.SubDecoder.cpp \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDTwoRegisterMiscellaneous.SubDecoder.cpp \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.CryptographicAES.SubDecoder.cpp \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDThreeSame.SubDecoder.cpp \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDModifiedImmediate.SubDecoder.cpp \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.CryptographicTwoRegisterSHA.SubDecoder.cpp \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.CryptographicTwoRegisterSHA512.SubDecoder.cpp \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDScalarThreeDifferent.SubDecoder.cpp \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDExtract.SubDecoder.cpp \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDPermute.SubDecoder.cpp \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDThreeDifferent.SubDecoder.cpp \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDScalarTwoRegisterMiscellaneous.SubDecoder.cpp \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDScalarXIndexedElement.SubDecoder.cpp \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDScalarCopy.SubDecoder.cpp \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.CryptographicThreeRegisterSHA.SubDecoder.cpp \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.CryptographicThreeRegisterImm2.SubDecoder.cpp \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDVectorXIndexedElement.SubDecoder.cpp \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.CryptographicFourRegister.SubDecoder.cpp \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDScalarThreeSameFP16.SubDecoder.cpp \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDTwoRegisterMiscellaneousFP16.SubDecoder.cpp \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.FloatingPointConditionalCompare.SubDecoder.cpp \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDScalarThreeSame.SubDecoder.cpp \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.ConversionBetweenFloatingPointAndInteger.SubDecoder.cpp \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.FloatingPointImmediate.SubDecoder.cpp \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.XAR.SubDecoder.cpp \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.FloatingPointDataProcessing1Source.SubDecoder.cpp \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDShiftByImmediate.SubDecoder.cpp \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDThreeRegisterExtension.SubDecoder.cpp \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDScalarShiftByImmediate.SubDecoder.cpp \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.AdvancedSIMDCopy.SubDecoder.cpp \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/SubDecoder/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.CryptographicThreeRegisterSHA512.SubDecoder.cpp \
	./src/decoder/DataProcessingScalarFPAndAdvancedSIMD/disxx.disasm.decoder.DataProcessingScalarFPAndAdvancedSIMD.Decoder.cpp \
	./src/decoder/DecoderFactory/disxx.disasm.decoder.DecoderFactory.cpp \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.LDAPRSTLRWriteback.SubDecoder.cpp \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.MemoryCopyAndMemorySet.SubDecoder.cpp \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.CompareAndSwapUnprivileged.SubDecoder.cpp \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.CompareAndSwapPairUnprivileged.SubDecoder.cpp \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.CompareAndSwap.SubDecoder.cpp \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.OneHundredAndTwentyEightBitAtomicMemoryOperations.SubDecoder.cpp \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.GCS.SubDecoder.cpp \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.AtomicMemoryOperationsUnprivileged.SubDecoder.cpp \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.RegisterImmediatePostIndexed.SubDecoder.cpp \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.LDIAPPSTILP.SubDecoder.cpp \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.RegisterPairPreIndexed.SubDecoder.cpp \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.RegisterImmediatePreIndexed.SubDecoder.cpp \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.NoAllocatePairOffset.SubDecoder.cpp \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.SIMDSingleStructurePostIndexed.SubDecoder.cpp \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.SIMDSingleStructure.SubDecoder.cpp \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.LDAPRSTLRSIMDAndFP.SubDecoder.cpp \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.SIMDMultipleStructures.SubDecoder.cpp \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.RCWCompareAndSwapPair.SubDecoder.cpp \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.RegisterPairOffset.SubDecoder.cpp \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.RegisterPairPostIndexed.SubDecoder.cpp \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.AtomicMemoryOperations.SubDecoder.cpp \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.Ordered.SubDecoder.cpp \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.CompareAndSwapPair.SubDecoder.cpp \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.RegisterLiteral.SubDecoder.cpp \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.SIMDMultipleStructuresPostIndexed.SubDecoder.cpp \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.RCWCompareAndSwap.SubDecoder.cpp \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.ExclusiveRegisterUnprivileged.SubDecoder.cpp \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.RegisterUnprivileged.SubDecoder.cpp \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.RegisterPAC.SubDecoder.cpp \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.RegisterUnsignedImmediate.SubDecoder.cpp \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.LDAPRSTLRUnscaledImmediate.SubDecoder.cpp \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.ExclusivePair.SubDecoder.cpp \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.ExclusiveRegister.SubDecoder.cpp \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.MemoryTags.SubDecoder.cpp \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.RegisterOffset.SubDecoder.cpp \
	./src/decoder/LoadsAndStores/SubDecoder/disxx.disasm.decoder.LoadsAndStores.RegisterUnscaledImmediate.SubDecoder.cpp \
	./src/decoder/LoadsAndStores/disxx.disasm.decoder.LoadsAndStores.Decoder.cpp \
	./src/decoder/BranchesExceptionsAndSystemInstructions/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.Decoder.cpp \
	./src/decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.TestAndBranchImmediate.SubDecoder.cpp \
	./src/decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.UnconditionalBranchRegister.SubDecoder.cpp \
	./src/decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.Barriers.SubDecoder.cpp \
	./src/decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.SystemRegisterMove.SubDecoder.cpp \
	./src/decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.UnconditionalBranchImmediate.SubDecoder.cpp \
	./src/decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.ConditionalBranchImmediate.SubDecoder.cpp \
	./src/decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.CompareRegisterWithImmediateAndBranch.SubDecoder.cpp \
	./src/decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.SystemRegisterPairMove.SubDecoder.cpp \
	./src/decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.SystemInstructionIDs.SubDecoder.cpp \
	./src/decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.CompareAndBranchImmediate.SubDecoder.cpp \
	./src/decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.SystemWithResult.SubDecoder.cpp \
	./src/decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.SystemPairInstructionIDs.SubDecoder.cpp \
	./src/decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.SystemInstructionIDsWithRegisterArgument.SubDecoder.cpp \
	./src/decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.CompareBytesHalfwordsInRegisterAndBranch.SubDecoder.cpp \
	./src/decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.Hints.SubDecoder.cpp \
	./src/decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.PSTATE.SubDecoder.cpp \
	./src/decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.CompareRegistersAndBranch.SubDecoder.cpp \
	./src/decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.MiscellaneousBranchImmediate.SubDecoder.cpp \
	./src/decoder/BranchesExceptionsAndSystemInstructions/SubDecoder/disxx.disasm.decoder.BranchesExceptionsAndSystemInstructions.ExceptionGeneration.SubDecoder.cpp \
	./src/disxx.disasm.Address.cpp \
	./src/disxx.disasm.Instruction.cpp \
	./src/disxx.disasm.Disassembler.cpp

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
	make -C ../disxx-utility/
	$(MOVE) ../../build/disxx-utility/$(notdir $@) $@
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
