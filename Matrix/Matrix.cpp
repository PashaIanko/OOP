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

	m = m.multhread_sum(&m, &m2, 2);
	
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
	m = m.multhread_sum(&m, &m2, 3);

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
	m = m.multhread_sum(&m, &m2, 2);

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

	Matrix<int> m_res = m.multhread_multiply(&m, &m2, 1);
	EXPECT_TRUE(m_res == expect);
	m_res = m.multhread_multiply(&m, &m2, 2);
	EXPECT_TRUE(m_res == expect);
	m_res = m.multhread_multiply(&m, &m2, 3);
	EXPECT_TRUE(m_res == expect);
	m_res = m.multhread_multiply(&m, &m2, 4);
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

	Matrix<int> m_res = m.multhread_multiply(&m, &m2, 3);
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

	Matrix<int> m_res = m.multhread_multiply(&m, &m2, 3);
	EXPECT_TRUE(m_res == m2);
	m_res = m.multhread_multiply(&m, &m2, 2);
	EXPECT_TRUE(m_res == m2);
	m_res = m.multhread_multiply(&m, &m2, 1);
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

	Matrix<int> m_res = m.multhread_multiply(&m, &m2, 3);
	EXPECT_TRUE(m_res == m2);
	m_res = m.multhread_multiply(&m, &m2, 2);
	EXPECT_TRUE(m_res == m2);
	m_res = m.multhread_multiply(&m, &m2, 1);
	EXPECT_TRUE(m_res == m2);
}

