#include "pch.h"
#include "gtest\gtest.h"
#include "..\Trie\trie.h"
#include "..\Trie\subtrie.h"
#include "..\Trie\trie_iterator.h"
#include <list>

template<typename T>
class TestHelper {
	template<typename>
	friend class TrieIterator;

	template<typename>
	friend class SubTrie;

public:
	TestHelper() {};
	TestHelper(TrieIterator<T>* tr_it_) : tr_it(tr_it_){};
	TestHelper(Trie<T>* tr_) : trie(tr_) {};
	T get_iterator_value() { return tr_it->data.value; }

	bool play_insert_scenario(std::pair<std::string, T> p, T expect) {
		std::pair<TrieIterator<T>, bool> pair = trie->insert(p.first, p.second);
		return (pair.first).data->value == expect;
	};

	bool play_extract_scenario(const std::string & str, T expect) {
		T value = trie->operator[](str);
		return value == expect;
	}

private:
	TrieIterator<T>* tr_it;
	Trie<T>* trie;
};


/*class IteratorHelper {
	template<typename>
	friend class TrieIterator;

	IteratorHelper() = default;

	//template<typename T>
	//static bool compare(const TrieIterator<T> & it) {
	//	it->data->
	//};
};*/

TEST(CONSTRUCTOR, empty_constr_OK) {
	/*check if compiled*/
	
	Trie<int> t;

	Trie<double> t2;

	struct my_struct {
		int a;
		float f;
	};

	Trie<my_struct> t3;
}

TEST(CONSTRUCTOR, vector_pairs_OK) {
	std::vector<std::pair<std::string, float>> v{ {"abc", 1.2f},{"abgl", 2.2f},{"cdf", 3.2f} };
	Trie<float> t(v.begin(), v.end());
	
	EXPECT_FALSE(t.empty());
	//EXPECT_EQ(t.size(), 3);
}

TEST(CONSTRUCTOR, list_pairs_OK) {
	std::list<std::pair<std::string, float>> v{ {"abc", 1.1f},{"abgl", 2.1f},{"cdf", 3.1f} };
	Trie<float> t(v.begin(), v.end());

	EXPECT_FALSE(t.empty());
	//EXPECT_EQ(t.size(), 3);
}

TEST(OPERATOR_EXTRACT, insert_one_elem) {
	Trie<int> t;
	t.insert("abc", 1);
	EXPECT_EQ(t.operator[]("abc"), 1);
}

TEST(OPERATOR_EXTRACT, finding_with_the_wrong_key) {
	/*like in std::map, expect insertion of new element where value is
	defaul (val{}) and returning a reference to the value of the inserted node*/

	Trie<int> t;
	t.insert("abc", 1);
	TestHelper<int> h(&t);
	EXPECT_TRUE(h.play_extract_scenario("def", 0));
}

TEST(OPERATOR_EXTRACT, insert_two_elem) {
	Trie<int> t;
	t.insert("abc", 1);
	t.insert("flg", 35);
	EXPECT_EQ(t.operator[]("flg"), 35);
}

TEST(OPERATOR_EXTRACT, insert_three_elem) {
	Trie<float> t;
	t.insert("abc", 1.1f);
	t.insert("flg", 1.23f);
	t.insert("flgd", 1.1f);
	EXPECT_FLOAT_EQ(t.operator[]("flg"), 1.23f);
	EXPECT_FLOAT_EQ(t.operator[]("abc"), 1.1f);
	EXPECT_FLOAT_EQ(t.operator[]("flgd"), 1.1f);
}

TEST(OPERATOR_EXTRACT, wrong_key) {
	Trie<> t;
	t.insert("abc", 1);
	TestHelper <int> h(&t);
	EXPECT_TRUE(h.play_extract_scenario("flg", 0));
}

TEST(OPERATOR_EXTRACT, wrong_key_no_throw) {
	Trie<> t;
	t.insert("abc", 1);
	EXPECT_NO_THROW(t["flg"] = 5);
}

TEST(OPERATOR_EXTRACT, correct_key_no_throw) {
	Trie<> t;
	t.insert("abc", 1);
	int val = 0;
	EXPECT_NO_THROW(val = t["abc"]);
}

TEST(OPERATOR_EXTRACT, part_of_key_but_not_key_itself) {
	Trie<> t;
	t.insert("abc", 1);
	int val = t["ab"];
	int default_int{};
	EXPECT_NO_THROW(t["ab"]);
	EXPECT_EQ(val, default_int);
}

