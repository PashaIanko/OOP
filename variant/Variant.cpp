#include "pch.h"
#include <iostream>
#include "Variant.h"
#include "getter.h"


int main()
{
	Variant<int> v;
	float g = 7.7f;
	//v.SetValue(g);
	Variant<int, double, float> v2;
	int y = 6;
	Variant<int, double> v3(y);
	double f = 6.2f;
	Variant<int, double, char> v4(f);


}
