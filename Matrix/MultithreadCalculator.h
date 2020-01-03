#pragma once
#include "pch.h"
//#include "Matrix.h"
#include <memory>
#include <utility>
#include <functional>
#include <future>
#include <thread>

template<typename T>
class Matrix;

using idx_from = size_t;
using idx_to = size_t;

template <typename T>
class MultithreadCalculator {
public:
	MultithreadCalculator(const Matrix<T>& left, const Matrix<T>& right, size_t threads_numb);
	Matrix<T> sum() const;

	
private:
	const Matrix<T>& left;
	const Matrix<T>& right;
	size_t threads_numb = 0;
	Matrix<T> calc(std::function<void(std::pair<idx_from, idx_to>&, std::shared_ptr<Matrix<T>>)>) const;
	std::vector<std::pair<size_t, size_t>> divide_matrix() const;
};

template<typename T>
MultithreadCalculator<T>::MultithreadCalculator(const Matrix<T>& left_, const Matrix<T>& right_, size_t threads_numb_) :
	left(left_), right(right_), threads_numb(threads_numb_)
{
	int v = 5;
}



template<typename T> 
void partial_sum(std::pair<idx_from, idx_to>&, std::shared_ptr<Matrix<T>>) {
	return;
}


template<typename T>
inline Matrix<T> MultithreadCalculator<T>::sum() const {
	return calc(partial_sum<T>);
}

void product(std::promise<void>&& intPromise, int a, int b) {
	intPromise.set_value();
}
int foo(int){
	return 5;
}

template<typename T>
inline Matrix<T> MultithreadCalculator<T>::calc(std::function<void(std::pair<idx_from, idx_to>&, std::shared_ptr<Matrix<T>>)> func) const
{
	Matrix<T> res = left;
	std::vector <std::pair<size_t, size_t>> line_interv = divide_matrix();

	//std::promise<void> sumPromise;
	//std::future<void> sumRes = sumPromise.get_future();
	//std::thread sumThread(product, std::move(sumPromise), 5, 1);

	std::vector<std::future<void>> futures;
	std::pair<size_t, size_t> p;

	//typedef void function_t(std::pair<idx_from, idx_to>&, std::shared_ptr<Matrix<T>>);

	//using function_t = void (*)(std::pair<idx_from, idx_to>&, std::shared_ptr<Matrix<T>>);
	//function_t* f = func.target<function_t*>();

	//void(*)(std::pair<idx_from, idx_to>&, std::shared_ptr<Matrix<T>>) ptr_fun = func.target<function_t>();
	std::future<int> fu = std::async(std::launch::async, foo, 5);// , p, std::make_shared<Matrix<T>>(res));

	return Matrix<T>();
}

template<typename T>
inline std::vector<std::pair<size_t, size_t>> MultithreadCalculator<T>::divide_matrix() const
{
	size_t numb_of_strings = left.get_height();
	size_t strings_per_thread = (size_t)(numb_of_strings / threads_numb);

	if (strings_per_thread == 0) /*потоков больше чем строк*/
	{
		strings_per_thread = 1;
	}
	std::vector<std::pair<size_t, size_t>> result;
	size_t from;
	size_t to;
	for (size_t i = 0; i < numb_of_strings; i+=strings_per_thread) {
		from = i;
		to = i + strings_per_thread; //[0,3),[3,7),...
		if (to > numb_of_strings) {
			to = numb_of_strings + 1;
			result.push_back({ from, to });
			break;
		}
		result.push_back({from, to});
	}
	return result;
}