TEST(SIZE, one_element) {
	Trie<float> t;
	t.insert("abc", 1.1f);
	EXPECT_EQ(t.size(), 1);
}

TEST(SIZE, empty_trie) {
	Trie<>t;
	EXPECT_EQ(t.size(), 0);
}

TEST(SIZE, adding_two_elements) {
	Trie<>t;
	t.insert("abc", 1);
	t.insert("abcd", 1);
	EXPECT_EQ(t.size(), 2);
}

TEST(INSERT, insert_two_times_same_key_OK) {
	Trie<> t;
	t.insert("abc", 1);
	t.insert("abc", 2);
	EXPECT_EQ(t.operator[]("abc"), 2);
	EXPECT_EQ(t.size(), 1);

}

TEST(INSERT, correct_iterator_return) {
	Trie<>t;
	TestHelper<int> th(&t);
	std::pair<std::string, int> p{ "a", 1 };
	bool res = th.play_insert_scenario(p, 1); /**/
	EXPECT_TRUE(res);
}

TEST(INSERT, multiple_insertions_correct_iterator_return) {
	Trie<>t;
	TestHelper<int> th(&t);
	std::pair<std::string, int> p{ "a", 1 };
	
	EXPECT_TRUE(th.play_insert_scenario(p, 1));
	EXPECT_TRUE(th.play_insert_scenario({"b", 2}, 2));
	EXPECT_TRUE(th.play_insert_scenario({ "ab", 3 }, 3));
	EXPECT_TRUE(th.play_insert_scenario({ "defg", 4 }, 4));

}


TEST(INSERT, insert_two_values_same_key_OK) {
	Trie<> t;
	t.insert("abc", 1);
	t.insert("abc", 2);
	EXPECT_EQ(t.operator[]("abc"), 2);
	EXPECT_EQ(t.size(), 1);
}

TEST(INSERT, insert_different_values_at_same_keys_OK) {
	Trie<> t;
	t.insert("abc", 1);
	t.insert("abc", 2);
	t.insert("qwerty", 2);
	t.insert("nsu", 5);
	t.insert("qwerty", 45);
	t.insert("abc", -3);
	t.insert("qwert", 1);
	EXPECT_EQ(t.operator[]("abc"), -3) << "t [abc] = " << t["abc"] <<std::endl;
	EXPECT_EQ(t["qwerty"], 45) << t["qwerty"];
	EXPECT_EQ(t["nsu"], 5) << t["nsu"];
	EXPECT_EQ(t["qwert"], 1) << t["qwert"];
	EXPECT_EQ(t.size(), 4);
}

TEST(INSERT, parts_of_word_as_the_keys) {
	Trie<> t;
	t.insert("abcd", 1);
	t.insert("abc", 2);
	t.insert("ab", 3);
	t.insert("a", 4);
	EXPECT_EQ(t.operator[]("abcd"), 1);
	EXPECT_EQ(t.operator[]("abc"), 2);
	EXPECT_EQ(t.operator[]("ab"), 3);
	EXPECT_EQ(t.operator[]("a"), 4);
	EXPECT_EQ(t.size(), 4);
}

TEST(COPY_CONSTRUCTOR, empty_trie) {
	Trie<> t;
	Trie<> t_(t);
	EXPECT_TRUE(t.size() == t_.size() && t_.size() == 0);
	/*EXPECT_TRUE(t==t_)*/
}

TEST(COPY_CONSTRUCTOR, one_element_trie) {
	Trie<> t;
	t.insert("a", 1);
	Trie<> t_(t);
	EXPECT_TRUE(t.size() == t_.size() && t_.size() == 1);
	EXPECT_TRUE(
		t["a"] == 1 
	&& t_["a"] == 1);
	/*EXPECT_TRUE(t==t_)*/
}

TEST(COPY_CONSTRUCTOR, two_letters_trie) {
	Trie<> t;
	t.insert("ab", 1);
	Trie<> t_(t);
	EXPECT_TRUE(t.size() == t_.size() && t_.size() == 1);
	EXPECT_TRUE(
		t["ab"] == 1
		&& t_["ab"] == 1);
	/*EXPECT_TRUE(t==t_)*/
}

