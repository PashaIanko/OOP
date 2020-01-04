
#pragma once
#include "pch.h"
#include <utility>

template<typename T>
class Matrix;


namespace CalcFunctions {
	template<typename T>
	static void partial_sum(std::pair<size_t, size_t> from_to, Matrix<T>*result, Matrix<T>*right) {
		size_t from = from_to.first;
		size_t to = from_to.second;
		
		for (size_t i = from; i < to; i++) {
			std::vector<T>& cur_row_left = result->get_row(i);
			std::vector<T>& cur_row_right = right->get_row(i);
			
			for (size_t j = 0; j < cur_row_left.size(); j++) {
				cur_row_left[j] += cur_row_right[j];
			}
		}
	};
	
}