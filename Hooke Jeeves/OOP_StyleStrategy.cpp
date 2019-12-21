#include "pch.h"
#include "OOP_StyleStrategy.h"
#include "..\HookeJeeves\HJ_Calculator.h"


OOP_StyleStrategy::OOP_StyleStrategy(const Ctor_Params & params) {
	this->calc_parameters = params;
}

void OOP_StyleStrategy::calc(){
	HJ_Calculator calculator(calc_parameters);
	
}
