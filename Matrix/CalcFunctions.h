
#pragma once
#include "pch.h"
#include <utility>

template<typename T>
class Matrix;


namespace CalcFunctions {
	template<typename T>
	static void partial_sum(std::pair<size_t, size_t> from_to, Matrix<T>*result, const Matrix<T>*right) {
		size_t from = from_to.first;
		size_t to = from_to.second;
		
		for (size_t i = from; i < to; i++) {
			std::vector<T>& cur_row_left = result->get_row(i);
			const std::vector<T>& cur_row_right = right->get_row(i);
			
			for (size_t j = 0; j < cur_row_left.size(); j++) {
				cur_row_left[j] += cur_row_right[j];
			}
		}
	};

	template<typename T>
	static void partial_subtract(std::pair<size_t, size_t> from_to, Matrix<T>*result, const Matrix<T>*right) {
		size_t from = from_to.first;
		size_t to = from_to.second;

		for (size_t i = from; i < to; i++) {
			std::vector<T>& cur_row_left = result->get_row(i);
			const std::vector<T>& cur_row_right = right->get_row(i);

			for (size_t j = 0; j < cur_row_left.size(); j++) {
				cur_row_left[j] -= cur_row_right[j];
			}
		}
	};

	template<typename T>
	static void partial_mult(std::pair<size_t, size_t> from_to, Matrix<T>* res, const Matrix<T>* left_m, const Matrix<T>* right_m) {
		size_t from = from_to.first;
		size_t to = from_to.second;
		size_t right_width = right_m->get_width();

		//for (size_t i = from; i < to; i++) {
		//	const std::vector<T>& cur_row_left = left_m->get_row(i);
		//	/*строку на все столбцы правой перемножаем, поочерЄдно записыва€ в €чейки результат*/
		//	for (size_t j = 0; j < right_width; j++) {
		//		std::vector<T> cur_column_right = right_m->get_column(j);
		//		T res_val{};
		//		for (size_t k = 0; k < cur_row_left.size(); k++) {
		//			res_val += cur_row_left[k] * cur_column_right[k];
		//		}
		//		std::vector<std::vector<T>>& data = res->get_data();
		//		data[i][j] = res_val;
		//	}
		//}
		//return;
		size_t left_width = left_m->get_width();
		std::vector<std::vector<T>>& res_data = res->get_data();
		const std::vector<std::vector<T>>& r_matrix_data = right_m->get_data();
		for (size_t i = from; i < to; i++) {
			const std::vector<T>& cur_row_left = left_m->get_row(i);
			/*строку на все столбцы правой перемножаем, поочерЄдно записыва€ в €чейки результат*/
			for (size_t j = 0; j < right_width; j++) {
				//std::vector<T> cur_column_right = right_m->get_column(j);
				T res_val{};
				for (size_t k = 0; k < left_width/*cur_row_left.size()*/; k++) {
					res_val += cur_row_left[k] * r_matrix_data[k][j];
				}
				res_data[i][j] = res_val;
			}
		}
		return;
	};

	template<typename T>
	static T partial_det(std::pair<size_t, size_t> from_to, const Matrix<T>* matrix) {
		/*считает aij*Aij, Aij = (-1)^(i+j)*Mij*/
		/*разложение по нулевой строке*/
		size_t column_from = from_to.first;
		size_t column_to = from_to.second;
		T result{};
		const std::vector<std::vector<T>>& m_data = matrix->get_data();
		int init_sign = pow(-1, column_from);
		for (size_t j = column_from; j < column_to; j++) {
			T aij = m_data[0][j];
			result += /*pow(-1, j)*/init_sign*aij*CalcFunctions::minor(matrix, 0, j); /*ƒумал, возведение
																					  в степень довольно долго,
																					  может хоть так соптимизировать*/
			init_sign = -init_sign;
		}
		return result;
	};

	template<typename T>
	static T minor(const Matrix<T>* matrix, size_t line, size_t column) {
		Matrix<T> shorter_m = CalcFunctions::cut_matrix(matrix, line, column);
		return CalcFunctions::simple_det(&shorter_m);
	}

	template<typename T>
	Matrix<T> cut_matrix(const Matrix<T>* matrix, size_t line, size_t column) {
		Matrix<T> result(matrix->get_width() - 1, matrix->get_height() -1);

		const std::vector<std::vector<T>>& m_data = matrix->get_data();
		size_t height = matrix->get_height();
		size_t m_width = matrix->get_width();

		size_t result_rows_counter = 0;
		for (size_t i = 0; i < height; i++) {
			if (i != line) {
				std::vector<T>& result_data = result.get_row(result_rows_counter);
				std::vector<T> matrix_data = matrix->get_row(i);
				matrix_data.erase(matrix_data.begin() + column);
				std::copy(matrix_data.begin(), matrix_data.end(), result_data.begin());
				result_rows_counter++;
			}
		}
		return result;

	};

	template<typename T>
	T simple_det(const Matrix<T>* m) {
		T result{};
		size_t m_width = m->get_width();
		size_t m_height= m->get_height();
		if (m_width == m_height) {
			const std::vector<std::vector<T>>& m_data = m->get_data();
			if (m_width == 1) {
				return m_data[0][0];
			}
			if (m_width == 2) {
				return (m_data[0][0] * m_data[1][1] - m_data[0][1] * m_data[1][0]);
			}
			else {
				for (size_t j = 0; j < m_width; j++) {
					result += m_data[0][j] * pow(-1, /*i+j i=0*/j)*CalcFunctions::minor(m, 0, j);
				}
			}
		}
		return result;
	}
}