#include "pch.h"
#include "Matrix.h"






static Matrix<int> investigation_matrix_500(500, 500, 1);
static Matrix<int> investigation_matrix_1000(1000, 1000, 1);
static Matrix<int> investigation_matrix_5000(5000, 5000, 1);
static Matrix<int> investigation_matrix_10000(10000, 10000, 1);
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
	auto start = std::chrono::high_resolution_clock::now();
	T det = matrix->multhread_det(threads_numb);
	auto end = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> diff = end - start;

	std::cout << "Investigation matrix[" << matrix->get_height()
		<< "][" << matrix->get_width() << "], "
		<< threads_numb << "threads took "
		<< diff.count() <<
		"tacts" << std::endl;
	len_result<T> result;
	result.res_det = det;
	result.duration = diff;
	return result;
}

template<typename T>
std::chrono::duration<double> investigate_sum(Matrix<T>* matrix, size_t threads_numb) {

	auto start = std::chrono::high_resolution_clock::now();
	Matrix<T> m = matrix->multhread_sum(matrix, threads_numb);
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start;

	std::cout << "Investigation matrix[" << matrix->get_height()
		<< "][" << matrix->get_width() << "], "
		<< threads_numb << "threads summ took "
		<< diff.count() <<
		"tacts" << std::endl;
	return diff;
}

template<typename T>
std::chrono::duration<double> investigate_mult(Matrix<T>* matrix_, size_t threads_numb) {
	Matrix<T> matrix = *matrix_;

	auto start = std::chrono::high_resolution_clock::now();
	Matrix<T> m = matrix.multhread_multiply(matrix_, threads_numb);
	auto end = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> diff = end - start;

	std::cout << "Investigation matrix[" << matrix.get_height()
		<< "][" << matrix.get_width() << "], "
		<< threads_numb << "threads multiply took "
		<< diff.count() <<
		"tacts" << std::endl;
	return diff;
}

TEST(MULTITHREAD_SUM_INVESTIGATION, investigation_500_x_500) {
	std::chrono::duration<double> dur;
	dur = investigate_sum(&investigation_matrix_500, 1);
	dur = investigate_sum(&investigation_matrix_500, 2);
	dur = investigate_sum(&investigation_matrix_500, 3);
	dur = investigate_sum(&investigation_matrix_500, 4);
	dur = investigate_sum(&investigation_matrix_500, 5);
	dur = investigate_sum(&investigation_matrix_500, 6);
	dur = investigate_sum(&investigation_matrix_500, 7);
	dur = investigate_sum(&investigation_matrix_500, 8);
	dur = investigate_sum(&investigation_matrix_500, 9);
	dur = investigate_sum(&investigation_matrix_500, 10);
}

TEST(MULTITHREAD_SUM_INVESTIGATION, investigation_1000_x_1000) {
	std::chrono::duration<double> dur;
	dur = investigate_sum(&investigation_matrix_1000, 1);
	dur = investigate_sum(&investigation_matrix_1000, 2);
	dur = investigate_sum(&investigation_matrix_1000, 3);
	dur = investigate_sum(&investigation_matrix_1000, 4);
	dur = investigate_sum(&investigation_matrix_1000, 5);
	dur = investigate_sum(&investigation_matrix_1000, 6);
	dur = investigate_sum(&investigation_matrix_1000, 7);
	dur = investigate_sum(&investigation_matrix_1000, 8);
	dur = investigate_sum(&investigation_matrix_1000, 9);
	dur = investigate_sum(&investigation_matrix_1000, 10);
}

TEST(MULTITHREAD_SUM_INVESTIGATION, investigation_5000_x_5000) {
	std::chrono::duration<double> dur;
	dur = investigate_sum(&investigation_matrix_5000, 1);
	dur = investigate_sum(&investigation_matrix_5000, 2);
	dur = investigate_sum(&investigation_matrix_5000, 3);
	dur = investigate_sum(&investigation_matrix_5000, 4);
	dur = investigate_sum(&investigation_matrix_5000, 5);
	dur = investigate_sum(&investigation_matrix_5000, 6);
	dur = investigate_sum(&investigation_matrix_5000, 7);
	dur = investigate_sum(&investigation_matrix_5000, 8);
	dur = investigate_sum(&investigation_matrix_5000, 9);
	dur = investigate_sum(&investigation_matrix_5000, 10);
}

