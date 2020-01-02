#include "pch.h"
#include <iostream>
#include "gtest\gtest.h"
#include "Matrix.h"


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

TEST(PLUS_ONE_THREAD, simple_test) {
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


int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	getchar();
	return 0;
}

