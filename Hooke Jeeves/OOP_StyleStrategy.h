#pragma once
#include "CalcStrategy.h"
#include "..\HookeJeeves\Ctor_Params.h"

class OOP_StyleStrategy : public CalcStrategy {
public:
	OOP_StyleStrategy() = delete;
	OOP_StyleStrategy(const Ctor_Params& params);
	virtual void calc() override;

private:
	Ctor_Params calc_parameters{};
	int numb_of_iterations{};
};