TEST(MULTITHREAD_SUM_INVESTIGATION, investigation_250_x_250) {
	std::chrono::duration<double> dur;
	dur = investigate_sum(&investigation_matrix_250, 1);
	dur = investigate_sum(&investigation_matrix_250, 2);
	dur = investigate_sum(&investigation_matrix_250, 3);
}

TEST(MULTITHREAD_SUM_INVESTIGATION, investigation_100_x_100) {
	std::chrono::duration<double> dur;
	dur = investigate_sum(&investigation_matrix_100, 1);
	dur = investigate_sum(&investigation_matrix_100, 2);
	dur = investigate_sum(&investigation_matrix_100, 3);
}

TEST(MULTITHREAD_MULT_INVESTIGATION, investigation_100_x_100) {
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
	dur = investigate_mult(&investigation_matrix_500, 1);
	dur = investigate_mult(&investigation_matrix_500, 2);
	dur = investigate_mult(&investigation_matrix_500, 3);
	dur = investigate_mult(&investigation_matrix_500, 4);
	dur = investigate_mult(&investigation_matrix_500, 5);
	dur = investigate_mult(&investigation_matrix_500, 6);
}

TEST(MULTITHREAD_DET_INVESTIGATION, investigation_5_x_5) {
	Matrix<int> investigation_matrix(5, 5, 1);
	len_result<int> result = investigate_det(&investigation_matrix, 1);
	result = investigate_det(&investigation_matrix, 2);
	result = investigate_det(&investigation_matrix, 3);
	EXPECT_EQ(result.res_det, 0);
}

TEST(MULTITHREAD_DET_INVESTIGATION, investigation_6_x_6) {
	Matrix<int> investigation_matrix(5, 5, 1);
	len_result<int> result = investigate_det(&investigation_matrix, 1);
	result = investigate_det(&investigation_matrix, 2);
	result = investigate_det(&investigation_matrix, 3);
	EXPECT_EQ(result.res_det, 0);
}

TEST(MULTITHREAD_DET_INVESTIGATION, investigation_7_x_7) {
	Matrix<int> investigation_matrix(7, 7, 1);
	len_result<int> result = investigate_det(&investigation_matrix, 1);
	result = investigate_det(&investigation_matrix, 2);
	result = investigate_det(&investigation_matrix, 3);
	result = investigate_det(&investigation_matrix, 4);
	result = investigate_det(&investigation_matrix, 5);
	result = investigate_det(&investigation_matrix, 6);

	EXPECT_EQ(result.res_det, 0);


}

TEST(MULTITHREAD_DET_INVESTIGATION, investigation_8_x_8) {
	Matrix<int> investigation_matrix(8, 8, 1);
	len_result<int> result = investigate_det(&investigation_matrix, 1);
	result = investigate_det(&investigation_matrix, 2);
	result = investigate_det(&investigation_matrix, 3);
	result = investigate_det(&investigation_matrix, 4);
	result = investigate_det(&investigation_matrix, 5);
	result = investigate_det(&investigation_matrix, 6);
	EXPECT_EQ(result.res_det, 0);
}

TEST(MULTITHREAD_DET_INVESTIGATION, investigation_9_x_9) {
	Matrix<int> investigation_matrix(9, 9, 1);
	len_result<int> result = investigate_det(&investigation_matrix, 1);
	result = investigate_det(&investigation_matrix, 2);
	result = investigate_det(&investigation_matrix, 3);
	result = investigate_det(&investigation_matrix, 4);
	result = investigate_det(&investigation_matrix, 5);
	result = investigate_det(&investigation_matrix, 6);
	EXPECT_EQ(result.res_det, 0);
}

TEST(MULTITHREAD_DET_INVESTIGATION, investigation_10_x_10) {
	Matrix<int> investigation_matrix(10, 10, 1);
	len_result<int> result = investigate_det(&investigation_matrix, 1);
	result = investigate_det(&investigation_matrix, 2);
	result = investigate_det(&investigation_matrix, 3);
	result = investigate_det(&investigation_matrix, 4);
	result = investigate_det(&investigation_matrix, 5);
	result = investigate_det(&investigation_matrix, 6);
	EXPECT_EQ(result.res_det, 0);
}


int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	getchar();
	return 0;
}