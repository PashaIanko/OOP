#include "pch.h"
#include "gtest\gtest.h"
#include "sum_all.h"
#include "test_func.h"



TEST(SINGULAR, char_singular_value) {
	char a = 'a';
	std::string res = sum_all(a);
	std::string expect ("a");
	EXPECT_EQ(expect, res);
}

TEST(REGULAR, empty_int_v) {
	std::vector<int> v = {};
	EXPECT_TRUE(test_func(v, 0));
}

TEST(REGULAR, double_v)
{
	std::vector<double> v1 = { 1.1, 2.1, 3.1 };
	EXPECT_TRUE(test_func(v1, 6.3));
}

TEST(REGULAR, int_v)
{
	std::vector<int> v1 = { 1, 2, 3 };
	EXPECT_TRUE(test_func(v1, 6));
}

TEST(SINGULAR, int_singular_value) {
	int val = 5;
	int sum = sum_all(val);
	EXPECT_EQ(sum, val);
}

TEST(SINGULAR, double_singular_value) {
	double val = 5;
	double sum = sum_all(val);
	EXPECT_EQ(sum, val);
}

TEST(SINGULAR, float_singular_value) {
	float val = 5;
	float sum = sum_all(val);
	EXPECT_EQ(sum, val);
}

TEST(SINGULAR, short_singular_value) {
	short val = 5;
	long sum = sum_all(val);
	EXPECT_EQ(sum, 5);
}

TEST(SINGULAR, unsigned_int_singular_value) {
	unsigned short val = 5;
	unsigned long expect = 5;
	unsigned long sum = sum_all(val);
	EXPECT_EQ(sum, expect);
}

TEST(REGULAR, empty_double_v) {
	std::vector<double> v = {};
	EXPECT_TRUE(test_func(v, 0.0));
}

TEST(REGULAR, double_v_but_int_values) {
	std::vector<float> v = {1, 2, 3, 4, 5};
	EXPECT_TRUE(test_func(v, 15));
}

TEST(REGULAR, string_v) {
	const std::vector<std::string> v1 = { "a", "b", "c" };
	const std::string str = "abc";
	EXPECT_TRUE(test_func(v1, str));
}

TEST(REGULAR, empty_string_v) {
	std::vector<std::string> v = {};
	std::string res = sum_all(v);
	EXPECT_TRUE(res == "");
}

TEST(REGULAR, char_v) {
	const std::vector<char> v = {'a', 'b', 'c'};
	std::string expect = "abc";
	std::string res = sum_all(v);
	EXPECT_TRUE(res == expect);  
}

TEST(REGULAR, empty_char_v) {
	const std::vector<char> v = {};
	std::string expect = "";
	std::string res = sum_all(v);
	EXPECT_TRUE(res == expect);
}


 
int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	getchar();
	return 0;
}