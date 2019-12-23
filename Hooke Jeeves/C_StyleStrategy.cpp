#include "pch.h"
#include "C_StyleStrategy.h"
#include "..\HookeJeeves\HookeJeeves.h"
//#include "HookeJeves.h"

C_StyleStrategy::C_StyleStrategy(const Ctor_Params & params) {
	calc_parameters = params;
}

void C_StyleStrategy::calc() { /*support the C-style 
							   function interface*/
	result.resize(calc_parameters.raw_data.size());
	int jj = hooke
	(
		calc_parameters.dimensions,
		calc_parameters.raw_data.data(),
		result.data(),
		calc_parameters.rho,
		calc_parameters.epsilon,
		calc_parameters.iterations_limit,
		calc_parameters.func_ptr
	);
	set_iterations_numb(jj);
	//set_calc_res(calc_parameters.cooked_data);
}

void C_StyleStrategy::set_calc_res(const std::vector<double>& v){
	result = v;
}

const std::vector<double>& C_StyleStrategy::get_res() {
	return result;
}

