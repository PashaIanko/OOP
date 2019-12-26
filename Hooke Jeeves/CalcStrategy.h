#pragma once
#include <vector>

class CalcStrategy {
public:
	virtual ~CalcStrategy() {};
	virtual void calc() = 0; /*������ ������ ��� ����� ������������*/
	virtual const std::vector<double>& get_result() = 0;
	size_t get_iterations_numb() const;
protected:
	void set_iterations_numb(size_t numb);
private:
	size_t iterations_numb{};
};