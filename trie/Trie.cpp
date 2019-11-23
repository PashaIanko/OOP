// Trie.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include "trie.h"
#include <vector>
#include <string>


int main()
{
	Trie<char>t;
	t.insert("abc", 1);
	/*t.insert("abgl", 0);
	t.insert("cdf", 0);
	t.insert("abcd", 0);*/
	

	std::vector<std::pair<std::string, float>> v{ {"abc", 1},{"abgl", 2},{"cdf", 3} };

	bool res = t.empty();

//	auto it = t.begin();

	Trie<float> t_(v.begin(), v.end());

}

