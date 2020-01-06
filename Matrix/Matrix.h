#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include "MultithreadCalculator.h"




template<typename T>
class Matrix {
public:
	Matrix() = default;
	Matrix(size_t width, size_t height);
	Matrix(const std::vector<std::vector<T>>& data);


	inline size_t get_width() const { return width; };
	inline size_t get_height() const { return height; };
	std::vector<T>& get_row(size_t idx);
	const std::vector<T>& get_row(size_t idx) const;
	const std::vector<T> get_column(size_t idx) const;
	inline std::vector<std::vector<T>>& get_data();
	inline const std::vector<std::vector<T>>& get_data() const;
	
	Matrix<T> operator+(const Matrix<T>&right);
	Matrix<T> multhread_sum(Matrix<T>* left, Matrix<T>* right, const size_t threads_numb);
	Matrix<T> multhread_multiply(const Matrix<T>* right, size_t threads_numb) const;

	T multhread_det(size_t threads_numb) const;

	bool operator==(const Matrix<T>& right) const;

private:
	size_t height = 0;
	size_t width = 0;
	std::vector<std::vector<T>> rows{};
	bool enable_multithread = false;
	Matrix<T> one_thread_sum(const Matrix<T>& right);
	bool check_eq_size(const std::vector<std::vector<T>>& rows) const;
	bool size_mismatch(const Matrix<T>& right) const;
};

template<typename T>
Matrix<T>::Matrix(size_t height_, size_t width_) : width(width_), height(height_) {
	try {
		rows.resize(height);
		for (size_t i = 0; i < rows.size(); ++i) {
			rows[i].resize(width);
		}
	}
	catch (...) {
		std::cout << "bad alloc";
	}
	
}

template<typename T>
Matrix<T>::Matrix(const std::vector<std::vector<T>>& rows_) {
	if (check_eq_size(rows_)) { /*�� ������ � ������ ����� �� ��������*/
		height = rows_.size();
		width = rows_.at(0).size();
		rows.resize(rows_.size());
		
		size_t counter = 0;
		for (auto it: rows_) {
			rows[counter].resize(it.size());
			rows[counter] = it;
			counter++;
		}
	}
	else {
		//throw ?
	}
}

template<typename T>
bool Matrix<T>::operator==(const Matrix<T>& right) const {
	if (size_mismatch(right)) {
		return false;
	}
	for (size_t i = 0; i < get_height(); i++)
	{
		bool if_eq = rows[i] == right.get_row(i);
		if (if_eq == false)
			return false;
	}
	return true;
}

template<typename T>
inline std::vector<T>& Matrix<T>::get_row(size_t idx) {
	if (idx < rows.size()) {
		return rows[idx];
	}
	else {
		//throw?
	}
}

template<typename T>
inline const std::vector<T>& Matrix<T>::get_row(size_t idx) const {
	if (idx < rows.size()) {
		return rows[idx];
	}
	else {
		//throw?
	}
}

template<typename T>
inline const std::vector<T> Matrix<T>::get_column(size_t idx) const {
	std::vector<T> result;
	size_t rows_size = rows.size();
	if (rows_size) {
		if (idx < rows.at(0).size()) {
			for (auto it : rows) {
				result.push_back(it[idx]);
			}
		}
	}
	return result;
}

template<typename T>
inline std::vector<std::vector<T>>& Matrix<T>::get_data() {
	return rows;
}

template<typename T>
inline const std::vector<std::vector<T>>& Matrix<T>::get_data() const {
	return rows;
}

template<typename T>
inline Matrix<T> Matrix<T>::operator+(const Matrix<T>& right) {
	if (enable_multithread == false) {
		return one_thread_sum(right);
	}
	
}

template<typename T>
inline Matrix<T> Matrix<T>::multhread_sum(Matrix<T>* left, Matrix<T>* right, const size_t threads_numb)
{
	if (size_mismatch(*right)) {
		return Matrix<T>();
	}
	else {
		MultithreadCalculator<T> adder(left, right, threads_numb);
		return adder.sum();
	}
	
}

template<typename T>
inline Matrix<T> Matrix<T>::multhread_multiply(const Matrix<T>* right, size_t threads_numb) const
{
	if (get_width() != right->get_height()) {
		return Matrix<T>();
	}
	else {
		MultithreadCalculator<T> multiplier(this, right, threads_numb);
		//return Matrix<T>();
		return multiplier.multiply();
	}
}

template<typename T>
inline T Matrix<T>::multhread_det(size_t threads_numb) const {
	if (width != height) {
		//throw?
		return T{};
	}
	MultithreadCalculator<T> calculator(this, threads_numb);
	return calculator.det(&CalcFunctions::partial_det);
	//size_t columns_per_thread = (size_t) (width / threads_numb); /*���������� �� ������� ������*/
	//if (columns_per_thread == 0) { /*������ ������ ���-�� �������*/
	//	columns_per_thread = 1;
	//}

	//if (threads_count == 1) return simple_det(mat);
	//if (threads_count > num_of_threads) threads_count = num_of_threads;
	//CalculationManager det_calculator(mat, threads_count);
	//return det_calculator.determinant();
}

template<typename T>
inline Matrix<T> Matrix<T>::one_thread_sum(const Matrix<T>& right) {
	
	if (size_mismatch(right)) {
		//throw()? ���� ������� �� ���������
		return Matrix<T>();
	}
	else {
		Matrix result(*this);
		size_t i = 0;
		for (auto row_rhs : right.rows) {
			std::vector<T>& row_lhs = result.get_row(i);
			/*summ_rows*/
			for (size_t j = 0; j < row_lhs.size(); j++) {
				row_lhs[j] += row_rhs[j];
			}
			i++;
		}
		return result;
	}
	
}

template<typename T>
inline bool Matrix<T>::check_eq_size(const std::vector<std::vector<T>>& rows) const {
	size_t rows_size = rows.size();
	if (rows_size) {
		for (size_t i = 0; i < rows_size; i++) {
			size_t prev_size = rows[i].size();
			if (i + 1 < rows_size) {
				if (prev_size != rows[i + 1].size()) {
					return false;
				}
			}
		}
	}
	return true;
}

template<typename T>
inline bool Matrix<T>::size_mismatch(const Matrix<T>& right) const
{
	return width != right.width || height != right.height;
}



