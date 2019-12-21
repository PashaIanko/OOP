#pragma once
#include "CalcStrategy.h"
#include "Ctor_Params.h"

class C_StyleStrategy : public CalcStrategy {
public:
	C_StyleStrategy() = delete;
	C_StyleStrategy(const Ctor_Params& params);
	virtual void calc() override;
	//void set_params(const Ctor_Params& params);

private:
	Ctor_Params calc_parameters{};
	int numb_of_iterations {};
};