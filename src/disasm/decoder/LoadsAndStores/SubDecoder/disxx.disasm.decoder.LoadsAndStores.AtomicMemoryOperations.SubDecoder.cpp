module disxx.disasm.decoder.LoadsAndStores.AtomicMemoryOperations.SubDecoder;

import disxx.disasm.operand.LoadsAndStoresAddress;
import disxx.utility.error.DisassemblyError;
import disxx.disasm.operand.Register;
import disxx.disasm.InstructionIdentifier;
import disxx.disasm.utility.bits;

namespace disxx::disasm::decoder::LoadsAndStores::AtomicMemoryOperations
{
	SubDecoder::SubDecoder(void) noexcept
		: disxx::disasm::decoder::abstract::SubDecoder{}
	{}

	SubDecoder::SubDecoder(std::uint32_t insn, std::uint64_t addr) noexcept
		: disxx::disasm::decoder::abstract::SubDecoder{insn, addr}
	{}

	SubDecoder::SubDecoder(const SubDecoder &other) noexcept
		: disxx::disasm::decoder::abstract::SubDecoder{other}
	{}

	SubDecoder &SubDecoder::operator=(const SubDecoder &other) noexcept
	{
		if (this != &other)
			[[maybe_unused]] const auto &_{disxx::disasm::decoder::abstract::SubDecoder::operator=(other)};
		return *this;
	}

	SubDecoder::SubDecoder(SubDecoder &&other) noexcept
		: disxx::disasm::decoder::abstract::SubDecoder{std::move(other)}
	{}

	SubDecoder &SubDecoder::operator=(SubDecoder &&other) noexcept
	{
		[[maybe_unused]] const auto &_{disxx::disasm::decoder::abstract::SubDecoder::operator=(std::move(other))};
		return *this;
	}

	std::unique_ptr<disxx::disasm::decoder::abstract::SubDecoder> SubDecoder::Clone(void) const noexcept
	{ return std::make_unique<std::decay_t<decltype(*this)>>(*this); }

