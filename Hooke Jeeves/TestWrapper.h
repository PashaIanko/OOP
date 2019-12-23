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
	C_StyleStrategy* ptr = static_cast<C_StyleStrategy*>(calc_strategy.get());
	const std::vector<double>& calculated_coord = ptr->get_res();
	size_t i = 0;
	for (auto it : min_coordinates) {
		EXPECT_NEAR(it, calculated_coord[i], check_accuracy);
		i++;
	}
	return true;
}

template<>
inline bool TestWrapper<OOP_StyleStrategy>::minimum_match(const std::vector<double>& expect_min_coordinates) const {
	OOP_StyleStrategy* ptr = static_cast<OOP_StyleStrategy*>(calc_strategy.get());
	
	std::vector<double> calculated_coord = ptr->get_calculated_min_coord();
	size_t i = 0;
	for (auto it: expect_min_coordinates) {
		EXPECT_NEAR(it, calculated_coord[i], check_accuracy);
		i++;
	}
	return true;
}



template<typename T>
inline bool TestWrapper<T>::numb_of_iterations_match(const size_t expect) const {
	return calc_strategy->number_of_iterations() == expect;
}
