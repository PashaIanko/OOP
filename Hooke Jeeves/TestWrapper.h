#pragma once
#include "C_StyleStrategy.h"
#include "OOP_StyleStrategy.h"
#include "gtest\gtest.h"

template<typename T>
class TestWrapper {

public:
	TestWrapper() = delete;
	TestWrapper(const Ctor_Params& params);
	void calc();
	bool minimum_match(const std::vector<double>& min_coordinates) const;
	bool numb_of_iterations_match (const size_t expect) const;
private:
	Ctor_Params calc_parameters;
	std::shared_ptr<CalcStrategy> calc_strategy {};
	const double check_accuracy = 0.00001;
};

template<typename T>
inline TestWrapper<T>::TestWrapper(const Ctor_Params & params){
	this->calc_parameters = params;
	this->calc_strategy = std::make_shared<T>(params);
}

template<typename T>
inline void TestWrapper<T>::calc() {
	calc_strategy->calc();
}

template<typename T>
inline bool TestWrapper<T>::minimum_match(const std::vector<double>& min_coordinates) const {
	return false;
}

template<>
inline bool TestWrapper<C_StyleStrategy>::minimum_match(const std::vector<double>& min_coordinates) const {
	double* cooked_ptr = calc_parameters.cooked_data;
	if (cooked_ptr != nullptr) {
		for (size_t i = 0; i < calc_parameters.dimensions; i++) {
			EXPECT_NEAR(cooked_ptr[i], min_coordinates[i], check_accuracy);
		}
	}
	return true;
}



template<typename T>
inline bool TestWrapper<T>::numb_of_iterations_match(const size_t expect) const {
	return calc_strategy->number_of_iterations() == expect;
}
