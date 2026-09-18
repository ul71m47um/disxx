export module disxx.utility.trait.IClone;

export import std;

export namespace disxx::utility::trait
{
	template <typename T>
	class IClone
	{
	  public:
		virtual ~IClone(void) noexcept = default;

		virtual std::unique_ptr<T> Clone(void) const noexcept = 0;
	};
} /* disxx::utility::trait */
