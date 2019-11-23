#pragma once
#include "trie_iterator.h"
#include "const_trie_iterator.h"
#include "Bad_search_exception.h"
#include "subtrie.h"
#include <map>
#include <string>
#include <iterator>
#include <utility>
#include <stdexcept>





template <class T = int>
class Trie {
public:

	typedef TrieIterator<T> iterator;
	typedef ConstTrieIterator<T> const_iterator;
	typedef T value_type;
	typedef std::string key_type;

	template<typename>
	friend class TestHelper;

	template<typename>
	friend class TrieIterator;

	template <typename>
	friend class SubTrie;

	Trie() : trie_size(0) { root = new SubTrie<T>; };


	template <class InputIterator>/*,
	std::enable_if_t<std::is_same<InputIterator::value, std::pair<key_type, value_type>>>> */
	Trie(InputIterator first, InputIterator last) {
		root = new SubTrie<T>;
		for (auto it = first; it != last; ++it) {
			std::pair<key_type, value_type> p{ *it };
			this->insert(p.first, p.second);
		}
	}

	Trie(const Trie<T> & trie) : trie_size(trie.trie_size) {
		root = new SubTrie<T>(*trie.root);
	};

	~Trie() = default;

	Trie<T> & operator= (const Trie<T> & trie) {
		if (this != &trie) {
			this->clear(); /*deep deleting each node, root remains!*/
			this->root->init(*(trie.root));
			trie_size = trie.trie_size;
		}
		return *this;
	};

	iterator begin() {
		/*returning iterator pointing to the node closest to the left side of tree*/
		SubTrie<T>* first_node = root;
		SubTrie<T>* node;
		std::string search_str;
		char symb;
		while (first_node->children.size()) {
			std::pair<char, SubTrie<T>*> pair = *(first_node->children.begin());

			node = pair.second;
			symb = pair.first;
			if (node->is_word_end()) {
				//char first_symb = pair.first;
				search_str += symb;
				//search_str(1, first_symb);
				return iterator(search_str, pair.second);
			}
			first_node = node;
			search_str += symb;
			
		}
		iterator it;
		return it;

		/*char symbol = NON_INITIALIZED;
		std::string search_str; //internal field of iterator
		while (first_node->children.size()) {
			symbol = ((first_node->children).cbegin())->first;
			search_str += symbol;
			first_node = ((first_node->children).cbegin())->second;
		}
		return iterator(search_str, first_node);*/
	};

	const_iterator cbegin() const {

	};

	iterator end() {
		/*returning iterator pointing to the node closest to the right side of tree*/
		
		/*previous realization*/
		/*SubTrie<T>* last_node = root;

		while (last_node->children.size()) {
			auto it = last_node->children.rbegin();
			last_node = it->second;
		}
		last_node += sizeof(SubTrie<T>);
		return iterator(last_node);*/
		iterator it;
		it.init_invalid(&it);
		return it;
	};
	const_iterator cend() const {
		return const_iterator();
	};

	bool empty() const;

	size_t size() const {
		return trie_size;
	};

	value_type& operator[] (const key_type& k) {
		SubTrie<T>* temp = root;
		for (auto letter : k) {
			auto it = temp->children.find(letter);
			if (it != temp->children.end()) {
				temp = it->second;
			}
			else {
				T val{};
				std::pair<TrieIterator<T>, bool> p = insert(k, val);
				return p.first.data->value; /*replicate std::map<> interface*/
			}
		}
		if (temp->is_end_of_word)
			return temp->value;
		else {
			std::invalid_argument exc("ab");
			throw exc;
		}
	};

	std::pair<iterator, bool> insert(const key_type& k, const value_type& val);

	template <class InputIterator> void
		insert(InputIterator first, InputIterator last) {
		for (auto it = first; it != last; ++it) {
			std::pair<key_type, value_type> p{ *it };
			this->insert(p.first, p.second);
		}
	};

	//удаление
	void erase(iterator position) {
		
	};