TEST(COPY_CONSTRUCTOR, many_different_keys) {
	Trie<> t;
	t.insert("abcd", 1);
	t.insert("abc", 2);
	t.insert("ab", 3);
	t.insert("a", 4);

	Trie<> t_(t);
	EXPECT_EQ(t.operator[]("abcd"), 1);
	EXPECT_EQ(t.operator[]("abc"), 2);
	EXPECT_EQ(t.operator[]("ab"), 3);
	EXPECT_EQ(t.operator[]("a"), 4);
	EXPECT_EQ(t.size(), 4);
	EXPECT_EQ(t_.operator[]("abcd"), 1);
	EXPECT_EQ(t_.operator[]("abc"), 2);
	EXPECT_EQ(t_.operator[]("ab"), 3);
	EXPECT_EQ(t_.operator[]("a"), 4);
	EXPECT_EQ(t_.size(), 4);
}

TEST(GET_SUBTRIE, empty_incorrect_key_OK) {
	/*expct defaul empty subtrie*/
	Trie<>t;
	EXPECT_THROW(t.GetSubTrie("a"), BadSearchException);
}

TEST(GET_SUBTRIE, one_letter_key_OK) {
	Trie<>t;
	t.insert("a", 1);
	EXPECT_NO_THROW(t.GetSubTrie("a"));

}

TEST(GET_SUBTRIE, two_letter_key_finding_key_OK) {
	Trie<>t;
	t.insert("ab", 1);
	EXPECT_NO_THROW(t.GetSubTrie("ab"));
}

TEST(GET_SUBTRIE, two_letter_key_but_finding_with_the_first_letter_OK) {
	/*key - ab*/
	Trie<>t;
	t.insert("ab", 1);
	EXPECT_NO_THROW(t.GetSubTrie("a")); /*expect empty subtrie, because the word "a" is not present*/

}

TEST(GET_SUBTRIE, two_letter_key_but_finding_with_the_right_key) {
	/*key - ab*/
	Trie<>t;
	t.insert("ab", 1);
	EXPECT_NO_THROW(t.GetSubTrie("ab")); /*expect non-empty subtrie, because the word "ab" not present*/

}

TEST(GET_SUBTRIE, cascade_keys) {
	Trie<>t;
	t.insert("a", 1);
	t.insert("ab", 2);
	t.insert("abc", 3);
	EXPECT_NO_THROW(t.GetSubTrie("a"));
}

TEST(GET_SUBTRIE, finding_the_wrong_key) {
	Trie<>t;
	t.insert("abc", 3);
	EXPECT_THROW(t.GetSubTrie("fg"), BadSearchException);
}

TEST(ERASE_KEY, two_keys_erase_prev_key_OK) {
	Trie<>t;
	t.insert("abc", 3);
	t.insert("abcd", 4);
	EXPECT_EQ(t.size(), 2);
	std::string str("abc");
	/*size_t val =*/ t.erase(str);
	EXPECT_EQ(t.size(), 1);
	auto it = t.find(str);
	EXPECT_EQ(it, t.end());
}

TEST(ERASE_KEY, three_keys_erase_two_prev_keys_OK) {
	Trie<>t;
	t.insert("abc", 3);
	t.insert("abcd", 4);
	t.insert("abcde", 4);

	std::string str("abc");
	std::string str_("abcd");
	size_t val = t.erase(str);
	val = t.erase(str_);
	EXPECT_EQ(t.find(str), t.end());
	EXPECT_EQ(t.find(str_), t.end());
	EXPECT_NE(t.find("abcde"), t.end());
}

TEST(ERASE_KEY, delete_nodes_scenario) {
	Trie<>t;
	t.insert("abc", 3);
	t.insert("abge", 4);

	std::string str("abge");
	/*size_t val = */t.erase(str);
	EXPECT_EQ(t.find(str), t.end());
	EXPECT_NE(t.find("abc"), t.end());
	EXPECT_FALSE(t.empty());
	EXPECT_EQ(t.size(), 1);
}

TEST(ERASE_KEY, single_key_map_erase) {
	/*Expect root remains intact as the head of the structure*/
	Trie<>t;
	t.insert("abcd", 2);
	std::string str("abcd");
	/*size_t val = */t.erase(str);
	EXPECT_EQ(t.find(str), t.end());
	EXPECT_TRUE(t.empty());
	EXPECT_EQ(t.size(), 0);
}

TEST(ERASE_KEY, two_keys_one_prefix_t_another) {
	
	Trie<>t;
	t.insert("b", 2);
	t.insert("bc", 2);
	std::string bc("bc");
	std::string b("b");
	EXPECT_EQ(t.size(), 2);
	/*size_t val = */t.erase("bc");
	EXPECT_EQ(t.find("bc"), t.end());
	EXPECT_FALSE(t.empty());
	EXPECT_EQ(t.size(), 1);
	EXPECT_NE(t.find(b), t.end());
}

