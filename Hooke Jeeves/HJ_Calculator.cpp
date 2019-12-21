#include "pch.h"
#include "HJ_Calculator.h"

HJ_Calculator::HJ_Calculator(const Ctor_Params & calc_params) : 
	domain_dimensions(calc_params.dimensions),
	convergence_param(calc_params.rho),
	accuracy(calc_params.epsilon),
	iterations_lim(calc_params.iterations_limit)
{
	if (calc_params.raw_data) {
		raw_data.assign(calc_params.raw_data, calc_params.raw_data + calc_params.data_size);
	}
	if (calc_params.cooked_data) {
		cooked_data.assign(calc_params.cooked_data, calc_params.cooked_data + calc_params.data_size);
	}
}