	size_t erase(const key_type& k) {

		/*deleting only if it is a full key (added work). if k is only part of the key
		it will not be deleted*/

		SubTrie<T>* temp = root;
		for (auto letter : k) {
			auto it = temp->children.find(letter);
			if (it != temp->children.end()) {
				temp = it->second;
			}
			else {
				return 0; /*the word is not found - why size_t in the interface?*/
			}
		}
		if (temp->is_end_of_word) {
			if (!temp->children.empty()) {
				temp->is_end_of_word = false;
			}
			else {
				//std::string::const_iterator key_it;
				for (auto c = k.crbegin(); c != k.crend(); ++c) {// (auto key_it = k.cbegin(); key_it != k.cend(); ++key_it) {
					temp = internal_delete(temp, *c);
					if (!temp || temp->is_end_of_word) { /*internal delete returns nullptr
							   when after deleting children map is not empty(can't
							   delete further)*/
						break;
					}
				}
			}
		}
		trie_size--;
		return trie_size;
	};
	void erase(iterator first, iterator last);

	void swap(Trie& trie) {
		size_t temp_size = trie.trie_size;
		trie.trie_size = this->trie_size;
		this->trie_size = temp_size;


		SubTrie<T>* tmp = trie.root;
		trie.root = this->root;
		this->root = tmp;
	};

	void clear() {
		root->clear();
		trie_size = 0;
	};

	//найти элемент
	iterator find(const key_type& k) {
		SubTrie<T>* temp = root;
		for (auto letter : k) {
			auto it_ = (temp->children).find(letter);
			if (it_ == temp->children.end()) {
				return end();
			}
			else {
				temp = it_->second;
			}
		}
		if (temp->is_end_of_word /*true - end_of_word*/) {
			return iterator(temp);
		}
		else {
			return end();
		}

	};

	SubTrie<T> GetSubTrie(const key_type & subKey) {
		SubTrie<T>* temp = root;
		for (auto letter : subKey) {
			auto it_ = temp->children.find(letter);
			if (it_ == temp->children.end()) {
				BadSearchException b(subKey);
				throw b;
			}
			else {
				temp = it_->second;
			}
		}
		//Previous: return SubTrie<T>::SubTrie(temp->parent, *temp);
		return *temp;

	};



private:
	SubTrie<T>* root;
	size_t trie_size;

	SubTrie<T>* internal_delete(SubTrie<T>* ptr, const char ch);
};



template<class T>
SubTrie<T>* Trie<T>::internal_delete(SubTrie<T>* st_ptr, const char ch) {
	SubTrie<T>* parent = st_ptr->parent;
	if (!(st_ptr->children.size())) {
		/*empty map*/
		delete st_ptr;
		auto found_it = (parent->children).find(ch);
		parent->children.erase(found_it);
		if (!parent->children.empty())
			return nullptr;
		else
			return parent;
	}
	else {
		/**/
		return nullptr;
	}

}



template<class T>
inline bool Trie<T>::empty() const /*empty if only root withour children*/ {
	return (!(root->children).size());
}

template<class T>
inline std::pair<TrieIterator<T>, bool> Trie<T>::insert(const key_type & k, const value_type & val)
{
	/*checking if key_type is present in the map*/
	iterator it = find(k);
	if (it != end()) {
		(it.data)->value = val;

		std::pair<TrieIterator<T>, bool> p; // (it, true);
		p.first = it;
		p.second = true;
		return p;
	}


	SubTrie<T>* temp = root;

	size_t index = 1; //index in key_type string
	size_t str_length = k.length();
	for (auto letter : k) {
		auto it_ = temp->children.find(letter);
		if (it_ == temp->children.end()) {
			SubTrie<T>* new_node;
			if (index == str_length)
				new_node = new SubTrie<T>(true, val, temp);
			else
				new_node = new SubTrie<T>(false, temp); /*if reached the end of the
																		  string, the node bool value must be true (indicates that
																		  the full word is added)*/
			std::pair<char, SubTrie<T>*> p(letter, new_node);
			temp->children.insert(p);
			temp = new_node;

		}
		else {
			temp = (it_)->second;
			if (index == str_length) {
				temp->value = val;
				temp->is_end_of_word = true;
				trie_size++;
				iterator it(temp);
				std::pair<TrieIterator<T>, bool> p{ it, true };
				return p;
			}

		}
		index++;
	}

	trie_size++;
	iterator it_(temp);
	std::pair<TrieIterator<T>, bool> p{ it_, true };
	return p;

	/*return std::pair<iterator, bool>();*/
}

