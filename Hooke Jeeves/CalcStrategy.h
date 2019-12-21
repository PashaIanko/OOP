#pragma once
class CalcStrategy {
public:
	virtual ~CalcStrategy() {};
	virtual void calc() = 0; /*Сишный расчёт или после рефакторинга*/
};