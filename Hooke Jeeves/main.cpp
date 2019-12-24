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
	const size_t	SIZE = 250;
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
		startpt,
	};

	TestWrapper<OOP_StyleStrategy> oop_wrapper(params);
	TestWrapper<C_StyleStrategy> c_wrapper(params);
	
	oop_wrapper.calc();
	c_wrapper.calc();

	EXPECT_TRUE(oop_wrapper.get_res() == c_wrapper.get_res());
	EXPECT_TRUE(oop_wrapper.get_iters() == c_wrapper.get_iters());
}

//TEST(GeneralFunctions, parabolic_func) {
//	const size_t	SIZE = 250;
//	double			RHO_BEGIN = 0.5;
//	double			EPSMIN = 1E-6;
//	int				IMAX = 5000;
//	int				domain_dimension = 1; //simple f: R^1->R^1 (f(x))
//	std::vector<double> startpt(SIZE, 0);
//
//	startpt[0] = 0.5;
//	Ctor_Params params
//	{
//		domain_dimension,
//		RHO_BEGIN,
//		EPSMIN,
//		IMAX,
//		SIZE,
//		&ParabolicFunc,
//		startpt,
//	};
//
//	TestWrapper<cur_strategy> t(params);
//	t.calc();
//	
//	size_t expect_iterations_numb = 19;
//	EXPECT_TRUE(t.minimum_match({ 0.0 })); /*минимум параболы несмещённой*/
//	EXPECT_TRUE(t.numb_of_iterations_match(expect_iterations_numb));
//}
//
//TEST(GeneralFunctions, shifted_up_parabolic_func) {
//	const size_t	SIZE = 250;
//	double			RHO_BEGIN = 0.5;
//	double			EPSMIN = 1E-6;
//	int				IMAX = 5000;
//	
//	int				domain_dimension = 1; //simple f: R^1->R^1 (f(x))
//	std::vector<double> startpt(SIZE, 0);
//
//	startpt[0] = 0.5;
//	Ctor_Params params
//	{
//		domain_dimension,
//		RHO_BEGIN,
//		EPSMIN,
//		IMAX,
//		SIZE,
//		&Shifted_up_ParabolicFunc,
//		startpt,
//	};
//
//	TestWrapper<cur_strategy> t(params);
//	t.calc();
//
//	size_t expect_iterations_numb = 19;
//	EXPECT_TRUE(t.minimum_match({ 0.0 })); /*минимум параболы смещённой вертикально*/
//	EXPECT_TRUE(t.numb_of_iterations_match(expect_iterations_numb));
//}
//
//TEST(GeneralFunctions, shifted_left_parabolic_func) {
//	const size_t	SIZE = 250;
//	double			RHO_BEGIN = 0.5;
//	double			EPSMIN = 1E-6;
//	int				IMAX = 5000;
//	
//	int				domain_dimension = 1; //simple f: R^1->R^1 (f(x))
//
//	std::vector<double> startpt(SIZE, 0);
//
//	startpt[0] = 0.5;
//	Ctor_Params params
//	{
//		domain_dimension,
//		RHO_BEGIN,
//		EPSMIN,
//		IMAX,
//		SIZE,
//		&Shifted_left_ParabolicFunc,
//		startpt,
//	};
//
//	TestWrapper<cur_strategy> t(params);
//	t.calc();
//
//	size_t expect_iterations_numb = 19;
//	EXPECT_TRUE(t.minimum_match({ -5.0 })); /*минимум параболы смещённой по оси x*/
//	EXPECT_TRUE(t.numb_of_iterations_match(expect_iterations_numb));
//}
//
//TEST(GeneralFunctions, Rotated_shifted_paraboloid) {
//	const size_t	SIZE = 250;
//	double			RHO_BEGIN = 0.5;
//	double			EPSMIN = 1E-6;
//	int				IMAX = 5000;
//	
//	int				domain_dimension = 2; //simple f: R^2->R^1 (f(x)) /*чашка*/
//
//	std::vector<double> startpt(SIZE, 0);
//	
//	startpt[0] = 0.5;
//	startpt[1] = 0.5;
//
//	Ctor_Params params
//	{
//		domain_dimension,
//		RHO_BEGIN,
//		EPSMIN,
//		IMAX,
//		SIZE,
//		&Shifted_Rotated_Paraboloid,
//		startpt,
//	};
//
//	TestWrapper<cur_strategy> t(params);
//	t.calc();
//
//	size_t expect_iterations_numb = 19;
//	EXPECT_TRUE(t.minimum_match({ -5.0, -15.0 })); /*минимум параболоида смещённого по осям x y*/
//	EXPECT_TRUE(t.numb_of_iterations_match(expect_iterations_numb));
//}


int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	getchar();
	return 0;
}