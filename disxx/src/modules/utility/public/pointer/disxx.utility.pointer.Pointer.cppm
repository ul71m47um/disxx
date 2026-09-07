export module disxx.utility.pointer.Pointer;

import std;

export namespace disxx::utility::pointer
{
	template <typename T>
	concept Pointer = requires(T ptr)
	{
		{ ptr == nullptr } -> std::same_as<bool>;
		{ ptr = T{} } -> std::same_as<T &>;
		{ T{ptr} } -> std::same_as<T>;
		{ *ptr };
	};
} /* disxx::utility::pointer */
