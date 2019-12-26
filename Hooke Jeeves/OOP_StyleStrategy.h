#pragma once
#include "CalcStrategy.h"
#include "..\HookeJeeves\Ctor_Params.h"
#include <vector>

class OOP_StyleStrategy : public CalcStrategy {
public:
	OOP_StyleStrategy() = delete;
	OOP_StyleStrategy(const Ctor_Params& params);
	virtual void calc() override;
	virtual const std::vector<double>& get_result() override;

private:
	const Ctor_Params& calc_parameters;
	int numb_of_iterations{};
	std::vector<double> calculated_min_coord{};
};