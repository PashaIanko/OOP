#pragma once
#include <vector>

struct Copyable {
	int dimensions; //����������� ������� ����������� �������
	double rho;
	double epsilon;
	int iterations_limit;
	size_t data_size;
	double(*func_ptr)(double*, int);
};

struct Ctor_Params 
{
	//int dimensions; //����������� ������� ����������� �������
	double rho;
	double epsilon;
	int iterations_limit;
	//size_t data_size;
	double(*func_ptr)(double*, int);
	const std::vector<double>& raw_data;
	//std::vector<double> cooked_data;
};
