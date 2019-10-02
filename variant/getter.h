#pragma once

/*template<int I, typename Head, typename... Args>
typename getter<I, Head, Args...>::return_type
get(variant<Head, Args...> t)
{
	return getter<I, Head, Args...>::get(t);
};

template<int I, typename Head, typename... Args>
struct getter
{
	typedef typename getter<I - 1, Args...>::return_type return_type;
	static return_type get(variant<Head, Args...> t)
	{
		return getter<I - 1, Args...>::get(t);
	}
};


template<typename Head, typename... Args>
struct getter<0, Head, Args...>
{
	typedef typename variant<Head, Args...>::value_type return_type;
	static return_type get(variant<Head, Args...> t)
	{
		return t.head_;
	}
};*/

