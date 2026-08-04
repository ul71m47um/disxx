export module disxx.utility.pointer.DefaultDeleter;

import std;

export namespace disxx::utility::pointer
{
	template <typename T>
	class [[clang::type_visibility("hidden")]] [[nodiscard]] DefaultDeleter
	{
	  public:
		constexpr explicit DefaultDeleter(void) noexcept = default;

		constexpr DefaultDeleter(const DefaultDeleter &) noexcept = default;
		constexpr DefaultDeleter &operator=(const DefaultDeleter &) noexcept = default;

		constexpr void operator()(T &) const noexcept;
	};

	template <typename T>
	constexpr void DefaultDeleter<T>::operator()(T &ptr) const noexcept
	{
		if (std::is_array<T>::value && ptr)
			delete [] ptr;
		else if (std::is_pointer<T>::value && ptr)
			delete ptr;
	}
} /* disxx::utility::pointer */