TEST(OPERATOR_EQ, empty_trie) {
	Trie<> t;
	t = t;
	EXPECT_TRUE(!t.size()); /*TEST!!*/
}

TEST(OPERATOR_EQ, one_node_trie) {
	Trie<> t, t_;
	t.insert("a", 5);
	t_ = t;
	EXPECT_EQ(t.size(), 1); 
	EXPECT_EQ(t.size(), t_.size());
	EXPECT_EQ(t["a"], 5);
	EXPECT_EQ(t["a"], t_["a"]);
}

TEST(OPERATOR_EQ, cascade_nodes) {
	Trie<> t, t_;
	t.insert("a", 5);
	t.insert("ab", 6);
	t.insert("abc", 7);

	t_ = t;
	EXPECT_EQ(t.size(), 3);
	EXPECT_EQ(t.size(), t_.size());
	
	
	EXPECT_TRUE(t["ab"] == t_["ab"] && t_["ab"] == 6);
	EXPECT_TRUE(t["abc"] == t_["abc"] && t_["abc"] == 7);
	EXPECT_TRUE(t["a"] == t_["a"] && t["a"] == 5);
}

TEST(OPERATOR_EQ, tree_like_structure_nodes) {
	Trie<> t;
	Trie<> t_;
	t.insert("ac", 5);
	t.insert("ab", 6);
	t.insert("bd", 7);
	t.insert("bf", 8);

	t_ = t;
	EXPECT_EQ(t.size(), 4);
	EXPECT_EQ(t.size(), t_.size());


	EXPECT_TRUE(t["ab"] == t_["ab"] && t_["ab"] == 6);
	EXPECT_TRUE(t["ac"] == t_["ac"] && t_["ac"] == 5);
	EXPECT_TRUE(t["bd"] == t_["bd"] && t_["bd"] == 7);
	EXPECT_TRUE(t["bf"] == t_["bf"] && t["bf"] == 8);
}

TEST(CLEAR, empty_trie) {
	Trie<> t;
	t.clear();
	EXPECT_TRUE(t.empty());
}

TEST(CLEAR, root_plus_one_node_trie) {
	Trie<>t;
	t.insert("a", 1);
	EXPECT_FALSE(t.empty());
	t.clear();
	EXPECT_TRUE(t.empty());
}

TEST(CLEAR, three_attached_nodes) {
	Trie<>t;
	t.insert("a", 1);
	t.insert("b", 2);
	t.insert("c", 3);
	EXPECT_FALSE(t.empty());
	t.clear();
	EXPECT_TRUE(t.empty());
}

TEST(CLEAR, cascade_nodes) {
	Trie<>t;
	t.insert("a", 1);
	t.insert("ab", 2);
	t.insert("abc", 3);
	EXPECT_FALSE(t.empty());
	t.clear();
	EXPECT_TRUE(t.empty());
}

TEST(CLEAR, tree_like_structure) {
	Trie<>t;
	t.insert("a", 1);
	t.insert("ab", 2);
	t.insert("ac", 3);

	t.insert("b", 4);
	t.insert("bd", 5);
	t.insert("bf", 6);
	EXPECT_FALSE(t.empty());
	t.clear();
	EXPECT_TRUE(t.empty());
}

TEST(ITERATOR, one_elem_trie_cycle) {
	Trie<> t;
	t.insert("a", 1);
	size_t count = 0;
	for (Trie<int>::iterator it = t.begin(); it != t.end(); ++it) {
		std::pair<std::string, int> i = *it;
		EXPECT_EQ(i.second, 1);
		count++;
	}
	EXPECT_EQ(count, 1);
}

TEST(ITERATOR, two_elems_trie_cycle) {
	Trie<> t;
	t.insert("a", 1);
	t.insert("b", 2);

	//int i = 0;
	int count = 1;
	for (auto it = t.begin(); it != t.end(); ++it) {
		std::pair<std::string, int> i = *it;
		EXPECT_EQ(i.second, count);
		++count;
	}
	EXPECT_EQ(count, 3);
}

TEST(ITERATOR, three_elems_trie_cycle) {
	Trie<> t;
	t.insert("a", 1);
	t.insert("b", 2);
	t.insert("c", 3);

	//int i = 0;
	int count = 1;
	for (Trie<int>::iterator it = t.begin(); it != t.end(); ++it) {
		std::pair<std::string, int> i = *it;
		EXPECT_EQ(i.second, count);
		++count;
	}
	EXPECT_EQ(count, 4);
}

