export module disxx.utility.Overload;

import std;

export namespace disxx::utility
{
	/*
	 * Just some usable pattern here :D
	 */
	template <typename ...Ts>
	class Overload : Ts...
	{
	  public:
		explicit Overload(Ts ...) noexcept;
		using Ts::operator()...;
	};

	template <typename ...Ts>
	Overload<Ts...>::Overload(Ts ...ts) noexcept
		: Ts{std::move(ts)}...
	{}
} /* disxx::utility */