TEST(MULTITHREAD_MULT, 11_x_11) {
	Matrix<int> m(11, 11, 1);
	Matrix<int> expect(11, 11, 11);
	
	Matrix<int> m_res = m.multhread_multiply(&m, &m, 6);
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


/*TEST(MULTITHREAD_DET, 10_x_10) {
	Matrix<int> m
	(
		{
		{1, 4, 5, 10, -3, 2, 1, 1, 1, 1},
		{1, 1, 1, 1, 4, 5, 6, 7, 9, 0},
		{3, 4, 4, 4, 4, 5, 6, 8, 0, 0},
		{2, 1, 7, 6, 8, 9, 10, 3, 2, 1},
		{2, 1, 3, 5, 7, 8, 4, 4, 4, 4},
		{1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
		{2, 1, 4, 3, 6, 7, 7, 2, 4, 25},
		{1, 4, 2, 3, 5, 6, 2, 1, 8, 9},
		{0, 1, 5, 3, 2, 6, 5, 4, 7, 8},
		{1, 4, 5, 2, 0, 9, 10, 7, 8, 2}
		}
	);
	int res = -5208;
	EXPECT_EQ(CalcFunctions::simple_det(&m), res);
	//EXPECT_EQ(m.multhread_det(4), res);
	//EXPECT_EQ(m.multhread_det(3), res);
	//EXPECT_EQ(m.multhread_det(2), res);
	//EXPECT_EQ(m.multhread_det(1), res);
}*/







static Matrix<int> investigation_matrix_500(500, 500, 1);
static Matrix<int> investigation_matrix_1000(1000, 1000, 1);
static Matrix<int> investigation_matrix_5000(5000, 5000, 1);
//static Matrix<int> investigation_matrix_10000(10000, 10000, 1);
static Matrix<int> investigation_matrix_250(250, 250, 1);
static Matrix<int> investigation_matrix_100(100, 100, 1);

template<typename T>
struct len_result {
	T res_det;
	std::chrono::duration<double> duration;
};

template<typename T>
len_result<T> investigate_det(const Matrix<T>* matrix, size_t threads_numb)
{
	std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
	T det = matrix->multhread_det(threads_numb);
	std::chrono::duration<double> dur = std::chrono::system_clock::now() - start;
	std::cout << "Investigation matrix[" << matrix->get_height()
		<< "][" << matrix->get_width() << "], "
		<< threads_numb << "threads took "
		<< dur.count() <<
		"tacts" << std::endl;
	len_result<T> result;
	result.res_det = det;
	result.duration = dur;
	return result;
}

template<typename T>
std::chrono::duration<double> investigate_sum(Matrix<T>* matrix, size_t threads_numb) {
	std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
	Matrix<T> m = matrix->multhread_sum(matrix, matrix, threads_numb);
	std::chrono::duration<double> dur = std::chrono::system_clock::now() - start;
	std::cout << "Investigation matrix[" << matrix->get_height()
		<< "][" << matrix->get_width() << "], "
		<< threads_numb << "threads summ took "
		<< dur.count() <<
		"tacts" << std::endl;
	return dur;
}

template<typename T>
std::chrono::duration<double> investigate_mult(Matrix<T>* matrix_, size_t threads_numb) {
	Matrix<T> matrix = *matrix_;
	std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
	Matrix<T> m = matrix.multhread_multiply(&matrix, matrix_, threads_numb); 
	std::chrono::duration<double> dur = std::chrono::system_clock::now() - start;
	std::cout << "Investigation matrix[" << matrix.get_height()
		<< "][" << matrix.get_width() << "], "
		<< threads_numb << "threads multiply took "
		<< dur.count() <<
		"tacts" << std::endl;
	return dur;
}

//TEST(MULTITHREAD_SUM_INVESTIGATION, investigation_500_x_500) {
//	std::chrono::duration<double> dur;
//	dur = investigate_sum(&investigation_matrix_500, 1);
//	dur = investigate_sum(&investigation_matrix_500, 2);
//	dur = investigate_sum(&investigation_matrix_500, 3);
//	dur = investigate_sum(&investigation_matrix_500, 4);
//	dur = investigate_sum(&investigation_matrix_500, 5);
//	dur = investigate_sum(&investigation_matrix_500, 6);
//	dur = investigate_sum(&investigation_matrix_500, 7);
//	dur = investigate_sum(&investigation_matrix_500, 8);
//	dur = investigate_sum(&investigation_matrix_500, 9);
//	dur = investigate_sum(&investigation_matrix_500, 10);
//}
//
//TEST(MULTITHREAD_SUM_INVESTIGATION, investigation_1000_x_1000) {
//	std::chrono::duration<double> dur;
//	dur = investigate_sum(&investigation_matrix_1000, 1);
//	dur = investigate_sum(&investigation_matrix_1000, 2);
//	dur = investigate_sum(&investigation_matrix_1000, 3);
//	dur = investigate_sum(&investigation_matrix_1000, 4);
//	dur = investigate_sum(&investigation_matrix_1000, 5);
//	dur = investigate_sum(&investigation_matrix_1000, 6);
//	dur = investigate_sum(&investigation_matrix_1000, 7);
//	dur = investigate_sum(&investigation_matrix_1000, 8);
//	dur = investigate_sum(&investigation_matrix_1000, 9);
//	dur = investigate_sum(&investigation_matrix_1000, 10);
//}
//
//TEST(MULTITHREAD_SUM_INVESTIGATION, investigation_5000_x_5000) {
//	std::chrono::duration<double> dur;
//	dur = investigate_sum(&investigation_matrix_5000, 1);
//	dur = investigate_sum(&investigation_matrix_5000, 2);
//	dur = investigate_sum(&investigation_matrix_5000, 3);
//	dur = investigate_sum(&investigation_matrix_5000, 4);
//	dur = investigate_sum(&investigation_matrix_5000, 5);
//	dur = investigate_sum(&investigation_matrix_5000, 6);
//	dur = investigate_sum(&investigation_matrix_5000, 7);
//	dur = investigate_sum(&investigation_matrix_5000, 8);
//	dur = investigate_sum(&investigation_matrix_5000, 9);
//	dur = investigate_sum(&investigation_matrix_5000, 10);
//}
//
//TEST(MULTITHREAD_SUM_INVESTIGATION, investigation_250_x_250) {
//	std::chrono::duration<double> dur;
//	dur = investigate_sum(&investigation_matrix_250, 1);
//	dur = investigate_sum(&investigation_matrix_250, 2);
//	dur = investigate_sum(&investigation_matrix_250, 3);
//}
//
//TEST(MULTITHREAD_SUM_INVESTIGATION, investigation_100_x_100) {
//	std::chrono::duration<double> dur;
//	dur = investigate_sum(&investigation_matrix_100, 1);
//	dur = investigate_sum(&investigation_matrix_100, 2);
//	dur = investigate_sum(&investigation_matrix_100, 3);
//}

/*TEST(MULTITHREAD_MULT_INVESTIGATION, investigation_100_x_100) {
	std::chrono::duration<double> dur;
	dur = investigate_mult(&investigation_matrix_100, 1);
	dur = investigate_mult(&investigation_matrix_100, 2);
	dur = investigate_mult(&investigation_matrix_100, 3);
	dur = investigate_mult(&investigation_matrix_100, 4);
	dur = investigate_mult(&investigation_matrix_100, 5);
	dur = investigate_mult(&investigation_matrix_100, 6);
}

TEST(MULTITHREAD_MULT_INVESTIGATION, investigation_250_x_250) {
	std::chrono::duration<double> dur;
	dur = investigate_mult(&investigation_matrix_250, 1);
	dur = investigate_mult(&investigation_matrix_250, 2);
	dur = investigate_mult(&investigation_matrix_250, 3);
	dur = investigate_mult(&investigation_matrix_250, 4);
	dur = investigate_mult(&investigation_matrix_250, 5);
	dur = investigate_mult(&investigation_matrix_250, 6);
}

TEST(MULTITHREAD_MULT_INVESTIGATION, investigation_1000_x_1000) {
	std::chrono::duration<double> dur;
	dur = investigate_mult(&investigation_matrix_1000, 1);
	dur = investigate_mult(&investigation_matrix_1000, 2);
	dur = investigate_mult(&investigation_matrix_1000, 3);
	dur = investigate_mult(&investigation_matrix_1000, 4);
	dur = investigate_mult(&investigation_matrix_1000, 5);
	dur = investigate_mult(&investigation_matrix_1000, 6);
}

TEST(MULTITHREAD_MULT_INVESTIGATION, investigation_500_x_500) {
	std::chrono::duration<double> dur;
	//dur = investigate_mult(&investigation_matrix_500, 1);
	//dur = investigate_mult(&investigation_matrix_500, 2);
	dur = investigate_mult(&investigation_matrix_500, 3);
	dur = investigate_mult(&investigation_matrix_500, 4);
	dur = investigate_mult(&investigation_matrix_500, 5);
	dur = investigate_mult(&investigation_matrix_500, 6);
}*/

//TEST(MULTITHREAD_DET_INVESTIGATION, investigation_5_x_5) {
//	Matrix<int> investigation_matrix(5, 5, 1);
//	len_result<int> result = investigate_det(&investigation_matrix, 1);
//	result = investigate_det(&investigation_matrix, 2);
//	result = investigate_det(&investigation_matrix, 3);
//	EXPECT_EQ(result.res_det, 0);
//}
//TEST(MULTITHREAD_DET_INVESTIGATION, investigation_7_x_7) {
//	Matrix<int> investigation_matrix(7, 7, 1);
//	//len_result<int> result = investigate_det(&investigation_matrix, 1);
//	//result = investigate_det(&investigation_matrix, 2);
//	//result = investigate_det(&investigation_matrix, 3);
//	len_result<int> result = investigate_det(&investigation_matrix, 1);
//	result = investigate_det(&investigation_matrix, 2);
//	result = investigate_det(&investigation_matrix, 3);
//	result = investigate_det(&investigation_matrix, 4);
//	result = investigate_det(&investigation_matrix, 5);
//	result = investigate_det(&investigation_matrix, 6);
//
//	EXPECT_EQ(result.res_det, 0);
//
//
//}
//
//TEST(MULTITHREAD_DET_INVESTIGATION, investigation_8_x_8) {
//	Matrix<int> investigation_matrix(8, 8, 1);
//	len_result<int> result = investigate_det(&investigation_matrix, 1);
//	result = investigate_det(&investigation_matrix, 2);
//	result = investigate_det(&investigation_matrix, 3);
//	result = investigate_det(&investigation_matrix, 4);
//	result = investigate_det(&investigation_matrix, 5);
//	result = investigate_det(&investigation_matrix, 6);
//	EXPECT_EQ(result.res_det, 0);
//}
//
//TEST(MULTITHREAD_DET_INVESTIGATION, investigation_9_x_9) {
//	Matrix<int> investigation_matrix(9, 9, 1);
//	len_result<int> result = investigate_det(&investigation_matrix, 1);
//	result = investigate_det(&investigation_matrix, 2);
//	result = investigate_det(&investigation_matrix, 3);
//	result = investigate_det(&investigation_matrix, 4);
//	result = investigate_det(&investigation_matrix, 5);
//	result = investigate_det(&investigation_matrix, 6);
//	EXPECT_EQ(result.res_det, 0);
//}



int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	getchar();
	return 0;
}

