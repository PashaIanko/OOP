#pragma once

struct Ctor_Params {
	int dimensions; //размерность области определения функции
	double* raw_data;
	double* cooked_data;
	double rho;
	double epsilon; 
	int iterations_limit;
	size_t data_size;
	double(*func_ptr)(double*, int);
};
