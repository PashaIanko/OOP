#include "pch.h"
#include <memory>
#include <iostream>
#include <sstream>
#include <istream>
#include "gtest\gtest.h"
#include "..\HookeJeeves\HookeJeeves.h"
#include "C_StyleStrategy.h"
#include "OOP_StyleStrategy.h"
#include "..\HookeJeeves\Ctor_Params.h"
#include "TestWrapper.h"
#include <vector>
#include "Functions.h"


using cur_strategy = OOP_StyleStrategy;//C_StyleStrategy;

TEST(GeneralFunctions, RosenbrocksFunc) {
	double			RHO_BEGIN = 0.5;
	double			EPSMIN = 1E-6;
	int				IMAX = 5000;
	int				domain_dimensions = 2; //f(x,y) , f:R^2->R^1

	std::vector<double> startpt(domain_dimensions, 0);
	startpt[0] = -1.2; /*предположит. координаты минимума*/
	startpt[1] = 1.0;

	Ctor_Params params
	{
		RHO_BEGIN,
		EPSMIN,
		IMAX,
		&RosenbrocksFunc,
		startpt
	};
	
	TestWrapper<OOP_StyleStrategy> oop_wrapper(params);
	TestWrapper<C_StyleStrategy> c_wrapper(params);
	
	oop_wrapper.calc();
	c_wrapper.calc();

	EXPECT_TRUE(oop_wrapper.get_res() == c_wrapper.get_res());
	EXPECT_TRUE(oop_wrapper.get_iters() == c_wrapper.get_iters());
}

TEST(GeneralFunctions, parabolic_func) {
	double			RHO_BEGIN = 0.5;
	double			EPSMIN = 1E-6;
	int				IMAX = 5000;
	int				domain_dimensions = 1; //simple f: R^1->R^1 (f(x))
	std::vector<double> startpt(domain_dimensions, 0);

	startpt[0] = 0.5;
	Ctor_Params params
	{
		RHO_BEGIN,
		EPSMIN,
		IMAX,
		&ParabolicFunc,
		startpt
	};


	TestWrapper<OOP_StyleStrategy> oop_wrapper(params);
	TestWrapper<C_StyleStrategy> c_wrapper(params);

	oop_wrapper.calc();
	c_wrapper.calc();

	EXPECT_TRUE(oop_wrapper.get_res() == c_wrapper.get_res());
	EXPECT_TRUE(oop_wrapper.get_iters() == c_wrapper.get_iters());
}

TEST(GeneralFunctions, shifted_up_parabolic_func) {
	double			RHO_BEGIN = 0.5;
	double			EPSMIN = 1E-6;
	int				IMAX = 5000;
	
	int				domain_dimensions = 1; //simple f: R^1->R^1 (f(x))
	std::vector<double> startpt(domain_dimensions, 0);

	startpt[0] = 0.5;
	Ctor_Params params
	{
		RHO_BEGIN,
		EPSMIN,
		IMAX,
		&Shifted_up_ParabolicFunc,
		startpt
	};

	TestWrapper<OOP_StyleStrategy> oop_wrapper(params);
	TestWrapper<C_StyleStrategy> c_wrapper(params);

	oop_wrapper.calc();
	c_wrapper.calc();

	EXPECT_TRUE(oop_wrapper.get_res() == c_wrapper.get_res());
	EXPECT_TRUE(oop_wrapper.get_iters() == c_wrapper.get_iters());
}

TEST(GeneralFunctions, shifted_left_parabolic_func) {
	double			RHO_BEGIN = 0.5;
	double			EPSMIN = 1E-6;
	int				IMAX = 5000;
	
	int				domain_dimensions = 1; //simple f: R^1->R^1 (f(x))

	std::vector<double> startpt(domain_dimensions, 0);

	startpt[0] = 0.5;
	Ctor_Params params
	{
		RHO_BEGIN,
		EPSMIN,
		IMAX,
		&Shifted_left_ParabolicFunc,
		startpt
	};

	TestWrapper<OOP_StyleStrategy> oop_wrapper(params);
	TestWrapper<C_StyleStrategy> c_wrapper(params);

	oop_wrapper.calc();
	c_wrapper.calc();

	EXPECT_TRUE(oop_wrapper.get_res() == c_wrapper.get_res());
	EXPECT_TRUE(oop_wrapper.get_iters() == c_wrapper.get_iters());
}

TEST(GeneralFunctions, Rotated_shifted_paraboloid) {
	double			RHO_BEGIN = 0.5;
	double			EPSMIN = 1E-6;
	int				IMAX = 5000;
	
	int				domain_dimensions = 2; //simple f: R^2->R^1 (f(x)) /*чашка*/

	std::vector<double> startpt(domain_dimensions, 0);
	
	startpt[0] = 0.5;
	startpt[1] = 0.5;

	Ctor_Params params
	{
		RHO_BEGIN,
		EPSMIN,
		IMAX,
		&Shifted_Rotated_Paraboloid,
		startpt
	};

	TestWrapper<OOP_StyleStrategy> oop_wrapper(params);
	TestWrapper<C_StyleStrategy> c_wrapper(params);

	oop_wrapper.calc();
	c_wrapper.calc();

	EXPECT_TRUE(oop_wrapper.get_res() == c_wrapper.get_res());
	EXPECT_TRUE(oop_wrapper.get_iters() == c_wrapper.get_iters());
}


int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	getchar();
	return 0;
}