TEST(ITERATOR, iterate_over_two_letter_word) {
	Trie<> t;
	t.insert("a", 1);
	t.insert("ab", 2);

//	int i = 0;
	int count = 1;
	for (Trie<int>::iterator it = t.begin(); it != t.end(); ++it) {
		std::pair<std::string, int> i = *it;
		EXPECT_EQ(i.second, count);
		++count;
	}
	EXPECT_EQ(count, 3);
}

TEST(ITERATOR, long_word_one_key) {
	Trie<> t;
	t.insert("abcdefghti", 1);
	
//	int i = 0;
	int count = 1;
	for (auto it = t.begin(); it != t.end(); ++it) {
		std::pair<std::string, int> i = *it;
		EXPECT_EQ(i.second, count);
		++count;
	}
	EXPECT_EQ(count, 2);
}

TEST(ITERATOR, tree_like_structure) {
	Trie<> t;
	t.insert("a", 1);
	t.insert("bc", 2);
	t.insert("bd", 3);

	//int i = 0;
	int count = 1;
	for (auto it = t.begin(); it != t.end(); ++it) {
		std::pair<std::string, int> i = *it;
		EXPECT_EQ(i.second, count);
		++count;
	}
	EXPECT_EQ(count, 4);
}

TEST(ITERATOR, wide_tree_structure) {
	Trie<> t;
	t.insert("abd", 1);
	t.insert("abe", 2);
	t.insert("acf", 3);
	t.insert("acg", 4);

//	int i = 0;
	int count = 1;
	for (auto it = t.begin(); it != t.end(); ++it) {
		std::pair<std::string, int> i = *it;
		EXPECT_EQ(i.second, count);
		++count;
	}
	EXPECT_EQ(count, 5);
}

TEST(ITERATOR, three_nodes_broadcast_tree_structure) {
	Trie<> t;
	t.insert("abe", 1);
	t.insert("abf", 2);
	t.insert("abg", 3);
	t.insert("ach", 4);
	t.insert("aci", 5);
	t.insert("acj", 6);
	t.insert("adk", 7);
	t.insert("adl", 8);
	t.insert("adm", 9);

//	int i = 0;
	int count = 1;
	for (auto it = t.begin(); it != t.end(); ++it) {
		std::pair<std::string, int> i = *it;
		EXPECT_EQ(i.second, count);
		++count;
	}
	EXPECT_EQ(count, 10);
}

TEST(ITERATOR, three_nodes_broadcast_tree_structure_) {
	Trie<> t;
	t.insert("abe", 1);
	t.insert("abf", 2);
	t.insert("abg", 3);
	t.insert("ach", 4);
	t.insert("aci", 5);
	t.insert("acj", 6);
	t.insert("adk", 7);
	t.insert("adl", 8);
	t.insert("adm", 9);

	t.insert("bbe", 10);
	t.insert("bbf", 11);
	t.insert("bbg", 12);
	t.insert("bch", 13);
	t.insert("bci", 14);
	t.insert("bcj", 15);
	t.insert("bdk", 16);
	t.insert("bdl", 17);
	t.insert("bdm", 18);

//	int i = 0;
	int count = 1;
	for (auto it = t.begin(); it != t.end(); ++it) {
		std::pair<std::string, int> i = *it;
		EXPECT_EQ(i.second, count);
		++count;
	}
	EXPECT_EQ(count, 19);
}

TEST(ITERATOR, two_long_words) {
	Trie<> t;
	t.insert("First", 1);
	t.insert("Second", 2);
//	int i = 0;
	int count = 1;
	for (auto it = t.begin(); it != t.end(); ++it) {
		std::pair<std::string, int> i = *it;
		EXPECT_EQ(i.second, count);
		++count;
	}
	EXPECT_EQ(count, 3);
}

TEST(ITERATOR, many_long_words) {
	Trie<> t;
	t.insert("Airst", 1);
	t.insert("Becond", 2);
	t.insert("Chird", 3);
	t.insert("Dhird", 4);
	t.insert("Ehird", 5);
	t.insert("Fhird", 6);
//	int i = 0;
	int count = 1;
	for (auto it = t.begin(); it != t.end(); ++it) {
		std::pair<std::string, int> i = *it;
		EXPECT_EQ(i.second, count);
		++count;
	}
	EXPECT_EQ(count, 7);
}

