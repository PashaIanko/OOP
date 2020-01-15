#include "pch.h"
#include <iostream>
#include "gtest\gtest.h"
#include "Matrix.h"
#include <chrono>

TEST(Ctor, init_list) {
	Matrix<int> m
	(
		{
		{1, 2, 3},
		{4, 5, 6},
		}
	);
	EXPECT_EQ(m.get_width(), 3);
	EXPECT_EQ(m.get_height(), 2);

	std::vector<int> row_0 = m.get_row(0);
	std::vector<int> row_1= m.get_row(1);
	std::vector<int> exp({ 1, 2, 3 });
	std::vector<int> row_1_exp({ 4, 5, 6 });
	EXPECT_EQ(row_0, exp);
	EXPECT_EQ(row_1, row_1_exp);

	EXPECT_EQ(m.get_column(0), std::vector<int>({ 1, 4 }));
	EXPECT_EQ(m.get_column(1), std::vector<int>({ 2, 5 }));
	EXPECT_EQ(m.get_column(2), std::vector<int>({ 3, 6 }));
}

TEST(ONE_THREAD_PLUS, simple_test) {
	Matrix<int> m
	(
		{
		{1, 2, 3},
		{4, 5, 6},
		}
	);

	Matrix<int> m2 = m;

	m = m + m2;
	EXPECT_EQ(m.get_width(), 3);
	EXPECT_EQ(m.get_height(), 2);

	std::vector<int> row_0 = m.get_row(0);
	std::vector<int> row_1 = m.get_row(1);
	std::vector<int> exp({ 2, 4, 6 });
	std::vector<int> row_1_exp({ 8, 10, 12 });
	EXPECT_EQ(row_0, exp);
	EXPECT_EQ(row_1, row_1_exp);

	EXPECT_EQ(m.get_column(0), std::vector<int>({ 2, 8 }));
	EXPECT_EQ(m.get_column(1), std::vector<int>({ 4, 10 }));
	EXPECT_EQ(m.get_column(2), std::vector<int>({ 6, 12 }));
}

TEST(MULTITHREAD_PLUS, simple_test) {
	Matrix<int> m
	(
		{
		{1, 2, 3},
		{4, 5, 6},
		}
	);

	Matrix<int> m2 = m;

	m = m.multhread_sum(&m2, 2);
	
	EXPECT_EQ(m.get_width(), 3);
	EXPECT_EQ(m.get_height(), 2);
		
	EXPECT_EQ(m.get_row(0), std::vector<int>({2, 4, 6}));
	EXPECT_EQ(m.get_row(1), std::vector<int>({ 8, 10, 12 }));
	EXPECT_EQ(m.get_column(0), std::vector<int>({ 2, 8 }));
	EXPECT_EQ(m.get_column(1), std::vector<int>({ 4, 10 }));
	EXPECT_EQ(m.get_column(2), std::vector<int>({ 6, 12 }));
}

TEST(MULTITHREAD_PLUS, threads_more_than_strings) {
	Matrix<int> m
	(
		{
		{1, 2, 3},
		}
	);
	Matrix<int> m2
	(
		{
		{-1, -2, -3},
		}
	);
	m = m.multhread_sum(&m2, 3);

	EXPECT_EQ(m.get_width(), 3);
	EXPECT_EQ(m.get_height(), 1);

	EXPECT_EQ(m.get_row(0), std::vector<int>({ 0, 0, 0 }));
	EXPECT_EQ(m.get_column(0), std::vector<int>({ 0 }));
	EXPECT_EQ(m.get_column(1), std::vector<int>({ 0}));
	EXPECT_EQ(m.get_column(2), std::vector<int>({ 0}));
}

