#include "pch.h"
#include "OOP_StyleStrategy.h"
#include "..\HookeJeeves\HJ_Calculator.h"


OOP_StyleStrategy::OOP_StyleStrategy(const Ctor_Params & params) :calc_parameters(params) {

}

void OOP_StyleStrategy::calc(){
	HJ_Calculator calculator(calc_parameters);
	size_t iterations_made = calculator.HJ_calc();
	set_iterations_numb(iterations_made);
	
	/*���������� ��������� ���������� �������, ����� �������� �� � TestWrapper*/
	calculated_min_coord = calculator.get_result();
}

const std::vector<double>& OOP_StyleStrategy::get_result() {
	return calculated_min_coord;
}
