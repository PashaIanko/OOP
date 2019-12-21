#pragma once
#include "Ctor_Params.h"
#include <vector>

class HJ_Calculator {

public:
	HJ_Calculator() = delete;
	HJ_Calculator(const Ctor_Params& calc_parameters);

	//set_function()

private:
	int domain_dimensions;
	double convergence_param;
	double accuracy;
	int iterations_lim;
	std::vector<double> raw_data;
	std::vector<double> cooked_data;
};