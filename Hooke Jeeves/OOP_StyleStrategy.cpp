#include "pch.h"
#include "OOP_StyleStrategy.h"
#include "..\HookeJeeves\HJ_Calculator.h"


OOP_StyleStrategy::OOP_StyleStrategy(const Ctor_Params & params) {
	this->calc_parameters = params;
}

void OOP_StyleStrategy::calc(){
	HJ_Calculator calculator(calc_parameters);
	size_t iterations_made = calculator.HJ_calc();
	set_iterations_numb(iterations_made);
	
	/*необходимо запомнить результаты расчёта, чтобы передать их в TestWrapper*/
	calculated_min_coord = calculator.return_min_coordinates();
}

std::vector<double> OOP_StyleStrategy::get_calculated_min_coord() const
{
	if (calculated_min_coord.size()) {
		return calculated_min_coord;
	}
	return std::vector<double>();
}
