#pragma once
class CalcStrategy {
public:
	virtual ~CalcStrategy() {};
	virtual void calc() = 0; /*������ ������ ��� ����� ������������*/
};