export module disxx.utility.pointer.Weak;

import disxx.utility.pointer.Pointer;

import std;

namespace
{
	template <typename T, typename U>
	concept WeakImpl = requires(T rc, U weak)
	{
		{ weak.lock() } -> std::same_as<T>;
		{ weak = rc };
	};
} /* */

export namespace disxx::utility::pointer
{
	template <typename T, typename U>
	concept Weak = WeakImpl<T, U> || WeakImpl<U, T>;
} /* disxx::utility::pointer */
