
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

	template<typename T>
	static void partial_mult(std::pair<size_t, size_t> from_to, Matrix<T>* res, Matrix<T>* left_m, Matrix<T>* right_m) {
		size_t from = from_to.first;
		size_t to = from_to.second;
		size_t right_width = right_m->get_width();

		for (size_t i = from; i < to; i++) {
			std::vector<T>& cur_row_left = left_m->get_row(i);
			/*строку на все столбцы правой перемножаем, поочерЄдно записыва€ в €чейки результат*/
			for (size_t j = 0; j < right_width; j++) {
				std::vector<T> cur_column_right = right_m->get_column(j);
				static_assert (cur_row_left.size() == cur_column_right.size());
				T res_val{};
				for (size_t k = 0; k < cur_row_left.size(); k++) {
					res_val += cur_row_left[k] * cur_column_right[k];
				}
				//result.get_data()[i][j]
				res->get_data()[i][j] = res_val;
			}
		}
		return;
	};
	
}