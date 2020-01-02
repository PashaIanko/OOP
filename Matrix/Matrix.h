#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
//#include "MultithreadCalculator.h"

/*template <typename T>
class MultithreadCalculator {
public:
	MultithreadCalculator(const Matrix<T>& left, const Matrix<T>& right, size_t threads_numb);

private:
	const Matrix<T>& left;
	const Matrix<T>& right;
};

template<typename T>
MultithreadCalculator<T>::MultithreadCalculator(const Matrix<T>& left_, const Matrix<T>& right_, size_t threads_numb) :
	left(left_), right(right_)
{
	int v = 5;
}*/


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
	Matrix<T> operator+(const Matrix<T>&right);

	Matrix<T> multhread_sum(const Matrix<T>&right, const size_t threads_numb);

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
Matrix<T>::Matrix(size_t width_, size_t height_) : width(width_), height(height_) {
	try {
		rows.resize(width);
		for (auto it : rows) {
			it.resize(height);
		}
	}
	catch (...) {
		std::cout << "bad alloc";
	}
	
}

template<typename T>
Matrix<T>::Matrix(const std::vector<std::vector<T>>& rows_) {
	if (check_eq_size(rows_)) { /*от строки к строке длина не меняется*/
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
inline Matrix<T> Matrix<T>::operator+(const Matrix<T>& right) {
	if (enable_multithread == false) {
		return one_thread_sum(right);
	}
	
}

template<typename T>
inline Matrix<T> Matrix<T>::multhread_sum(const Matrix<T>& right, const size_t threads_numb)
{
	if (size_mismatch(right)) {
		return Matrix<T>();
	}
	/*else {
		MultiThreadCalculator<T> adder(*this, right, threads_numb);
	}*/
	
}

template<typename T>
inline Matrix<T> Matrix<T>::one_thread_sum(const Matrix<T>& right) {
	
	if (size_mismatch(right)) {
		//throw()? Если размеры не совпадают
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



