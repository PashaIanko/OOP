#pragma once
#include "pch.h"
//#include "Matrix.h"
template<typename T>
class Matrix;

template <typename T>
class MultithreadCalculator {
public:
	MultithreadCalculator(const Matrix<T>& left, const Matrix<T>& right, size_t threads_numb);
	Matrix<T> sum() const;

	using idx_from = size_t;
	using idx_to = size_t;
private:
	const Matrix<T>& left;
	const Matrix<T>& right;

	void partial_sum(std::pair<idx_from, idx_to>& interval, const Matrix<T>& result);
	Matrix<T> calc(void(MultithreadCalculator::* f)(std::pair<idx_from, idx_to>&, std::shared_ptr<Matrix<T>>));
};

template<typename T>
MultithreadCalculator<T>::MultithreadCalculator(const Matrix<T>& left_, const Matrix<T>& right_, size_t threads_numb) :
	left(left_), right(right_)
{
	int v = 5;
}

template<typename T>
inline Matrix<T> MultithreadCalculator<T>::sum() const {
	return Matrix<T>(5, 1);
}

template<typename T>
inline void MultithreadCalculator<T>::partial_sum(std::pair<idx_from, idx_to>& interval, const Matrix<T> & result) {

}
