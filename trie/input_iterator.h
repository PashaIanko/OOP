#pragma once
template <class T>
class InputIterator : public std::iterator<std::input_iterator_tag, std::pair<std::string, T&>>
{
	typedef T value_type;
public:
	InputIterator(value_type & x);
	InputIterator() = default;
	InputIterator(const InputIterator& mit);

	InputIterator& operator++();
	InputIterator operator++(int);

	bool operator!=(const InputIterator& rhs);

	value_type operator*();
	value_type * operator->(); //value_type???
}; 