TEST(ITERATOR, combo_broadcast_long_words) {
	Trie<> t;
	t.insert("aa", 1);
	t.insert("ab", 2);
	t.insert("ac", 3);
	t.insert("ad", 4);

	t.insert("blong", 5);

	t.insert("ca", 6);
	t.insert("cb", 7);
	t.insert("cc", 8);
//	int i = 0;
	int count = 1;
	for (auto it = t.begin(); it != t.end(); ++it) {
		std::pair<std::string, int> i = *it;
		EXPECT_EQ(i.second, count);
		++count;
	}
	EXPECT_EQ(count, 9);
}

TEST(ITERATOR, long_word_prefix_keys) {
	Trie<> t;
	
	t.insert("long word", 3);
	t.insert("long w", 2);
	t.insert("lo", 1);
	
	
	//int i = 0;
	int count = 1;
	for (auto it = t.begin(); it != t.end(); ++it) {
		std::pair<std::string, int> i = *it;
		EXPECT_EQ(i.second, count);
		++count;
	}
	EXPECT_EQ(count, 4);
}


TEST(ITERATOR, three_long_word_prefix_keys) {
	Trie<> t;

	t.insert("long word", 3);
	t.insert("long w", 2);
	t.insert("lo", 1);

	t.insert("new", 4);
	t.insert("new long", 5);
	t.insert("new long word", 6);


//	int i = 0;
	int count = 1;
	for (auto it = t.begin(); it != t.end(); ++it) {
		std::pair<std::string, int> i = *it;
		EXPECT_EQ(i.second, count);
		++count;
	}
	EXPECT_EQ(count, 7);
}

TEST(ITERATOR, three_long_word_prefix_keys_2) {
	Trie<> t;

	t.insert("long word", 3);
	t.insert("long w", 2);
	t.insert("lo", 1);

	t.insert("n", 4);
	t.insert("n l", 5);
	t.insert("n l w", 6);


//	int i = 0;
	int count = 1;
	for (auto it = t.begin(); it != t.end(); ++it) {
		std::pair<std::string, int> i = *it;
		EXPECT_EQ(i.second, count);
		++count;
	}
	EXPECT_EQ(count, 7);
}

TEST(ITERATOR, combo_broadcast_many_long_words) {
	Trie<> t;
	t.insert("aa", 1);
	t.insert("ab", 2);
	t.insert("ac", 3);
	t.insert("ad", 4);

	t.insert("blong", 5);

	t.insert("dlongword with spaces", 9);

	t.insert("ca", 6);
	t.insert("cb", 7);
	t.insert("cc", 8);
//	int i = 0;
	int count = 1;
	for (auto it = t.begin(); it != t.end(); ++it) {
		std::pair<std::string, int> i = *it;
		EXPECT_EQ(i.second, count);
		++count;
	}
	EXPECT_EQ(count, 10);
}

TEST(POSTFIX_INCREMENT, invalid_after_increment) {
	Trie<>t;
	t.insert("a", 1);
	auto it = t.begin();
	std::pair<std::string, int> i = *it++;
	EXPECT_EQ(i.second, 1);
	//int i = *it++;
	//EXPECT_EQ(i, 1);
	EXPECT_TRUE(it == t.end());
}

TEST(POSTFIX_INCREMENT, two_letter_word) {
	Trie<>t;
	t.insert("a", 1);
	t.insert("ab", 2);
	auto it = t.begin();
	//int i = *it++;
	std::pair<std::string, int> i = *it++;
	EXPECT_EQ(i.second, 1);

	//EXPECT_EQ(i, 2);
	i = *it++;
	EXPECT_EQ(i.second, 2);
	EXPECT_TRUE(it == t.end());
}

TEST(POSTFIX_INCREMENT, combo_broadcast_many_long_words_cycle) {
	Trie<> t;
	t.insert("aa", 1);
	t.insert("ab", 2);
	t.insert("ac", 3);
	t.insert("ad", 4);

	t.insert("blong", 5);

	t.insert("dlongword with spaces", 9);

	t.insert("ca", 6);
	t.insert("cb", 7);
	t.insert("cc", 8);
//	int i = 0;
	int count = 1;
	for (auto it = t.begin(); it != t.end();) {
		std::pair<std::string, int> i = *it++;
		EXPECT_EQ(i.second, count);
		++count;
	}
	EXPECT_EQ(count, 10);
}

TEST(POSTFIX_INCREMENT, long_word_prefix_keys_cycle) {
	Trie<> t;

	t.insert("long word", 3);
	t.insert("long w", 2);
	t.insert("lo", 1);


//	int i = 0;
	int count = 1;
	for (auto it = t.begin(); it != t.end();) {
		std::pair<std::string, int> i = *it++;
		EXPECT_EQ(i.second, count);
		++count;
	}
	EXPECT_EQ(count, 4);
}

