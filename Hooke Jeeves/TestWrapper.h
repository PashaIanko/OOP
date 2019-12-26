#pragma once
#include "C_StyleStrategy.h"
#include "OOP_StyleStrategy.h"
#include "gtest\gtest.h"
#include <vector>
#include <iterator>

template<typename T>
class TestWrapper {

public:
	TestWrapper() = delete;
	TestWrapper(const Ctor_Params& params);
	void calc();
	inline size_t get_iterations_numb() const;
	inline const std::vector<double>& get_result() const;
private:
	const Ctor_Params& calc_parameters;
	std::shared_ptr<CalcStrategy> calc_strategy {};
	const double check_accuracy = 0.00001;
};

template<typename T>
inline TestWrapper<T>::TestWrapper(const Ctor_Params & params) : calc_parameters (params) {
	this->calc_strategy = std::make_shared<T>(params);
}

template<typename T>
inline void TestWrapper<T>::calc() {
	calc_strategy->calc();
}

template<typename T>
inline size_t TestWrapper<T>::get_iterations_numb() const {
	return calc_strategy->get_iterations_numb();
}

template<typename T>
inline const std::vector<double>& TestWrapper<T>::get_result() const {
	return calc_strategy->get_result();
}