	DisassemblyResult SubDecoder::Decode(void) const noexcept
	{
        // +----+---+--+--+-+-+-+--+--+---+--+--+--+
        // |size|111|VR|00|A|R|1|Rs|o3|opc|00|Rn|Rt|
        // +----+---+--+--+-+-+-+--+--+---+--+--+--+

        unsigned short int size, VR, A, R, Rs, o3, opc, Rn, Rt;
        size = bits::extract<unsigned short int, std::uint32_t, 30, 31>(this->m_Insn);
        VR = bits::extract<unsigned short int, std::uint32_t, 26, 26>(this->m_Insn);
        A = bits::extract<unsigned short int, std::uint32_t, 23, 23>(this->m_Insn);
        R = bits::extract<unsigned short int, std::uint32_t, 22, 22>(this->m_Insn);
        Rs = bits::extract<unsigned short int, std::uint32_t, 16, 20>(this->m_Insn);
        o3 = bits::extract<unsigned short int, std::uint32_t, 15, 15>(this->m_Insn);
        opc = bits::extract<unsigned short int, std::uint32_t, 12, 14>(this->m_Insn);
        Rn = bits::extract<unsigned short int, std::uint32_t, 5, 9>(this->m_Insn);
        Rt = bits::extract<unsigned short int, std::uint32_t, 0, 4>(this->m_Insn);
    
        static const std::unordered_map<unsigned short int, std::pair<InstructionIdentifier, std::optional<InstructionIdentifier>>> insnTable1 = {
            {0b000000000, {InstructionIdentifier::ID_LDADDB, InstructionIdentifier::ID_STADDB}},
            {0b000010000, {InstructionIdentifier::ID_LDADDLB, InstructionIdentifier::ID_STADDLB}},
            {0b000100000, {InstructionIdentifier::ID_LDADDAB, std::nullopt}},
            {0b000110000, {InstructionIdentifier::ID_LDADDALB, std::nullopt}},
            {0b000000001, {InstructionIdentifier::ID_LDCLRB, InstructionIdentifier::ID_STCLRB}},
            {0b000010001, {InstructionIdentifier::ID_LDCLRLB, InstructionIdentifier::ID_STCLRLB}},
            {0b000100001, {InstructionIdentifier::ID_LDCLRAB, std::nullopt}},
            {0b000110001, {InstructionIdentifier::ID_LDCLRALB, std::nullopt}},
            {0b000000010, {InstructionIdentifier::ID_LDEORB, InstructionIdentifier::ID_STEORB}},
            {0b000010010, {InstructionIdentifier::ID_LDEORLB, InstructionIdentifier::ID_STEORLB}},
            {0b000100010, {InstructionIdentifier::ID_LDEORAB, std::nullopt}},
            {0b000110010, {InstructionIdentifier::ID_LDEORALB, std::nullopt}},
            {0b000000011, {InstructionIdentifier::ID_LDSETB, InstructionIdentifier::ID_STSETB}},
            {0b000010011, {InstructionIdentifier::ID_LDSETLB, InstructionIdentifier::ID_STSETLB}},
            {0b000100011, {InstructionIdentifier::ID_LDSETAB, std::nullopt}},
            {0b000110011, {InstructionIdentifier::ID_LDSETALB, std::nullopt}},
            {0b000000100, {InstructionIdentifier::ID_LDSMAXB, InstructionIdentifier::ID_STSMAXB}},
            {0b000010100, {InstructionIdentifier::ID_LDSMAXLB, InstructionIdentifier::ID_STSMAXLB}},
            {0b000100100, {InstructionIdentifier::ID_LDSMAXAB, std::nullopt}},
            {0b000110100, {InstructionIdentifier::ID_LDSMAXALB, std::nullopt}},
            {0b000000101, {InstructionIdentifier::ID_LDSMINB, InstructionIdentifier::ID_STSMINB}},
            {0b000010101, {InstructionIdentifier::ID_LDSMINLB, InstructionIdentifier::ID_STSMINLB}},
            {0b000100101, {InstructionIdentifier::ID_LDSMINAB, std::nullopt}},
            {0b000110101, {InstructionIdentifier::ID_LDSMINALB, std::nullopt}},
            {0b000000110, {InstructionIdentifier::ID_LDUMAXB, InstructionIdentifier::ID_STUMAXB}},
            {0b000010110, {InstructionIdentifier::ID_LDUMAXLB, InstructionIdentifier::ID_STUMAXLB}},
            {0b000100110, {InstructionIdentifier::ID_LDUMAXAB, std::nullopt}},
            {0b000110110, {InstructionIdentifier::ID_LDUMAXALB, std::nullopt}},
            {0b000000111, {InstructionIdentifier::ID_LDUMINB, InstructionIdentifier::ID_STUMINB}},
            {0b000010111, {InstructionIdentifier::ID_LDUMINLB, InstructionIdentifier::ID_STUMINLB}},
            {0b000100111, {InstructionIdentifier::ID_LDUMINAB, std::nullopt}},
            {0b000110111, {InstructionIdentifier::ID_LDUMINALB, std::nullopt}},
            {0b000001000, {InstructionIdentifier::ID_SWPB, std::nullopt}},
            {0b000011000, {InstructionIdentifier::ID_SWPLB, std::nullopt}},
            {0b000101000, {InstructionIdentifier::ID_SWPAB, std::nullopt}},
            {0b000111000, {InstructionIdentifier::ID_SWPALB, std::nullopt}},
            {0b000101100, {InstructionIdentifier::ID_LDAPRB, std::nullopt}},
            {0b010000000, {InstructionIdentifier::ID_LDADDH, InstructionIdentifier::ID_STADDH}},
            {0b010010000, {InstructionIdentifier::ID_LDADDLH, InstructionIdentifier::ID_STADDLH}},
            {0b010100000, {InstructionIdentifier::ID_LDADDAH, std::nullopt}},
            {0b010110000, {InstructionIdentifier::ID_LDADDALH, std::nullopt}},
            {0b010000001, {InstructionIdentifier::ID_LDCLRH, InstructionIdentifier::ID_STCLRH}},
            {0b010010001, {InstructionIdentifier::ID_LDCLRLH, InstructionIdentifier::ID_STCLRLH}},
            {0b010100001, {InstructionIdentifier::ID_LDCLRAH, std::nullopt}},
            {0b010110001, {InstructionIdentifier::ID_LDCLRALH, std::nullopt}},
            {0b010000010, {InstructionIdentifier::ID_LDEORH, InstructionIdentifier::ID_STEORH}},
            {0b010010010, {InstructionIdentifier::ID_LDEORLH, InstructionIdentifier::ID_STEORLH}},
            {0b010100010, {InstructionIdentifier::ID_LDEORAH, std::nullopt}},
            {0b010110010, {InstructionIdentifier::ID_LDEORALH, std::nullopt}},
            {0b010000011, {InstructionIdentifier::ID_LDSETH, InstructionIdentifier::ID_STSETH}},
            {0b010010011, {InstructionIdentifier::ID_LDSETLH, InstructionIdentifier::ID_STSETLH}},
            {0b010100011, {InstructionIdentifier::ID_LDSETAH, std::nullopt}},
            {0b010110011, {InstructionIdentifier::ID_LDSETALH, std::nullopt}},
            {0b010000100, {InstructionIdentifier::ID_LDSMAXH, InstructionIdentifier::ID_STSMAXH}},
            {0b010010100, {InstructionIdentifier::ID_LDSMAXLH, InstructionIdentifier::ID_STSMAXLH}},
            {0b010100100, {InstructionIdentifier::ID_LDSMAXAH, std::nullopt}},
            {0b010110100, {InstructionIdentifier::ID_LDSMAXALH, std::nullopt}},
            {0b010000101, {InstructionIdentifier::ID_LDSMINH, InstructionIdentifier::ID_STSMINH}},
            {0b010010101, {InstructionIdentifier::ID_LDSMINLH, InstructionIdentifier::ID_STSMINLH}},
            {0b010100101, {InstructionIdentifier::ID_LDSMINAH, std::nullopt}},
            {0b010110101, {InstructionIdentifier::ID_LDSMINALH, std::nullopt}},
            {0b010000110, {InstructionIdentifier::ID_LDUMAXH, InstructionIdentifier::ID_STUMAXH}},
            {0b010010110, {InstructionIdentifier::ID_LDUMAXLH, InstructionIdentifier::ID_STUMAXLH}},
            {0b010100110, {InstructionIdentifier::ID_LDUMAXAH, std::nullopt}},
            {0b010110110, {InstructionIdentifier::ID_LDUMAXALH, std::nullopt}},
            {0b010000111, {InstructionIdentifier::ID_LDUMINH, InstructionIdentifier::ID_STUMINH}},
            {0b010010111, {InstructionIdentifier::ID_LDUMINLH, InstructionIdentifier::ID_STUMINLH}},
            {0b010100111, {InstructionIdentifier::ID_LDUMINAH, std::nullopt}},
            {0b010110111, {InstructionIdentifier::ID_LDUMINALH, std::nullopt}},
            {0b010001000, {InstructionIdentifier::ID_SWPH, std::nullopt}},
            {0b010011000, {InstructionIdentifier::ID_SWPLH, std::nullopt}},
            {0b010101000, {InstructionIdentifier::ID_SWPAH, std::nullopt}},
            {0b010111000, {InstructionIdentifier::ID_SWPALH, std::nullopt}},
            {0b010101100, {InstructionIdentifier::ID_LDAPRH, std::nullopt}},
            {0b100000000, {InstructionIdentifier::ID_LDADD, InstructionIdentifier::ID_STADD}},
            {0b100010000, {InstructionIdentifier::ID_LDADDL, InstructionIdentifier::ID_STADDL}},
            {0b100100000, {InstructionIdentifier::ID_LDADDA, std::nullopt}},
            {0b100110000, {InstructionIdentifier::ID_LDADDAL, std::nullopt}},
            {0b100000001, {InstructionIdentifier::ID_LDCLR, InstructionIdentifier::ID_STCLR}},
            {0b100010001, {InstructionIdentifier::ID_LDCLRL, InstructionIdentifier::ID_STCLRL}},
            {0b100100001, {InstructionIdentifier::ID_LDCLRA, std::nullopt}},
            {0b100110001, {InstructionIdentifier::ID_LDCLRAL, std::nullopt}},
            {0b100000010, {InstructionIdentifier::ID_LDEOR, InstructionIdentifier::ID_STEOR}},
            {0b100010010, {InstructionIdentifier::ID_LDEORL, InstructionIdentifier::ID_STEORL}},
            {0b100100010, {InstructionIdentifier::ID_LDEORA, std::nullopt}},
            {0b100110010, {InstructionIdentifier::ID_LDEORAL, std::nullopt}},
            {0b100000011, {InstructionIdentifier::ID_LDSET, InstructionIdentifier::ID_STSET}},
            {0b100010011, {InstructionIdentifier::ID_LDSETL, InstructionIdentifier::ID_STSETL}},
            {0b100100011, {InstructionIdentifier::ID_LDSETA, std::nullopt}},
            {0b100110011, {InstructionIdentifier::ID_LDSETAL, std::nullopt}},
            {0b100000100, {InstructionIdentifier::ID_LDSMAX, InstructionIdentifier::ID_STSMAX}},
            {0b100010100, {InstructionIdentifier::ID_LDSMAXL, InstructionIdentifier::ID_STSMAXL}},
            {0b100100100, {InstructionIdentifier::ID_LDSMAXA, std::nullopt}},
            {0b100110100, {InstructionIdentifier::ID_LDSMAXAL, std::nullopt}},
            {0b100000101, {InstructionIdentifier::ID_LDSMIN, InstructionIdentifier::ID_STSMIN}},
            {0b100010101, {InstructionIdentifier::ID_LDSMINL, InstructionIdentifier::ID_STSMINL}},
            {0b100100101, {InstructionIdentifier::ID_LDSMINA, std::nullopt}},
            {0b100110101, {InstructionIdentifier::ID_LDSMINAL, std::nullopt}},
            {0b100000110, {InstructionIdentifier::ID_LDUMAX, InstructionIdentifier::ID_STUMAX}},
            {0b100010110, {InstructionIdentifier::ID_LDUMAXL, InstructionIdentifier::ID_STUMAXL}},
            {0b100100110, {InstructionIdentifier::ID_LDUMAXA, std::nullopt}},
            {0b100110110, {InstructionIdentifier::ID_LDUMAXAL, std::nullopt}},
            {0b100000111, {InstructionIdentifier::ID_LDUMIN, InstructionIdentifier::ID_STUMIN}},
            {0b100010111, {InstructionIdentifier::ID_LDUMINL, InstructionIdentifier::ID_STUMINL}},
            {0b100100111, {InstructionIdentifier::ID_LDUMINA, std::nullopt}},
            {0b100110111, {InstructionIdentifier::ID_LDUMINAL, std::nullopt}},
            {0b100001000, {InstructionIdentifier::ID_SWP, std::nullopt}},
            {0b100011000, {InstructionIdentifier::ID_SWPL, std::nullopt}},
            {0b100101000, {InstructionIdentifier::ID_SWPA, std::nullopt}},
            {0b100111000, {InstructionIdentifier::ID_SWPAL, std::nullopt}},
            {0b100101100, {InstructionIdentifier::ID_LDAPR, std::nullopt}},
            {0b110000000, {InstructionIdentifier::ID_LDADD, InstructionIdentifier::ID_STADD}},
            {0b110010000, {InstructionIdentifier::ID_LDADDL, InstructionIdentifier::ID_STADDL}},
            {0b110100000, {InstructionIdentifier::ID_LDADDA, std::nullopt}},
            {0b110110000, {InstructionIdentifier::ID_LDADDAL, std::nullopt}},
            {0b110000001, {InstructionIdentifier::ID_LDCLR, InstructionIdentifier::ID_STCLR}},
            {0b110010001, {InstructionIdentifier::ID_LDCLRL, InstructionIdentifier::ID_STCLRL}},
            {0b110100001, {InstructionIdentifier::ID_LDCLRA, std::nullopt}},
            {0b110110001, {InstructionIdentifier::ID_LDCLRAL, std::nullopt}},
            {0b110000010, {InstructionIdentifier::ID_LDEOR, InstructionIdentifier::ID_STEOR}},
            {0b110010010, {InstructionIdentifier::ID_LDEORL, InstructionIdentifier::ID_STEORL}},
            {0b110100010, {InstructionIdentifier::ID_LDEORA, std::nullopt}},
            {0b110110010, {InstructionIdentifier::ID_LDEORAL, std::nullopt}},
            {0b110000011, {InstructionIdentifier::ID_LDSET, InstructionIdentifier::ID_STSET}},
            {0b110010011, {InstructionIdentifier::ID_LDSETL, InstructionIdentifier::ID_STSETL}},
            {0b110100011, {InstructionIdentifier::ID_LDSETA, std::nullopt}},
            {0b110110011, {InstructionIdentifier::ID_LDSETAL, std::nullopt}},
            {0b110000100, {InstructionIdentifier::ID_LDSMAX, InstructionIdentifier::ID_STSMAX}},
            {0b110010100, {InstructionIdentifier::ID_LDSMAXL, InstructionIdentifier::ID_STSMAXL}},
            {0b110100100, {InstructionIdentifier::ID_LDSMAXA, std::nullopt}},
            {0b110110100, {InstructionIdentifier::ID_LDSMAXAL, std::nullopt}},
            {0b110000101, {InstructionIdentifier::ID_LDSMIN, InstructionIdentifier::ID_STSMIN}},
            {0b110010101, {InstructionIdentifier::ID_LDSMINL, InstructionIdentifier::ID_STSMINL}},
            {0b110100101, {InstructionIdentifier::ID_LDSMINA, std::nullopt}},
            {0b110110101, {InstructionIdentifier::ID_LDSMINAL, std::nullopt}},
            {0b110000110, {InstructionIdentifier::ID_LDUMAX, InstructionIdentifier::ID_STUMAX}},
            {0b110010110, {InstructionIdentifier::ID_LDUMAXL, InstructionIdentifier::ID_STUMAXL}},
            {0b110100110, {InstructionIdentifier::ID_LDUMAXA, std::nullopt}},
            {0b110110110, {InstructionIdentifier::ID_LDUMAXAL, std::nullopt}},
            {0b110000111, {InstructionIdentifier::ID_LDUMIN, InstructionIdentifier::ID_STUMIN}},
            {0b110010111, {InstructionIdentifier::ID_LDUMINL, InstructionIdentifier::ID_STUMINL}},
            {0b110100111, {InstructionIdentifier::ID_LDUMINA, std::nullopt}},
            {0b110110111, {InstructionIdentifier::ID_LDUMINAL, std::nullopt}},
            {0b110001000, {InstructionIdentifier::ID_SWP, std::nullopt}},
            {0b110011000, {InstructionIdentifier::ID_SWPL, std::nullopt}},
            {0b110101000, {InstructionIdentifier::ID_SWPA, std::nullopt}},
            {0b110111000, {InstructionIdentifier::ID_SWPAL, std::nullopt}},
            {0b110001010, {InstructionIdentifier::ID_ST64BVO, std::nullopt}},
            {0b110001011, {InstructionIdentifier::ID_ST64BV, std::nullopt}},
            {0b110101100, {InstructionIdentifier::ID_LDAPR, std::nullopt}}
        };

        static const std::unordered_map<unsigned short int, InstructionIdentifier> insnTable2 = {
            {0b001000000, InstructionIdentifier::ID_LDBFADD},
            {0b001010000, InstructionIdentifier::ID_LDBFADDL},
            {0b001100000, InstructionIdentifier::ID_LDBFADDA},
            {0b001110000, InstructionIdentifier::ID_LDBFADDAL},
            {0b001000100, InstructionIdentifier::ID_LDBFMAX},
            {0b001010100, InstructionIdentifier::ID_LDBFMAXL},
            {0b001100100, InstructionIdentifier::ID_LDBFMAXA},
            {0b001110100, InstructionIdentifier::ID_LDBFMAXAL},
            {0b001000101, InstructionIdentifier::ID_LDBFMIN},
            {0b001010101, InstructionIdentifier::ID_LDBFMINL},
            {0b001100101, InstructionIdentifier::ID_LDBFMINA},
            {0b001110101, InstructionIdentifier::ID_LDBFMINAL},
            {0b001000110, InstructionIdentifier::ID_LDBFMAXNM},
            {0b001010110, InstructionIdentifier::ID_LDBFMAXNML},
            {0b001100110, InstructionIdentifier::ID_LDBFMAXNMA},
            {0b001110110, InstructionIdentifier::ID_LDBFMAXNMAL},
            {0b001000111, InstructionIdentifier::ID_LDBFMINNM},
            {0b001010111, InstructionIdentifier::ID_LDBFMINNML},
            {0b001100111, InstructionIdentifier::ID_LDBFMINNMA},
            {0b001110111, InstructionIdentifier::ID_LDBFMINNMAL},
            {0b011000000, InstructionIdentifier::ID_LDFADD},
            {0b011010000, InstructionIdentifier::ID_LDFADDL},
            {0b011100000, InstructionIdentifier::ID_LDFADDA},
            {0b011110000, InstructionIdentifier::ID_LDFADDAL},
            {0b011000100, InstructionIdentifier::ID_LDFMAX},
            {0b011010100, InstructionIdentifier::ID_LDFMAXL},
            {0b011100100, InstructionIdentifier::ID_LDFMAXA},
            {0b011110100, InstructionIdentifier::ID_LDFMAXAL},
            {0b011000101, InstructionIdentifier::ID_LDFMIN},
            {0b011010101, InstructionIdentifier::ID_LDFMINL},
            {0b011100101, InstructionIdentifier::ID_LDFMINA},
            {0b011110101, InstructionIdentifier::ID_LDFMINAL},
            {0b011000110, InstructionIdentifier::ID_LDFMAXNM},
            {0b011010110, InstructionIdentifier::ID_LDFMAXNML},
            {0b011100110, InstructionIdentifier::ID_LDFMAXNMA},
            {0b011110110, InstructionIdentifier::ID_LDFMAXNMAL},
            {0b011000111, InstructionIdentifier::ID_LDFMINNM},
            {0b011010111, InstructionIdentifier::ID_LDFMINNML},
            {0b011100111, InstructionIdentifier::ID_LDFMINNMA},
            {0b011110111, InstructionIdentifier::ID_LDFMINNMAL},
            {0b101000000, InstructionIdentifier::ID_LDFADD},
            {0b101010000, InstructionIdentifier::ID_LDFADDL},
            {0b101100000, InstructionIdentifier::ID_LDFADDA},
            {0b101110000, InstructionIdentifier::ID_LDFADDAL},
            {0b101000100, InstructionIdentifier::ID_LDFMAX},
            {0b101010100, InstructionIdentifier::ID_LDFMAXL},
            {0b101100100, InstructionIdentifier::ID_LDFMAXA},
            {0b101110100, InstructionIdentifier::ID_LDFMAXAL},
            {0b101000101, InstructionIdentifier::ID_LDFMIN},
            {0b101010101, InstructionIdentifier::ID_LDFMINL},
            {0b101100101, InstructionIdentifier::ID_LDFMINA},
            {0b101110101, InstructionIdentifier::ID_LDFMINAL},
            {0b101000110, InstructionIdentifier::ID_LDFMAXNM},
            {0b101010110, InstructionIdentifier::ID_LDFMAXNML},
            {0b101100110, InstructionIdentifier::ID_LDFMAXNMA},
            {0b101110110, InstructionIdentifier::ID_LDFMAXNMAL},
            {0b101000111, InstructionIdentifier::ID_LDFMINNM},
            {0b101010111, InstructionIdentifier::ID_LDFMINNML},
            {0b101100111, InstructionIdentifier::ID_LDFMINNMA},
            {0b101110111, InstructionIdentifier::ID_LDFMINNMAL},
            {0b111000000, InstructionIdentifier::ID_LDFADD},
            {0b111010000, InstructionIdentifier::ID_LDFADDL},
            {0b111100000, InstructionIdentifier::ID_LDFADDA},
            {0b111110000, InstructionIdentifier::ID_LDFADDAL},
            {0b111000100, InstructionIdentifier::ID_LDFMAX},
            {0b111010100, InstructionIdentifier::ID_LDFMAXL},
            {0b111100100, InstructionIdentifier::ID_LDFMAXA},
            {0b111110100, InstructionIdentifier::ID_LDFMAXAL},
            {0b111000101, InstructionIdentifier::ID_LDFMIN},
            {0b111010101, InstructionIdentifier::ID_LDFMINL},
            {0b111100101, InstructionIdentifier::ID_LDFMINA},
            {0b111110101, InstructionIdentifier::ID_LDFMINAL},
            {0b111000110, InstructionIdentifier::ID_LDFMAXNM},
            {0b111010110, InstructionIdentifier::ID_LDFMAXNML},
            {0b111100110, InstructionIdentifier::ID_LDFMAXNMA},
            {0b111110110, InstructionIdentifier::ID_LDFMAXNMAL},
            {0b111000111, InstructionIdentifier::ID_LDFMINNM},
            {0b111010111, InstructionIdentifier::ID_LDFMINNML},
            {0b111100111, InstructionIdentifier::ID_LDFMINNMA},
            {0b111110111, InstructionIdentifier::ID_LDFMINNMAL}
        };

        static const std::unordered_map<unsigned short int, InstructionIdentifier> insnTable3 = {
            {0b00100100011111, InstructionIdentifier::ID_STBFADD},
            {0b00101100011111, InstructionIdentifier::ID_STBFADDL},
            {0b00100110011111, InstructionIdentifier::ID_STBFMAX},
            {0b00101110011111, InstructionIdentifier::ID_STBFMAXL},
            {0b00100110111111, InstructionIdentifier::ID_STBFMIN},
            {0b00101110111111, InstructionIdentifier::ID_STBFMINL},
            {0b00100111011111, InstructionIdentifier::ID_STBFMAXNM},
            {0b00101111011111, InstructionIdentifier::ID_STBFMAXNML},
            {0b00100111111111, InstructionIdentifier::ID_STBFMINNM},
            {0b00101111111111, InstructionIdentifier::ID_STBFMINNML},
            {0b01100100011111, InstructionIdentifier::ID_STFADD},
            {0b01101100011111, InstructionIdentifier::ID_STFADDL},
            {0b01100110011111, InstructionIdentifier::ID_STFMAX},
            {0b01101110011111, InstructionIdentifier::ID_STFMAXL},
            {0b01100110111111, InstructionIdentifier::ID_STFMIN},
            {0b01101110111111, InstructionIdentifier::ID_STFMINL},
            {0b01100111011111, InstructionIdentifier::ID_STFMAXNM},
            {0b01101111011111, InstructionIdentifier::ID_STFMAXNML},
            {0b01100111111111, InstructionIdentifier::ID_STFMINNM},
            {0b01101111111111, InstructionIdentifier::ID_STFMINNML},
            {0b10100100011111, InstructionIdentifier::ID_STFADD},
            {0b10101100011111, InstructionIdentifier::ID_STFADDL},
            {0b10100110011111, InstructionIdentifier::ID_STFMAX},
            {0b10101110011111, InstructionIdentifier::ID_STFMAXL},
            {0b10100110111111, InstructionIdentifier::ID_STFMIN},
            {0b10101110111111, InstructionIdentifier::ID_STFMINL},
            {0b10100111011111, InstructionIdentifier::ID_STFMAXNM},
            {0b10101111011111, InstructionIdentifier::ID_STFMAXNML},
            {0b10100111111111, InstructionIdentifier::ID_STFMINNM},
            {0b10101111111111, InstructionIdentifier::ID_STFMINNML},
            {0b11100100011111, InstructionIdentifier::ID_STFADD},
            {0b11101100011111, InstructionIdentifier::ID_STFADDL},
            {0b11100110011111, InstructionIdentifier::ID_STFMAX},
            {0b11101110011111, InstructionIdentifier::ID_STFMAXL},
            {0b11100110111111, InstructionIdentifier::ID_STFMIN},
            {0b11101110111111, InstructionIdentifier::ID_STFMINL},
            {0b11100111011111, InstructionIdentifier::ID_STFMAXNM},
            {0b11101111011111, InstructionIdentifier::ID_STFMAXNML},
            {0b11100111111111, InstructionIdentifier::ID_STFMINNM},
            {0b11101111111111, InstructionIdentifier::ID_STFMINNML}
        };

        static const std::unordered_map<unsigned short int, InstructionIdentifier> insnTable4 = {
            {0b000001001, InstructionIdentifier::ID_RCWCLR},
            {0b000011001, InstructionIdentifier::ID_RCWCLRL},
            {0b000101001, InstructionIdentifier::ID_RCWCLRA},
            {0b000111001, InstructionIdentifier::ID_RCWCLRAL},
            {0b000001010, InstructionIdentifier::ID_RCWSWP},
            {0b000011010, InstructionIdentifier::ID_RCWSWPL},
            {0b000101010, InstructionIdentifier::ID_RCWSWPA},
            {0b000111010, InstructionIdentifier::ID_RCWSWPAL},
            {0b000001011, InstructionIdentifier::ID_RCWSET},
            {0b000011011, InstructionIdentifier::ID_RCWSETL},
            {0b000101011, InstructionIdentifier::ID_RCWSETA},
            {0b000111011, InstructionIdentifier::ID_RCWSETAL},
            {0b010001001, InstructionIdentifier::ID_RCWSCLR},
            {0b010011001, InstructionIdentifier::ID_RCWSCLRL},
            {0b010101001, InstructionIdentifier::ID_RCWSCLRA},
            {0b010111001, InstructionIdentifier::ID_RCWSCLRAL},
            {0b010001010, InstructionIdentifier::ID_RCWSSWP},
            {0b010011010, InstructionIdentifier::ID_RCWSSWPL},
            {0b010101010, InstructionIdentifier::ID_RCWSSWPA},
            {0b010111010, InstructionIdentifier::ID_RCWSSWPAL},
            {0b010001011, InstructionIdentifier::ID_RCWSSET},
            {0b010011011, InstructionIdentifier::ID_RCWSSETL},
            {0b010101011, InstructionIdentifier::ID_RCWSSETA},
            {0b010111011, InstructionIdentifier::ID_RCWSSETAL}
        };

        const static std::unordered_map<unsigned short int, InstructionIdentifier> insnTable5 = {
            {0b11000111111001, InstructionIdentifier::ID_ST64B},
            {0b11000111111101, InstructionIdentifier::ID_LD64B}
        };

        this->m_Operands.emplace_back
		(
			std::make_unique<disxx::disasm::operand::Register>
			(
				disxx::disasm::operand::Register::Type::TYPE_X,
				Rn
			)
		);

        const unsigned short int encoding = (size << 7) | (VR << 6) | (A << 5) | (R << 4) | (o3 << 3) | opc;
        if (const auto it{insnTable1.find(encoding)}; it != insnTable1.end())
        {
            const auto &[insn, alias]{it->second};
            this->m_Operands.emplace_back
			(
				std::make_unique<disxx::disasm::operand::Register>
				(
					size == 0b11
						? disxx::disasm::operand::Register::Type::TYPE_X
						: disxx::disasm::operand::Register::Type::TYPE_W,
					Rs
				)
			);
			this->m_Operands.emplace_back
			(
				std::make_unique<disxx::disasm::operand::LoadsAndStoresAddress>
				(
					disxx::disasm::operand::Register
					{
						size == 0b11
							? disxx::disasm::operand::Register::Type::TYPE_X
							: disxx::disasm::operand::Register::Type::TYPE_W,
						Rt
					}
				)
			);

            return std::make_pair(alias ? *alias : insn, std::move(this->m_Operands));
        }
        else if (const auto it2{insnTable2.find(encoding)}; it2 != insnTable2.end())
        {
            static constexpr std::array<disxx::disasm::operand::Register::Type, 4> typeTable
			{
				disxx::disasm::operand::Register::Type::TYPE_H,
				disxx::disasm::operand::Register::Type::TYPE_H,
				disxx::disasm::operand::Register::Type::TYPE_S,
				disxx::disasm::operand::Register::Type::TYPE_D
			};

            this->m_Operands.emplace_back(std::make_unique<disxx::disasm::operand::Register>(typeTable[size], Rs));
            this->m_Operands.emplace_back(std::make_unique<disxx::disasm::operand::Register>(typeTable[size], Rt));
           
            return std::make_pair(it2->second, std::move(this->m_Operands));
        }
        else if (const auto it3{insnTable3.find(encoding)}; it3 != insnTable3.end())
        {
        	this->m_Operands.emplace_back
			(
				std::make_unique<disxx::disasm::operand::Register>
				(
					disxx::disasm::operand::Register::Type::TYPE_X,
					Rs
				)
			);
			this->m_Operands.emplace_back
			(
				std::make_unique<disxx::disasm::operand::LoadsAndStoresAddress>
				(
					disxx::disasm::operand::Register
					{
						disxx::disasm::operand::Register::Type::TYPE_X,
						Rt,
					}
				)
			);
          
            return std::make_pair(it3->second, std::move(this->m_Operands));
        }
        else if (const auto it4{insnTable4.find((encoding << 5) | 0b11111)}; it4 != insnTable4.end())
        {
			static constexpr std::array<disxx::disasm::operand::Register::Type, 4> typeTable
			{
				disxx::disasm::operand::Register::Type::TYPE_H,
				disxx::disasm::operand::Register::Type::TYPE_H,
				disxx::disasm::operand::Register::Type::TYPE_S,
				disxx::disasm::operand::Register::Type::TYPE_D
			};

			this->m_Operands.emplace_back
			(
				std::make_unique<disxx::disasm::operand::LoadsAndStoresAddress>
				(
					disxx::disasm::operand::Register
					{
						typeTable[size],
						Rs
					}
				)
			);

            return std::make_pair(it4->second, std::move(this->m_Operands));
        }
        
        auto it5{insnTable5.find((size << 12) | (VR << 11) | (A << 10) | (R << 9) | (Rs << 4) | (o3 << 3) | opc)};
        if (it5 == insnTable5.end()) [[unlikely]]
            return std::unexpected{disxx::utility::error::DisassemblyError{this->m_Insn}};
           
        this->m_Operands.emplace_back
		(
			std::make_unique<disxx::disasm::operand::LoadsAndStoresAddress>
			(
				disxx::disasm::operand::Register
				{
					disxx::disasm::operand::Register::Type::TYPE_X,
					Rt
				}
			)
		);

        return std::make_pair(it5->second, std::move(this->m_Operands)); 
	}
} /* disxx::disasm::decoder::LoadsAndStores::AtomicMemoryOperations */
