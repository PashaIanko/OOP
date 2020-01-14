#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include "MultithreadCalculator.h"
#include <sstream>


const double multithread_sum_optimization_parameter = 250; /*Результат исследования*/
const double multithread_mult_optimization_parameter = 200; /*Результат исследования*/
const double multithread_det_optimization_parameter = 1.5; /*Результат исследования*/
const size_t max_threads_limit = 5;

template<typename T>
class Matrix {
public:
	Matrix() = default;
	
	Matrix(const std::vector<std::vector<T>>& data);
	Matrix(size_t width, size_t height, T default_val = T{});

	inline size_t get_width() const { return width; };
	inline size_t get_height() const { return height; };
	std::vector<T>& get_row(size_t idx);
	const std::vector<T>& get_row(size_t idx) const;
	const std::vector<T> get_column(size_t idx) const;
	inline std::vector<std::vector<T>>& get_data();
	inline const std::vector<std::vector<T>>& get_data() const;
	
	Matrix<T> operator+(const Matrix<T>&right);
	Matrix<T> operator-(const Matrix<T>&right);
	Matrix<T> operator*(const Matrix<T>&right);
	T det() const;

	Matrix<T> multhread_sum
	(const Matrix<T>* right, const size_t threads_numb) const;

	Matrix<T> multhread_multiply
	(const Matrix<T>* right, const size_t threads_numb) const;
	
	Matrix<T> multhread_subtract
	(const Matrix<T>* right, const size_t threads_numb) const;
	
	T multhread_det(size_t threads_numb) const;

	bool operator==(const Matrix<T>& right) const;
	bool operator==(const Matrix<T>&& right) const;
	bool operator!=(const Matrix<T>& right) const;

	Matrix<T>(Matrix<T>&& val) = default;
	Matrix<T>(const Matrix<T>& val) = default;
	Matrix<T>& operator=(const Matrix<T>& right) = default;
	Matrix<T>& operator=(Matrix<T>&& val) = default;


	inline void enable_multithreading();
	inline void disable_multithreading();
	inline bool multithread_on() const { return enable_multithread; }
	inline bool multithread_off()const { return !enable_multithread; }

private:
	size_t height = 0;
	size_t width = 0;
	std::vector<std::vector<T>> rows{};
	bool enable_multithread = false;
	
	
	bool check_eq_size(const std::vector<std::vector<T>>& rows) const;
	bool size_mismatch(const Matrix<T>& right) const;
	void resize_rows(const size_t height, const size_t width, const T& val);


	
};

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
		throw std::bad_alloc();
	}
}

