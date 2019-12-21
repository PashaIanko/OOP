#include "pch.h"
#include "C_StyleStrategy.h"
#include "..\HookeJeeves\HookeJeeves.h"
//#include "HookeJeves.h"

C_StyleStrategy::C_StyleStrategy(const Ctor_Params & params) {
	calc_parameters = params;
}

void C_StyleStrategy::calc() { /*support the C-style 
							   function interface*/
	int jj = hooke
	(
		calc_parameters.dimensions,
		calc_parameters.raw_data,
		calc_parameters.cooked_data,
		calc_parameters.rho,
		calc_parameters.epsilon,
		calc_parameters.iterations_limit,
		calc_parameters.func_ptr
	);
	set_iterations_numb(jj);
	//numb_of_iterations = jj;
}

/*void C_StyleStrategy::set_params(const Ctor_Params & params) {
	calc_parameters = params;
}*/
