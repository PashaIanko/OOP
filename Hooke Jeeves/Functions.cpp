#include "pch.h"
#include "Functions.h"

double RosenbrocksFunc(double * x, int)
{
	double	   a, b, c;
	a = x[0];
	b = x[1];
	c = 100.0 * (b - (a * a)) * (b - (a * a));
	return (c + ((1.0 - a) * (1.0 - a)));
}

double ParabolicFunc(double * x, int)
{
	if (x != nullptr) {
		return (x[0])*(x[0]);
	}
	return 0;
}

double Shifted_up_ParabolicFunc(double * x, int)
{
	const double shift = 5.0;
	if (x != nullptr) {
		return (x[0])*(x[0]) + shift;
	}
	return 0;
}

double Shifted_left_ParabolicFunc(double * x, int)
{
	const double shift = 5.0;
	if (x != nullptr) {
		return (x[0] + shift)*(x[0] + shift);
	}
	return 0;
}

double Shifted_Rotated_Paraboloid(double * x, int)
{
	const double x_shift = 5.0;
	const double y_shift = 15.0;

	if (x != nullptr) { //x^2 + y^2
		return (x[0] + x_shift)*(x[0] + x_shift) +
				(x[1] + y_shift)*(x[1] + y_shift);
	}
	return 0;
}
