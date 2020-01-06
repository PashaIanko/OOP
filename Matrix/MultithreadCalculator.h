#pragma once
#include "pch.h"
//#include "Matrix.h"
#include <memory>
#include <utility>
#include <functional>
#include <future>
#include <vector>
#include <thread>
#include "CalcFunctions.h"

template<typename T>
class Matrix;

using idx_from = size_t;
using idx_to = size_t;

template <typename T>
class MultithreadCalculator {
public:
	MultithreadCalculator(const Matrix<T>* left, const Matrix<T>* right, size_t threads_numb);
	MultithreadCalculator(const Matrix<T>* matrix, size_t threads_numb); //for det()
	
	Matrix<T> sum();
	Matrix<T> multiply();
	T det(T(*calc_f)(std::pair<size_t, size_t>, const Matrix<T>* matrix));

	
private:
	const Matrix<T>* left = nullptr;
	const Matrix<T>* right = nullptr;
	size_t threads_numb = 0;
	Matrix<T> calc(void(*calc_f)(std::pair<size_t, size_t>, Matrix<T>*, const Matrix<T>*));
	Matrix<T> calc(void(*calc_f)(std::pair<size_t, size_t>, Matrix<T>* res, const Matrix<T>* left_m, const Matrix<T>* right_m));
	std::vector<std::pair<size_t, size_t>> divide_matrix() const;
};

template<typename T>
inline MultithreadCalculator<T>::MultithreadCalculator(const Matrix<T>* left_, const Matrix<T>* right_, size_t threads_numb_) 
	: left(left_), right(right_), threads_numb(threads_numb_)
{
}

template<typename T>
inline MultithreadCalculator<T>::MultithreadCalculator(const Matrix<T>* matrix, size_t threads_numb_) :
left(matrix), threads_numb(threads_numb_)
{

}


template<typename T>
inline Matrix<T> MultithreadCalculator<T>::sum() {
	return calc(&CalcFunctions::partial_sum);
}

template<typename T>
inline Matrix<T> MultithreadCalculator<T>::multiply() {
	return calc(&CalcFunctions::partial_mult);
}

template<typename T>
inline T MultithreadCalculator<T>::det
(T(*calc_f)(std::pair<size_t, size_t>, const Matrix<T>* matrix))
{
	std::vector <std::pair<size_t, size_t>> line_interv = divide_matrix();
	std::vector<std::future<T>> futures;
	
	for (auto interval : line_interv) {
		futures.push_back(std::async(std::launch::async, calc_f, interval, left));
	}

	T det_val{};
	for (size_t i = 0; i < futures.size(); i++) {
		det_val += futures[i].get();
	}
	return det_val;
}

template<typename T>
inline Matrix<T> MultithreadCalculator<T>::calc
(void(*calc_f)(std::pair<size_t, size_t>, Matrix<T>* res, const Matrix<T>* left_m, const Matrix<T>* right_m)) {
	/*Ёто дл€ реализации умножени€, размеры результ матрицы мен€ютс€*/
	
	Matrix<T> res(left->get_height(), right->get_width());
	std::vector <std::pair<size_t, size_t>> line_interv = divide_matrix();
	std::vector<std::future<void>> futures;
	for (auto interval : line_interv) {
		futures.push_back(std::async(std::launch::async, calc_f, interval, &res, left, right));
	}
	for (size_t i = 0; i < futures.size(); i++) /*auto it:futures deleted*/
	{
		futures[i].get();
	}
	return res;
	
}

template<typename T>
inline Matrix<T> MultithreadCalculator<T>::calc(
	void(*calc_f)(std::pair<size_t, size_t>, Matrix<T>* res, const Matrix<T>* right_matrix))
{
	Matrix<T> res = *left;
	std::vector <std::pair<size_t, size_t>> line_interv = divide_matrix();
	std::vector<std::future<void>> futures;
	for (auto interval : line_interv) {
		futures.push_back(std::async(std::launch::async, calc_f, interval, &res, right));
	}
	for (size_t i =0; i<futures.size(); i++) /*auto it:futures deleted*/
	{
		futures[i].get();
	}
	return res;
}

template<typename T>
inline std::vector<std::pair<size_t, size_t>> MultithreadCalculator<T>::divide_matrix() const
{
	std::vector<std::pair<size_t, size_t>> result;
	size_t numb_of_strings = left->get_height();
	size_t strings_per_thread = (size_t)(numb_of_strings / threads_numb);
	size_t from = 0;
	for (size_t i = 0; i < threads_numb; i++)
	{
		result.push_back({ from , from + strings_per_thread });
		from += strings_per_thread;
	}
	result[threads_numb - 1].second = numb_of_strings;
	return result;
}

