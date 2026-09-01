export module disxx.utility.Overload;

export namespace disxx::utility
{
	/*
	 * Just some usable pattern here :D
	 */
	template <typename ...Ts>
	class Overload : Ts...
	{
	  public:
		using Ts::operator()...;
	};
} /* disxx::utility */
