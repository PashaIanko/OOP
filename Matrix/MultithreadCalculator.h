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
	//MultithreadCalculator(const Matrix<T>& left, const Matrix<T>& right, size_t threads_numb);
	MultithreadCalculator(Matrix<T>* left, Matrix<T>* right, size_t threads_numb);
	Matrix<T> sum();

	
private:
	//const Matrix<T>& left;
	//const Matrix<T>& right;
	Matrix<T>* left = nullptr;
	Matrix<T>* right = nullptr;
	size_t threads_numb = 0;
	//Matrix<T> calc(void (*calc_f)(std::pair<size_t, size_t>&, Matrix<T>&, Matrix<T>&));
	Matrix<T> calc(void(*calc_f)(std::pair<size_t, size_t>, Matrix<T>*, Matrix<T>*));
	std::vector<std::pair<size_t, size_t>> divide_matrix() const;
};

//template<typename T>
//MultithreadCalculator<T>::MultithreadCalculator(const Matrix<T>& left_, const Matrix<T>& right_, size_t threads_numb_) :
//	left(left_), right(right_), threads_numb(threads_numb_)
//{
//	int v = 5;
//}

template<typename T>
inline MultithreadCalculator<T>::MultithreadCalculator(Matrix<T>* left_, Matrix<T>* right_, size_t threads_numb_) 
	: left(left_), right(right_), threads_numb(threads_numb_)
{
}


template<typename T>
inline Matrix<T> MultithreadCalculator<T>::sum() {
	return calc(&CalcFunctions::partial_sum);
}

void product(std::promise<void>&& intPromise, int a, int b) {
	intPromise.set_value();
}
int foo(int){
	return 5;
}

template<typename T>
inline Matrix<T> MultithreadCalculator<T>::calc(
	void(*calc_f)(std::pair<size_t, size_t>, Matrix<T>* res, Matrix<T>* right_matrix))
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
	//size_t numb_of_strings = left->get_height();
	//size_t strings_per_thread = (size_t)(numb_of_strings / threads_numb);

	//if (strings_per_thread == 0) /*потоков больше чем строк*/
	//{
	//	strings_per_thread = 1;
	//}
	//std::vector<std::pair<size_t, size_t>> result;
	//size_t from;
	//size_t to;
	//for (size_t i = 0; i < numb_of_strings; i+=strings_per_thread) {
	//	from = i;
	//	to = i + strings_per_thread; //[0,3),[3,7),...
	//	if (to > numb_of_strings) {
	//		to = numb_of_strings;
	//		result.push_back({ from, to });
	//		break;
	//	}
	//	result.push_back({from, to});
	//}
	//return result;

	std::vector<std::pair<size_t, size_t>> result;
	size_t numb_of_strings = left->get_height();
	size_t strings_per_thread = (size_t)(numb_of_strings / threads_numb);
	//if (strings_per_thread == 0) /*потоков больше чем строк*/
	//{
		//strings_per_thread = 1;
	//}
	size_t from = 0;
	for (size_t i = 0; i < threads_numb; i++)
	{
		result.push_back({ from , from + strings_per_thread });
		from += strings_per_thread;
		//if (from + strings_per_thread >= numb_of_strings) {
			//break;
		//}
	}
	result[threads_numb - 1].second = numb_of_strings;
	return result;
}

//template<typename T>
//inline void MultithreadCalculator<T>::partial_sum(std::pair<idx_from, idx_to>&, std::shared_ptr<Matrix<T>>&) {
//	return;
//}
