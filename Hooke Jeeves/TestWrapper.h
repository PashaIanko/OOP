#pragma once
#include "C_StyleStrategy.h"
#include "OOP_StyleStrategy.h"

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

template<typename T>
inline bool TestWrapper<T>::numb_of_iterations_match(const size_t expect) const {
	return false;
}
