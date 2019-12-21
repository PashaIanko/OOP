#include "pch.h"
#include <memory>
#include <iostream>
#include <sstream>
#include <istream>
#include "gtest\gtest.h"
#include "..\HookeJeeves\HookeJeeves.h"
#include "C_StyleStrategy.h"
#include "OOP_StyleStrategy.h"
#include "Ctor_Params.h"
#include "TestWrapper.h"
#include <vector>

using cur_strategy = OOP_StyleStrategy;//C_StyleStrategy;

TEST(first, run_old_algorithm) {
	const size_t VARS = 250;
	double RHO_BEGIN = 0.5;
	double EPSMIN = 1E-6;
	int IMAX = 5000;

	double	   startpt[VARS], endpt[VARS];
	int		   nvars, itermax;
	double	   rho, epsilon;
	int		   i, jj;

	/* starting guess for rosenbrock test function */
	nvars = 2;
	startpt[0] = -1.2;
	startpt[1] = 1.0;

	itermax = IMAX;
	rho = RHO_BEGIN;
	epsilon = EPSMIN;


	Ctor_Params params
	{
		nvars,
		startpt,
		endpt,
		rho,
		epsilon,
		itermax
	};

	TestWrapper<cur_strategy> t(params);
	t.calc();
	size_t expect_iterations_numb = 19;
	EXPECT_TRUE(t.minimum_match({ 1.0, 1.0 }));
	EXPECT_TRUE(t.numb_of_iterations_match(expect_iterations_numb));
}


int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	getchar();
	return 0;
}