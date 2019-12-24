#pragma once
#include <vector>

class CalcStrategy {
public:
	virtual ~CalcStrategy() {};
	virtual void calc() = 0; /*Сишный расчёт или после рефакторинга*/
	virtual const std::vector<double>& get_res() = 0;
	size_t number_of_iterations() const;
protected:
	void set_iterations_numb(size_t numb);
private:
	size_t iterations_numb{};
};