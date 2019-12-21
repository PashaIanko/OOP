#pragma once
class CalcStrategy {
public:
	virtual ~CalcStrategy() {};
	virtual void calc() = 0; /*Сишный расчёт или после рефакторинга*/
	
	size_t number_of_iterations() const;
protected:
	void set_iterations_numb(size_t numb);
private:
	size_t iterations_numb{};
};