TEST(MULTITHREAD_PLUS, different_strings_numb_for_threads) {
	Matrix<int> m
	(
		{
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, 9},
		{10, 11, 12},
		{13, 14, 15},
		}
	);
	Matrix<int> m2 = m;
	m = m.multhread_sum(&m2, 2);

	EXPECT_EQ(m.get_width(), 3);
	EXPECT_EQ(m.get_height(), 5);

	EXPECT_EQ(m.get_row(0), std::vector<int>({ 2, 4, 6 }));
	EXPECT_EQ(m.get_row(1), std::vector<int>({ 8, 10, 12 }));
	EXPECT_EQ(m.get_row(2), std::vector<int>({ 14, 16, 18 }));
	EXPECT_EQ(m.get_row(3), std::vector<int>({ 20, 22, 24 }));
	EXPECT_EQ(m.get_row(4), std::vector<int>({ 26, 28, 30 }));

}

TEST(MULTITHREAD_MULT, simple_test) {
	Matrix<int> m
	(
		{
		{1, 2, 0},
		}
	);
	Matrix<int> m2
	(
		{
		{2, 3},
		{1, 3},
		{0, 3},
		}
	);
	Matrix<int> expect
	(
		{ 
			{ 4, 9 }
		}
	);

	Matrix<int> m_res = m.multhread_multiply(&m2, 1);
	EXPECT_TRUE(m_res == expect);
	m_res = m.multhread_multiply(&m2, 2);
	EXPECT_TRUE(m_res == expect);
	m_res = m.multhread_multiply(&m2, 3);
	EXPECT_TRUE(m_res == expect);
	m_res = m.multhread_multiply(&m2, 4);
	EXPECT_TRUE(m_res == expect);
}

TEST(MULTITHREAD_MULT, 3_x_3_identical_operator) {
	Matrix<int> m
	(
		{
		{1, 2, 0},
		{1, 2, 0},
		{1, 2, 0},
		}
	);
	Matrix<int> m2
	(
		{
		{1, 0, 0},
		{0, 1, 0},
		{0, 0, 1},
		}
	);

	Matrix<int> m_res = m.multhread_multiply(&m2, 3);
	EXPECT_TRUE(m_res == m);
}

TEST(MULTITHREAD_MULT, 3_x_3_mult_3_x_7_identical_operator) {
	Matrix<int> m
	(
		{
		{1, 0, 0},
		{0, 1, 0},
		{0, 0, 1},
		}
	);
	Matrix<int> m2
	(
		{
		{1, 2, 3, 4, 5, 6, 7},
		{5, 6, 7, 8, 8, 8, 8},
		{2, 3, 3, 3, 4, 2, 9},
		}
	);

	Matrix<int> m_res = m.multhread_multiply(&m2, 3);
	EXPECT_TRUE(m_res == m2);
	m_res = m.multhread_multiply(&m2, 2);
	EXPECT_TRUE(m_res == m2);
	m_res = m.multhread_multiply(&m2, 1);
	EXPECT_TRUE(m_res == m2);
}

TEST(MULTITHREAD_MULT, 3_x_3_mult_3_x_2_identical_operator) {
	Matrix<int> m
	(
		{
		{1, 0, 0},
		{0, 1, 0},
		{0, 0, 1},
		}
	);
	Matrix<int> m2
	(
		{
		{1, 2},
		{5, 3},
		{2, 4},
		}
	);

	Matrix<int> m_res = m.multhread_multiply(&m2, 3);
	EXPECT_TRUE(m_res == m2);
	m_res = m.multhread_multiply(&m2, 2);
	EXPECT_TRUE(m_res == m2);
	m_res = m.multhread_multiply(&m2, 1);
	EXPECT_TRUE(m_res == m2);
}

TEST(MULTITHREAD_MULT, 11_x_11) {
	Matrix<int> m(11, 11, 1);
	Matrix<int> expect(11, 11, 11);
	
	Matrix<int> m_res = m.multhread_multiply(&m, 6);
	EXPECT_TRUE(m_res == expect);
}

TEST(MULTITHREAD_DET, 3_x_3_identical_operator) {
	Matrix<int> m
	(
		{
		{1, 0, 0},
		{0, 1, 0},
		{0, 0, 1},
		}
	);
	EXPECT_EQ(m.multhread_det(3), 1);
}