TEST(POSTFIX_INCREMENT, three_long_word_prefix_keys_cycle) {
	Trie<> t;

	t.insert("long word", 3);
	t.insert("long w", 2);
	t.insert("lo", 1);

	t.insert("new", 4);
	t.insert("new long", 5);
	t.insert("new long word", 6);


//	int i = 0;
	int count = 1;
	for (auto it = t.begin(); it != t.end();) {
		std::pair<std::string, int> i = *it++;
		EXPECT_EQ(i.second, count);
		++count;
	}
	EXPECT_EQ(count, 7);
}

TEST(POSTFIX_INCREMENT, three_long_word_prefix_keys) {
	Trie<> t;

	t.insert("a", 1);
	t.insert("aa", 2);
	t.insert("aaa", 3);
	t.insert("b", 4);
	t.insert("bb", 5);
	t.insert("bbb", 6);


//	int i = 0;
	int count = 1;
	for (auto it = t.begin(); it != t.end();) {
		std::pair<std::string, int> i = *it++;
		EXPECT_EQ(i.second, count);
		++count;
	}
	EXPECT_EQ(count, 7);
}

TEST(POSTFIX_INCREMENT, three_long_word_prefix_keys_2_cycle) {
	Trie<> t;

	t.insert("long word", 3);
	t.insert("long w", 2);
	t.insert("lo", 1);

	t.insert("n", 4);
	t.insert("n l", 5);
	t.insert("n l w", 6);


//	int i = 0;
	int count = 1;
	for (auto it = t.begin(); it != t.end();) {
		std::pair<std::string, int> i = *it++;
		EXPECT_EQ(i.second, count);
		++count;
	}
	EXPECT_EQ(count, 7);
}

TEST(POSTFIX_INCREMENT, try_to_acess_invalid) {
	Trie<>t;
	t.insert("a",1);
	auto it = t.begin();
	std::pair<std::string, int> i = *++it;
	EXPECT_TRUE(i.first == "" && i.second == 0);
}

TEST(POSTFIX_INCREMENT, two_letters_word) {
	Trie<>t;
	t.insert("a", 1);
	t.insert("ab", 2);
	auto it = t.begin();
	std::pair<std::string, int> i = *it++;
	EXPECT_EQ(i.second, 1);
	EXPECT_TRUE(it != t.end());
}

TEST(PREFIX_INCREMENT, two_letters_word) {
	Trie<>t;
	t.insert("a", 1);
	t.insert("ab", 2);
	auto it = t.begin();
	std::pair<std::string, int> i = *++it;
	EXPECT_EQ(i.second, 2);
	EXPECT_TRUE(it != t.end());
}

TEST(POSTFIX_INCREMENT, shallow_tree) {
	Trie<>t;
	t.insert("a", 1);
	t.insert("b", 2);
	t.insert("d", 3);
	t.insert("e", 4);

	int count = 2;
	for (auto it = t.begin(); ++it != t.end(); count++) {
		std::pair<std::string, int> i = *it;
		EXPECT_EQ(i.second, count);
	}
	EXPECT_EQ(count, 5);
}

TEST(ERASE_AT_ITERATOR, erase_at_begin) {
	Trie<>t;
	t.insert("a", 1);
	t.insert("b", 2);
	t.insert("c", 3);

	t.erase(t.begin());
	EXPECT_EQ(t.size(), 2);

	EXPECT_EQ(t.find("a"), t.end());
	EXPECT_NE(t.find("b"), t.end());
	EXPECT_NE(t.find("c"), t.end());

}

TEST(ERASE_AT_ITERATOR, erase_at_end) {
	Trie<>t;
	t.insert("a", 1);
	t.insert("b", 2);
	t.insert("c", 3);

	t.erase(t.end());
	EXPECT_EQ(t.size(), 3);

	EXPECT_NE(t.find("a"), t.end());
	EXPECT_NE(t.find("b"), t.end());
	EXPECT_NE(t.find("c"), t.end());

}

TEST(ERASE_AT_ITERATOR, prefix_as_a_key) {
	Trie<>t;
	t.insert("abc", 2);
	t.insert("ab", 1);
	
	EXPECT_EQ(t.size(), 2);
	t.erase(t.begin());
	
	EXPECT_EQ(t.size(), 1);
	EXPECT_EQ(t.find("ab"), t.end());
	EXPECT_NE(t.find("abc"), t.end());

	auto it = t.find("abc");
	std::pair<std::string, int> p = *it;
	EXPECT_TRUE(p.first == "abc" && p.second == 2);
}

