#pragma once

struct Ctor_Params {
	int dimensions; //����������� ������� ����������� �������
	double* raw_data;
	double* cooked_data;
	double rho;
	double epsilon; 
	int iterations_limit;
};
