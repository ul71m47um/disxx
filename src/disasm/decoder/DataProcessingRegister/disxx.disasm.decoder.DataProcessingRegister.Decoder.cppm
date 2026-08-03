



export module disxx.disasm.decoder.DataProcessingRegister.Decoder;

import disxx.disasm.decoder.abstract.Decoder;
import disxx.utility.error.DisassemblyError;

export namespace disxx::disasm::decoder::DataProcessingRegister
{
	class [[clang::type_visibility("hidden")]] [[nodiscard]] Decoder final : public disxx::disasm::decoder::abstract::Decoder
	{
	  protected:
		virtual std::expected
		<
			std::unique_ptr<disxx::disasm::decoder::abstract::SubDecoder>,
			disxx::utility::error::DisassemblyError
		> __GetDecoder(void) const noexcept override;

	  public:
		explicit Decoder(void) noexcept;
		explicit Decoder(std::uint32_t, std::uint64_t) noexcept;
	
		explicit Decoder(const Decoder &other) noexcept;
		Decoder &operator=(const Decoder &other) noexcept;

		explicit Decoder(Decoder &&other) noexcept;
		Decoder &operator=(Decoder &&other) noexcept;
	};
} /* disxx::disasm::decoder::LoadsAndStores */