template<typename T>
inline Matrix<T>::Matrix(size_t width_, size_t height_, T default_val) 
	: width(width_), height(height_)
{
	try {
		resize_rows(height, width, std::ref(default_val));
	}
	catch (...) {
		int v = 5;
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
inline bool Matrix<T>::operator==(const Matrix<T>&& right) const
{
	return false;
}

template<typename T>
inline std::vector<T>& Matrix<T>::get_row(size_t idx) {
	if (idx < rows.size()) {
		return rows[idx];
	}
	else {
		std::stringstream istr;
		istr << "Out of range" << idx;
		throw std::out_of_range(istr.str());
	}
}

template<typename T>
inline const std::vector<T>& Matrix<T>::get_row(size_t idx) const {
	if (idx < rows.size()) {
		return rows[idx];
	}
	else {
		std::stringstream istr;
		istr << "Out of range" << idx;
		throw std::out_of_range(istr.str());
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
	if (multithread_off() || right.multithread_off()) {
		return multhread_sum(&right, 1);
	}
	else {
		/*Результаты исследования в екселе. Меджик намбер == 250,91. (Колво строк/меджик_набмер)
		== оптимальное кол-во потоков + позаботиться, чтобы оно не превышало оговорённый порог (~5 потоков)*/
		size_t optimal_threads_numb = (size_t)
			(right.get_height() / multithread_sum_optimization_parameter);
		if (optimal_threads_numb == 0)
			optimal_threads_numb = 1;
		if (optimal_threads_numb > max_threads_limit)
			optimal_threads_numb = max_threads_limit;
		
		return multhread_sum(&right, optimal_threads_numb);
		
	}
	
}

template<typename T>
inline Matrix<T> Matrix<T>::operator*(const Matrix<T>& right) {
	if (multithread_off() || right.multithread_off()) {
		return multhread_multiply(&right, 1);
	}
	else {
		/*Результаты исследования в екселе. Меджик намбер == 200,91. (Колво строк/меджик_набмер)
		== оптимальное кол-во потоков + позаботиться, чтобы оно не превышало оговорённый порог (~5 потоков)*/
		size_t optimal_threads_numb = (size_t)
			(right.get_height() / multithread_mult_optimization_parameter);
		if (optimal_threads_numb == 0)
			optimal_threads_numb = 1;
		if (optimal_threads_numb > max_threads_limit)
			optimal_threads_numb = max_threads_limit;
		
		return multhread_multiply(&right, optimal_threads_numb);
		
	}

}

template<typename T>
inline T Matrix<T>::det() const {
	if (multithread_off()) {
		return multhread_det(1);
	}
	else {
		/*Меджик намбер == 1,5. (Колво строк/меджик_набмер)*/
		size_t optimal_threads_numb = (size_t)
			(height / multithread_det_optimization_parameter);
		if (optimal_threads_numb == 0)
			optimal_threads_numb = 1;
		if (optimal_threads_numb > max_threads_limit)
			optimal_threads_numb = max_threads_limit;
		return multhread_det(optimal_threads_numb);
	}
}

template<typename T>
inline Matrix<T> Matrix<T>::operator-(const Matrix<T>& right) {
	if (enable_multithread == false) {
		return multhread_subtract(&right, 1);
	}
	else {
		/*Результаты исследования в екселе. Меджик намбер == 250,91. (Колво строк/меджик_набмер)
		== оптимальное кол-во потоков + позаботиться, чтобы оно не превышало оговорённый порог (~5 потоков)*/
		size_t optimal_threads_numb = (size_t)
			(right.get_height() / multithread_sum_optimization_parameter);
		if (optimal_threads_numb == 0)
			optimal_threads_numb = 1;
		if (optimal_threads_numb > max_threads_limit)
			optimal_threads_numb = max_threads_limit;
		return multhread_subtract(&right, optimal_threads_numb);
		
	}
}


template<typename T>
inline Matrix<T> Matrix<T>::multhread_sum(const Matrix<T>* right, const size_t threads_numb) const
{
	if (size_mismatch(*right)) {
		return Matrix<T>();
	}
	else {
		MultithreadCalculator<T> adder(this, right, threads_numb);
		return adder.sum();
	}
	
}

template<typename T>
inline Matrix<T> Matrix<T>::multhread_multiply(const Matrix<T>* right, const size_t threads_numb) const
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
inline Matrix<T> Matrix<T>::multhread_subtract(const Matrix<T>* right, const size_t threads_numb) const
{
	if (size_mismatch(*right)) {
		return Matrix<T>();
	}
	else {
		MultithreadCalculator<T> subtractor(this, right, threads_numb);
		return subtractor.subtract();
	}
}

template<typename T>
inline T Matrix<T>::multhread_det(size_t threads_numb) const {
	if (width != height) {
		return T{};
	}
	MultithreadCalculator<T> calculator(this, threads_numb);
	return calculator.det(&CalcFunctions::partial_det);
}

template<typename T>
inline bool Matrix<T>::operator!=(const Matrix<T>& right) const {
	return !(this->operator==(std::ref(right)));
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
inline void Matrix<T>::resize_rows(const size_t height, const size_t width, const T& val) {
	rows.resize(height);
	for (size_t i = 0; i < rows.size(); ++i) {
		rows[i].resize(width, val);
	}
}



