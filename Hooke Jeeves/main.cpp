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


using cur_strategy = C_StyleStrategy;//OOP_StyleStrategy;//C_StyleStrategy;

TEST(GeneralFunctions, RosenbrocksFunc) {
	const size_t	SIZE = 250;
	double			RHO_BEGIN = 0.5;
	double			EPSMIN = 1E-6;
	int				IMAX = 5000;

	double			startpt[SIZE], endpt[SIZE];
	int				domain_dimensions = 2; //f(x,y) , f:R^2->R^1
	
	startpt[0] = -1.2; /*предположит. координаты минимума*/
	startpt[1] = 1.0;

	Ctor_Params params
	{
		domain_dimensions,
		startpt,
		endpt,
		RHO_BEGIN,
		EPSMIN,
		IMAX,
		SIZE,
		&RosenbrocksFunc
	};

	TestWrapper<cur_strategy> t(params);
	t.calc();
	size_t expect_iterations_numb = 19;
	EXPECT_TRUE(t.minimum_match({ 1.0, 1.0 }));
	EXPECT_TRUE(t.numb_of_iterations_match(expect_iterations_numb));
}

TEST(GeneralFunctions, parabolic_func) {
	const size_t	SIZE = 250;
	double			RHO_BEGIN = 0.5;
	double			EPSMIN = 1E-6;
	int				IMAX = 5000;
	double			startpt[SIZE], endpt[SIZE];
	int				domain_dimension = 1; //simple f: R^1->R^1 (f(x))

	startpt[0] = 0.5;
	Ctor_Params params
	{
		domain_dimension,
		startpt,
		endpt,
		RHO_BEGIN,
		EPSMIN,
		IMAX,
		SIZE,
		&ParabolicFunc
	};

	TestWrapper<cur_strategy> t(params);
	t.calc();
	
	size_t expect_iterations_numb = 19;
	EXPECT_TRUE(t.minimum_match({ 0.0 })); /*минимум параболы несмещённой*/
	EXPECT_TRUE(t.numb_of_iterations_match(expect_iterations_numb));
}

TEST(GeneralFunctions, shifted_up_parabolic_func) {
	const size_t	SIZE = 250;
	double			RHO_BEGIN = 0.5;
	double			EPSMIN = 1E-6;
	int				IMAX = 5000;
	double			startpt[SIZE], endpt[SIZE];
	int				domain_dimension = 1; //simple f: R^1->R^1 (f(x))

	startpt[0] = 0.5;
	Ctor_Params params
	{
		domain_dimension,
		startpt,
		endpt,
		RHO_BEGIN,
		EPSMIN,
		IMAX,
		SIZE,
		&Shifted_up_ParabolicFunc
	};

	TestWrapper<cur_strategy> t(params);
	t.calc();

	size_t expect_iterations_numb = 19;
	EXPECT_TRUE(t.minimum_match({ 0.0 })); /*минимум параболы смещённой вертикально*/
	EXPECT_TRUE(t.numb_of_iterations_match(expect_iterations_numb));
}

TEST(GeneralFunctions, shifted_left_parabolic_func) {
	const size_t	SIZE = 250;
	double			RHO_BEGIN = 0.5;
	double			EPSMIN = 1E-6;
	int				IMAX = 5000;
	double			startpt[SIZE], endpt[SIZE];
	int				domain_dimension = 1; //simple f: R^1->R^1 (f(x))

	startpt[0] = 0.5;
	Ctor_Params params
	{
		domain_dimension,
		startpt,
		endpt,
		RHO_BEGIN,
		EPSMIN,
		IMAX,
		SIZE,
		&Shifted_left_ParabolicFunc
	};

	TestWrapper<cur_strategy> t(params);
	t.calc();

	size_t expect_iterations_numb = 19;
	EXPECT_TRUE(t.minimum_match({ -5.0 })); /*минимум параболы смещённой по оси x*/
	EXPECT_TRUE(t.numb_of_iterations_match(expect_iterations_numb));
}


int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	getchar();
	return 0;
}