TEST(ERASE_AT_ITERATOR, full_erase) {
	Trie<>t;
	t.insert("a", 1);
	t.insert("aa", 2);
	t.insert("aaa", 3);
	t.insert("b", 4);
	t.insert("bb", 5);
	t.insert("bbb", 6);
	

	EXPECT_EQ(t.size(), 6);
	t.erase(t.begin(), t.end());
	EXPECT_EQ(t.size(), 0);
	EXPECT_TRUE(t.empty());

	EXPECT_EQ(t.find("a"), t.end());
	EXPECT_EQ(t.find("aa"), t.end());
}

TEST(ERASE_AT_ITERATOR, copy_constructor_erase_in_one_trie) {
	Trie<>t;
	t.insert("a", 1);
	t.insert("aa", 2);
	
	Trie<> t_ = t;

	t.erase(t.begin());
	
	EXPECT_EQ(t.size(), 1);
	EXPECT_EQ(t_.size(), 2);

	std::pair<std::string, int> p = *(t.find("aa"));
	EXPECT_TRUE(p.first == "aa" && p.second == 2); 
	EXPECT_EQ(t.find("a"), t.end());

	p = *(t_.find("a"));
	EXPECT_TRUE(p.first == "a" && p.second == 1);
	p = *(t_.find("aa"));
	EXPECT_TRUE(p.first == "aa" && p.second == 2);
}

TEST(ERASE_AT_ITERATOR, postfix_inc_erase) {
	Trie<>t;
	t.insert("a", 1);
	t.insert("aa", 2);

	t.erase(t.begin()++);

	EXPECT_EQ(t.size(), 1);
	
	std::pair<std::string, int> p = *(t.find("aa"));
	EXPECT_TRUE(p.first == "aa" && p.second == 2);
	EXPECT_EQ(t.find("a"), t.end());
}

TEST(ERASE_AT_ITERATOR, pretfix_inc_erase) {
	Trie<>t;
	t.insert("a", 1);
	t.insert("aa", 2);

	t.erase(++t.begin());

	EXPECT_EQ(t.size(), 1);

	std::pair<std::string, int> p = *(t.find("a"));
	EXPECT_TRUE(p.first == "a" && p.second == 1);
	EXPECT_EQ(t.find("aa"), t.end());
}

TEST(ERASE_FROM_TO, one_element_trie) {
	Trie<>t;
	t.insert("a", 1);
	
	t.erase(t.begin(), t.end());

	EXPECT_EQ(t.size(), 0);
	EXPECT_TRUE(t.empty());

	EXPECT_EQ(t.find("a"), t.end());
}

TEST(ERASE_FROM_TO, erase_all) {
	Trie<>t;
	t.insert("a", 1);
	t.insert("ab", 2);
	t.insert("b", 3);

	t.erase(t.begin(), t.end());

	EXPECT_EQ(t.size(), 0);
	EXPECT_TRUE(t.empty());

	EXPECT_EQ(t.find("a"), t.end());
	EXPECT_EQ(t.find("ab"), t.end());
	EXPECT_EQ(t.find("b"), t.end());
}

TEST(ERASE_FROM_TO, iterator_refresh_check) {
	Trie<>t;
	t.insert("a", 1);
	t.insert("ab", 2);
	t.insert("b", 3);

	t.erase(t.begin(), ++(++t.begin()));

	EXPECT_EQ(t.size(), 1);
	EXPECT_FALSE(t.empty());

	EXPECT_EQ(t.find("a"), t.end());
	EXPECT_EQ(t.find("ab"), t.end());
	EXPECT_NE(t.find("b"), t.end());
}

TEST(ERASE_AT_ITERATOR, repeated_erase) {
	Trie<>t;
	t.insert("a", 1);
	t.insert("ab", 2);
	t.insert("abc", 3);

	t.insert("b", 4);
	t.insert("bc", 5);

	t.erase(t.begin(), ++t.begin());

	EXPECT_EQ(t.size(), 4);
	EXPECT_EQ(t.find("a"), t.end());

	t.erase(t.begin(), ++(++t.begin()));
	EXPECT_EQ(t.size(), 2);
	EXPECT_EQ(t.find("ab"), t.end());
	EXPECT_EQ(t.find("abc"), t.end());
	
	EXPECT_NE(t.find("bc"), t.end());
	EXPECT_NE(t.find("b"), t.end());
}


int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	getchar();
	return 0;
}