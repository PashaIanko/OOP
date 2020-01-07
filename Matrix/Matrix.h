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
	Matrix(size_t width, size_t height, T& default_val);
	Matrix(size_t width, size_t height, T&& default_val);


	inline size_t get_width() const { return width; };
	inline size_t get_height() const { return height; };
	std::vector<T>& get_row(size_t idx);
	const std::vector<T>& get_row(size_t idx) const;
	const std::vector<T> get_column(size_t idx) const;
	inline std::vector<std::vector<T>>& get_data();
	inline const std::vector<std::vector<T>>& get_data() const;
	
	Matrix<T> operator+(const Matrix<T>&right);
	Matrix<T> operator-(const Matrix<T>&right);

	Matrix<T> multhread_sum(const Matrix<T>* left, const Matrix<T>* right, const size_t threads_numb);
	Matrix<T> multhread_multiply(const Matrix<T>* right, size_t threads_numb) const;
	Matrix<T> multhread_subtract(const Matrix<T>* left, const Matrix<T>* right, const size_t threads_numb) const;
	T multhread_det(size_t threads_numb) const;

	bool operator==(const Matrix<T>& right) const;
	bool operator!=(const Matrix<T>& right) const;

	Matrix<T>& operator=(const Matrix<T>& right);

	void enable_multithreading();
	void disable_multithreading();

private:
	size_t height = 0;
	size_t width = 0;
	std::vector<std::vector<T>> rows{};
	bool enable_multithread = false;
	
	bool check_eq_size(const std::vector<std::vector<T>>& rows) const;
	bool size_mismatch(const Matrix<T>& right) const;
	void resize_rows(const size_t height, const size_t width);

	const double multithread_sum_optimization_parameter = 250; /*��������� ������������*/
	const size_t max_threads_limit = 5;
};

template<typename T>
Matrix<T>::Matrix(size_t height_, size_t width_) : width(width_), height(height_) {
	try {
		resize_rows(height, width);
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
inline Matrix<T>::Matrix(size_t width_, size_t height_, T & default_val) 
	: width(width_), height(height_)
{
	try {
		resize_rows(height, width);
	}
	catch (...) {

	}
	for (size_t i = 0; i < rows.size(); i++) {
		std::vector<T>& cur_row = rows[i];
		std::fill(cur_row.begin(), cur_row.end(), default_val);
	}
}

template<typename T>
inline Matrix<T>::Matrix(size_t width_, size_t height_, T && default_val) 
	: width(width_), height(height_)

{
	try {
		resize_rows(height, width);
	}
	catch (...) {

	}
	for (size_t i = 0; i < rows.size(); i++) {
		std::vector<T>& cur_row = rows[i];
		std::fill(cur_row.begin(), cur_row.end(), default_val);
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
		return multhread_sum(this, &right, 1);
	}
	else {
		/*���������� ������������ � ������. ������ ������ == 873,91. (����� �����/������_������)
		== ����������� ���-�� ������� + ������������, ����� ��� �� ��������� ���������� ����� (~5 �������)*/
		size_t optimal_threads_numb = (size_t)
			(right.get_height() / multithread_sum_optimization_parameter);
		if (optimal_threads_numb == 0)
			optimal_threads_numb = 1;
		if (optimal_threads_numb > max_threads_limit)
			optimal_threads_numb = max_threads_limit;
		else {
			return multhread_sum(this, &right, optimal_threads_numb);
		}
	}
	
}

template<typename T>
inline Matrix<T> Matrix<T>::operator-(const Matrix<T>& right) {
	if (enable_multithread == false) {
		return multhread_subtract(this, &right, 1);
	}
	else {
		/*���������� ������������ � ������. ������ ������ == 873,91. (����� �����/������_������)
		== ����������� ���-�� ������� + ������������, ����� ��� �� ��������� ���������� ����� (~5 �������)*/
		size_t optimal_threads_numb = (size_t)
			(right.get_height() / multithread_sum_optimization_parameter);
		if (optimal_threads_numb == 0)
			optimal_threads_numb = 1;
		if (optimal_threads_numb > max_threads_limit)
			optimal_threads_numb = max_threads_limit;
		else {
			return multhread_subtract(this, &right, optimal_threads_numb);
		}
	}
}


template<typename T>
inline Matrix<T> Matrix<T>::multhread_sum(const Matrix<T>* left, const Matrix<T>* right, const size_t threads_numb)
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
		return multiplier.multiply();
	}
}

template<typename T>
inline Matrix<T> Matrix<T>::multhread_subtract(const Matrix<T>* left, const Matrix<T>* right, const size_t threads_numb) const
{
	if (size_mismatch(*right)) {
		return Matrix<T>();
	}
	else {
		MultithreadCalculator<T> subtractor(left, right, threads_numb);
		return subtractor.subtract();
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
}

template<typename T>
inline bool Matrix<T>::operator!=(const Matrix<T>& right) const {
	return !(this->operator==(right));
}

template<typename T>
inline Matrix<T>& Matrix<T>::operator=(const Matrix<T>& right) {
	if (*this != right) {
		height = right.get_height();
		width = right.get_width();
		rows = right.rows;
		enable_multithread = right.enable_multithread;
	}
	return *this;
}

template<typename T>
inline void Matrix<T>::enable_multithreading() {
	enable_multithread = true;
}

template<typename T>
inline void Matrix<T>::disable_multithreading() {
	enable_multithread = false;
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

template<typename T>
inline void Matrix<T>::resize_rows(const size_t height, const size_t width) {
	rows.resize(height);
	for (size_t i = 0; i < rows.size(); ++i) {
		rows[i].resize(width);
	}
}