TEST(MULTITHREAD_DET, 3_x_3) {
	Matrix<int> m
	(
		{
		{1, 2, 3},
		{4, 5, 6},
		{7, 7, 9},
		}
	);
	EXPECT_EQ(m.multhread_det(3), -6);
	EXPECT_EQ(m.multhread_det(2), -6);
	EXPECT_EQ(m.multhread_det(1), -6);
}

TEST(MULTITHREAD_DET, 3_x_3_threads_more_than_columns) {
	Matrix<int> m
	(
		{
		{1, 2, 3},
		{4, 5, 6},
		{7, 7, 9},
		}
	);
	EXPECT_EQ(m.multhread_det(4), -6);
}

TEST(MULTITHREAD_DET, 4_x_4) {
	Matrix<int> m
	(
		{
		{0, 2, 3, 4},
		{5, 6, 7, 8},
		{9, 10, 11, 12},
		{13, 14, 15, 15},
		}
	);
	EXPECT_EQ(m.multhread_det(4), -4);
	EXPECT_EQ(m.multhread_det(3), -4);
	EXPECT_EQ(m.multhread_det(2), -4);
	EXPECT_EQ(m.multhread_det(1), -4);
}

TEST(CALC_FUNCTIONS_ONE_THREAD_DET, 3_x_3) {
	Matrix<int> m
	(
		{
		{1, 2, 3},
		{4, 5, 6},
		{7, 7, 9},
		}
	);
	EXPECT_EQ(CalcFunctions::simple_det(&m), -6);
}

TEST(CALC_FUNCTIONS_ONE_THREAD_DET, 4_x_4) {
	Matrix<int> m
	(
		{
		{0, 2, 3, 4},
		{5, 6, 7, 8},
		{9, 10, 11, 12},
		{13, 14, 15, 15},
		}
	);
	EXPECT_EQ(CalcFunctions::simple_det(&m), -4);
}

TEST(CALC_FUNCTIONS_ONE_THREAD_DET, 7_x_7) {
	Matrix<int> m
	(
		{
		{1, 0, 0, 0, 0, 8, 4},
		{0, 1, 0, 0, 0, 8, 5},
		{0, 0, 1, 0, 0, 8, 6},
		{0, 0, 0, 1, 0, 8, 7},
		{0, 7, 0, 0, 1, 0, 0},
		{0, 7, 0, 0, 0, 1, 0},
		{0, 7, 0, 0, 0, 0, 1},
		}
	);
	EXPECT_EQ(CalcFunctions::simple_det(&m), -90);
}

TEST(OPERATOR_PLUS, simple_test) {
	Matrix<int> m(1000, 1000, 1);
	m.enable_multithreading();
	Matrix<int> m_exp(1000, 1000, 2);
	Matrix<int> m2 = m + m;
	EXPECT_EQ(m2, m_exp);
}

TEST(OPERATOR_MINUS, simple_test) {
	Matrix<int> m(1000, 1000, 1);
	Matrix<int> m_exp(1000, 1000, 0);
	m.enable_multithreading();
	Matrix<int> m2 = m - m;
	EXPECT_EQ(m2, m_exp);
}

TEST(OPERATOR_MULT, simple_test) {
	Matrix<int> m(100, 50, 1);
	Matrix<int> m2(50, 100, 1);
	Matrix<int> m_exp(50, 50, 100);
	m.enable_multithreading();
	m2.enable_multithreading();
	Matrix<int> m_res = m * m2;
	EXPECT_EQ(m_res, m_exp);
}

TEST(MULTITHREAD_DET, 5_x_5_strings_more_than_threads) {
	Matrix<int> m
	(
		{
		{1, 4, 5, 1, 3 },
		{1, 1, 1, 1, 4 },
		{3, 4, 4, 4, 4 },
		{2, 1, 7, 6, 8 },
		{2, 1, 3, 5, 7 },
		}
	);
	int res = 195;
	EXPECT_EQ(m.multhread_det(4), res);
	EXPECT_EQ(m.multhread_det(3), res);
	EXPECT_EQ(m.multhread_det(2), res);
}


int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	getchar();
	return 0;
}

