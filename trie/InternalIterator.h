#pragma once

#pragma once
#include <initializer_list>
#include <type_traits>
#include <iterator>
#include <utility>
#include <vector>
#include <exception>

template<typename>
class SubTrie;

template<typename T, bool is_const>
class InternalIterator
{
public:

	template <typename>
	friend class Trie;

	template<typename>
	friend class SubTrie;

	template<typename>
	friend class TestHelper;

	using ref_pair = std::pair<std::string, T&>;
	using const_ref_pair = std::pair<std::string, const T&>;

	using iterator_category = std::forward_iterator_tag;
	
	using pointer = typename std::conditional<
		is_const, 
		const typename const_ref_pair*,
		typename ref_pair*>;
	
	using reference = typename std::conditional<
		is_const, 
		const typename const_ref_pair&,
		typename ref_pair&>;

	using difference_type = std::ptrdiff_t;


	using value_type = typename std::conditional<
		is_const, 
		const std::pair<std::string, const T&>, 
		std::pair<std::string, T&>>::type;
	
	InternalIterator(SubTrie<T>* data_) : data(data_) {};

	InternalIterator(const std::string& search_str_, SubTrie<T>* data_) :
		data(data_) {
		search_str = search_str_;
		symbol = search_str.rbegin();
	};

private:
	std::string::reverse_iterator symbol{};// = NON_INITIALIZED;
	SubTrie<T>* data{};
	std::string search_str;
	std::vector<SubTrie<T>*> attended_nodes{};

	T default_val{}; //чтобы инициализировать
	std::pair<std::string, T&> iter_value{ "", default_val };
	char buf_symb{};
};

