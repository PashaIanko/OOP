#pragma once


double best_nearby(double* delta, double* point, double prevbest, int nvars, double(*f)(double*, int));
int hooke 
(
	int nvars, 
	double* startpt, 
	double* endpt, 
	double rho, 
	double epsilon, 
	int itermax, 
	double(*f)(double*, int)
);
double f(double* x, int n);