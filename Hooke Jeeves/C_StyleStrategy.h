#pragma once
#include "CalcStrategy.h"
#include "..\HookeJeeves\Ctor_Params.h"

class C_StyleStrategy : public CalcStrategy {
public:
	C_StyleStrategy() = delete;
	C_StyleStrategy(const Ctor_Params& params);
	virtual void calc() override;
	virtual const std::vector<double>& get_res() override;
private:
	Ctor_Params calc_parameters;
	std::vector<double> result{};
};