#pragma once
#include <string>
#include <algorithm>
#include <utility>
#include <memory>
#include <vector>

const char NON_INITIALIZED = '0';

template<typename T>
class SubTrie;


template<typename T>
class has_greater {
public:
	has_greater(char ch_) : ch(ch_) {}

	//	template<typename T>
	bool operator() (const std::pair<char, SubTrie<T>*> & p) {
		if (!(p.second)->if_attended())
			return (p.first >= ch);
		else
			return false;
	}
private:
	char ch;
};

template<typename T>
class is_not_attended {
public:
	is_not_attended() = default;
	is_not_attended(const std::vector<SubTrie<T>*>& vect_) : vect(vect_) {}
	bool operator() (const std::pair<char, SubTrie<T>*> & p) {
		/*if ((p.second)->if_attended() == false) {
			return true;
		}
		else
			return false;*/
		auto it = std::find(vect.begin(), vect.end(), p.second);
		return (it == vect.end());// {
			/*� ������� ��� ���������� ������ �� �����*/
	}
	static bool if_not_attended(std::pair<char, SubTrie<T>*> & p) {
		return true;
	}
private:
	std::vector<SubTrie<T>*> vect;
};


template <class T>
class TrieIterator
{

	typedef std::pair<std::string, T&> value_type;// typedef T value_type;

	template <typename>
	friend class Trie;

	template<typename>
	friend class SubTrie;

	template<typename>
	friend class TestHelper;


public:
	TrieIterator(SubTrie<T>* data_) : data(data_) {};
	TrieIterator(const char symbol_, SubTrie<T>* data_) : symbol(symbol_), data(data_) {};
	TrieIterator(const std::string& search_str_, SubTrie<T>* data_) :
		data(data_) {
		search_str = search_str_;
		symbol = search_str.rbegin();
	};
	TrieIterator() : data(nullptr) {
		search_str = "";
		symbol = search_str.rbegin();
	};

	TrieIterator(const TrieIterator& mit) = default;

	~TrieIterator() {
		search_str.clear();
	}
	TrieIterator& operator++() {
		do {
			auto unvisited = std::find_if(
				data->children.cbegin(),
				data->children.cend(),
				is_not_attended<T>(attended_nodes)
			);
			if (unvisited == (data->children).cend()) {
				SubTrie<T>* parent = data->parent;
				if (parent != nullptr) {


					/*data->attended = true;*/
					add_attended(data);

					data = parent;
					buf_symb = *search_str.rbegin();
					search_str.erase(search_str.size() - 1);
				}
				else {
					init_invalid(this);
					break;
				}
			}
			else {
				search_str += unvisited->first;
				symbol = search_str.rbegin(); //refresh current symbol
				buf_symb = unvisited->first;

				/*data->attended = true;*/
				add_attended(data);

				data = unvisited->second;
			}
		} while (!(this->data->is_end_of_word == true
			&& node_is_not_attended(this->data)));//&& (this->data->attended == false)));
		return *this;
	};


	TrieIterator operator++(int) {
		TrieIterator temp = *this;
		++*this;
		return temp;
	};

	TrieIterator& operator=(const TrieIterator& rhs) = default;

	bool operator==(const TrieIterator& rhs) const { return (this->data == rhs.data); };
	bool operator!=(const TrieIterator& rhs) const { return !(this->data == rhs.data); };

	value_type operator*() {
		init_iter_value();
		return iter_value;//return (this->data)->value; 

	};//{ return std::pair<std::string, T&> p(search_str, (this->data)->value); };
	value_type * operator->() {
		init_iter_value();
		return &iter_value;
		//return &((this->p)->value); 


	}; /*� �� ���� ���������� ���������
		�� �������� ��������� � ���� ������ ����, ��� ����
		����������. �� ���� ���������, ���������, ��� ����� �������
		�����. ������� ������ ���� ������ - ����. �� ������ T& ����� �������������������,
		������� ��������� ���� T default{}, �� ������� ������ ���*/
	inline void set_word_end(const bool arg) { data->is_end_of_word = arg; }
	inline bool is_end_of_word() { return data->is_word_end(); }

	
private:
	std::string::reverse_iterator symbol{};// = NON_INITIALIZED;
	SubTrie<T>* data{};
	std::string search_str;
	std::vector<SubTrie<T>*> attended_nodes {};

	T default_val{}; //����� ����������������
	std::pair<std::string, T&> iter_value{ "", default_val };
	char buf_symb{};

	void init_invalid(TrieIterator* it) {
		it->data = nullptr;
		it->search_str.clear();
		it->symbol = search_str.rend();
	}

	void add_attended(SubTrie<T>* data) {
		attended_nodes.push_back(data);
	}

	void init_iter_value() {
		iter_value.first = search_str;
		if (this->data != nullptr)
			iter_value.second = (this->data)->value;
		else
			iter_value.second = T{};
	}

	bool node_is_not_attended(SubTrie<T>* ptr) {
		if (ptr != nullptr) {
			if (std::find(attended_nodes.begin(), attended_nodes.end(), ptr) != attended_nodes.end()) {
				return false;
			}
			else {
				return true; //��, �������������, ���� ���� ��� � ������� ��� ����������
			}
			
		}
	}
};