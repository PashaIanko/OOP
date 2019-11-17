#include "pch.h"
#include "gtest\gtest.h"
#include <list>
#include "..\Variant\Variant.h"
#include <variant>


template<typename... Ts>
class TestHelper {
public:
	TestHelper(Variant<Ts...>* v) : v_ptr(v) {};
	size_t get_v_data_size() { return (v_ptr->get_data_size()); }

	template<typename T>
	T get_value() {
		T* val = static_cast<T*>(v_ptr->value);
		return *val;
	}

	Types get_cur_type() {
		return v_ptr->current_type;
	}

private:
	Variant<Ts...>* v_ptr;
};

TEST(CONSTRUCTOR, default_ctor_OK) {
	Variant<int, double, float> v2;
}

TEST(CONSTRUCTOR, T_ctor_one_of_types_OK) {
	int y = 6;
	float f = 7.7f;
	Variant<int, double> v3(y);
	/*Variant<int, double> v4(f); //not compiled*/

}

TEST(CONSTRUCTOR, string_ctor) {
	std::string s("abcdef");
	Variant<int, std::string> v(s);
	
}

TEST(CONSTRUCTOR, string_ctor_double_type_is_of_higher_size_than_string) {
	std::string s("abc");
	Variant<double, std::string> v(s); /*expect max_size == 8*/
	TestHelper<double, std::string> h(&v);
	size_t i = h.get_v_data_size();
	EXPECT_EQ(i, 28);
}

TEST(CONSTRUCTOR, correct_max_size_calc) {
	Variant<char, int, double> v;
	TestHelper<char, int, double> h(&v);
	size_t max_size = h.get_v_data_size();
	EXPECT_EQ(max_size, sizeof(double));
}

TEST(CONSTRUCTOR, correct_max_size_one_type) {
	Variant<char> v;
	TestHelper<char> h(&v);
	EXPECT_EQ(h.get_v_data_size(), sizeof(char));
}

TEST(TO_TYPE, to_int) {
	int i = 0;
	bool res = true;
	Variant<int> v(i);
	int i_ = v.ToInt(&res);
	EXPECT_TRUE(res);
	EXPECT_EQ(i_, 0);
}

TEST(TO_TYPE, to_int_) {
	int i = 5;
	bool res = true;
	Variant<int> v(i);
	int i_ = v.ToInt(&res);
	EXPECT_TRUE(res);
	EXPECT_EQ(i_, 5);
}

TEST(TO_TYPE, to_int_another_val) {
	int i = 5;
	bool res = true;
	Variant<int> v(i);
	int i_ = v.ToInt(&res);
	EXPECT_TRUE(res);
	EXPECT_EQ(i_, 5);
}

TEST(TO_INT, double_val) {
	double i = 5.276287;
	bool res = true;
	Variant<int, double> v(i);
	int i_ = v.ToInt(&res);
	EXPECT_TRUE(res);
	EXPECT_EQ(i_, 5);
}

TEST(TO_INT, float_val) {
	float i = 5.27f;
	bool res = true;
	Variant<int, float> v(i);
	int i_ = v.ToInt(&res);
	EXPECT_TRUE(res);
	EXPECT_EQ(i_, 5);
}

TEST(TO_INT, str_val) {
	std::string i ("abs");
	bool res = true;
	Variant<int, std::string> v(i);
	int i_ = v.ToInt(&res);
	EXPECT_FALSE(res);
	EXPECT_EQ(i_, -1);
}

TEST(TO_INT, char_val) {
	char i = '5';
	bool res = true;
	Variant<int, char> v(i);
	int i_ = v.ToInt(&res);
	EXPECT_TRUE(res);
	EXPECT_EQ(i_, 5);
}

TEST(TO_DOUBLE, double_val) {
	double i = 5.276287;
	bool res = true;
	Variant<int, double> v(i);
	double i_ = v.ToDouble(&res);
	EXPECT_TRUE(res);
	EXPECT_NEAR(i_, i, 0.0001);
}

TEST(TO_DOUBLE, float_val) {
	float i = 5.27f;
	bool res = true;
	Variant<int, float> v(i);
	double i_ = v.ToDouble(&res);
	EXPECT_TRUE(res);
	EXPECT_DOUBLE_EQ(i_, i);
}

TEST(TO_DOUBLE, str_val) {
	std::string i("5.78453");
	double expect = 5.78453;
	bool res = true;
	Variant<int, std::string> v(i);
	double i_ = v.ToDouble(&res);
	EXPECT_TRUE(res);
	EXPECT_NEAR(expect, i_, 0.0001);
}

TEST(TO_DOUBLE, char_val) {
	char i = '5';
	bool res = true;
	Variant<int, char> v(i);
	double i_ = v.ToDouble(&res);
	EXPECT_TRUE(res);
	EXPECT_DOUBLE_EQ(i_, 5);
}

TEST(TO_FLOAT, double_val) {
	double i = 5.276287;
	bool res = true;
	Variant<float, double> v(i);
	float i_ = v.ToFloat(&res);
	EXPECT_TRUE(res);

	EXPECT_NEAR(i_, i, 0.0001);
}

TEST(TO_FLOAT, float_val) {
	float i = 5.27f;
	bool res = true;
	Variant<int, float> v(i);
	float i_ = v.ToFloat(&res);
	EXPECT_TRUE(res);
	EXPECT_FLOAT_EQ(i_, i);
}

TEST(TO_FLOAT, str_val) {
	std::string i("5.78453");
	float expect = 5.78453f;
	bool res = true;
	Variant<int, std::string> v(i);
	float i_ = v.ToFloat(&res);
	EXPECT_TRUE(res);
	EXPECT_NEAR(expect, i_, 0.0001);
}

TEST(TO_FLOAT, char_val) {
	char i = '5';
	bool res = true;
	Variant<int, char> v(i);
	float i_ = v.ToFloat(&res);
	EXPECT_TRUE(res);
	EXPECT_FLOAT_EQ(i_, 5.0f);
}


TEST(TO_STRING, double_val) {
	double i = 5.276287;
	bool res = true;
	Variant<float, double> v(i);
	std::string str = v.ToString(&res);
	double i_ = std::stod(str);
	
	EXPECT_TRUE(res);
	EXPECT_NEAR(i_, i, 0.0001);
}

TEST(TO_STRING, float_val) {
	float i = 5.27f;
	bool res = true;
	Variant<int, float> v(i);
	std::string str = v.ToString(&res);
	float i_ = std::stof(str);
	
	EXPECT_TRUE(res);
	EXPECT_FLOAT_EQ(i_, i);
}

TEST(TO_STRING, str_val) {
	std::string i("5.78453");
	
	bool res = true;
	Variant<int, std::string> v(i);
	std::string i_ = v.ToString(&res);
	EXPECT_TRUE(res);
	EXPECT_EQ(i, i_);
}

TEST(TO_STRING, char_val) {
	char i = '5';
	bool res = true;
	Variant<int, char> v(i);
	std::string i_ = v.ToString(&res);
	std::string expect("5");
	EXPECT_TRUE(res);
	EXPECT_EQ(i_, expect);
}


TEST(TO_CHAR, double_val) {
	double i = 5.276287;
	bool res = true;
	Variant<float, double> v(i);
	char ch = v.ToChar(&res);
	
	EXPECT_FALSE(res);
	EXPECT_EQ(ch, '0');
}

TEST(TO_CHAR, float_val) {
	float i = 5.27f;
	bool res = true;
	Variant<int, float> v(i);
	char ch = v.ToChar(&res);
	
	EXPECT_FALSE(res);
	EXPECT_EQ(ch, '0');
}

TEST(TO_CHAR, long_string) {
	std::string i("5.78453");

	bool res = true;
	Variant<int, std::string> v(i);
	char ch = v.ToChar(&res);
	EXPECT_FALSE(res);
	EXPECT_EQ(ch, '0');
}

TEST(TO_CHAR, one_numb_string) {
	std::string i("5");

	bool res = true;
	Variant<int, std::string> v(i);
	char ch = v.ToChar(&res);
	EXPECT_TRUE(res);
	EXPECT_EQ(ch, '5');
}

TEST(TO_CHAR, one_letter_string) {
	std::string i("a");

	bool res = true;
	Variant<int, std::string> v(i);
	char ch = v.ToChar(&res);
	EXPECT_TRUE(res);
	EXPECT_EQ(ch, 'a');
}

TEST(TO_CHAR, char_val) {
	char i = '5';
	bool res = true;
	Variant<int, char> v(i);
	char ch = v.ToChar(&res);
	
	EXPECT_TRUE(res);
	EXPECT_EQ(ch, '5');
}

TEST(CAN_CONVERT, double_to_int) {
	int i = 5;
	Variant<int, double> v(i);
	const double y = 3.3;
	bool res = v.CanConvert(y);  
	EXPECT_TRUE(res);
}

TEST(CAN_CONVERT, char_to_int) {
	int i = 5;
	Variant<int, double> v(i);
	const char y = 'a';
	bool res = v.CanConvert(y);  
	EXPECT_TRUE(res);
}

TEST(CAN_CONVERT, float_to_int) {
	int i = 5;
	Variant<int, double> v(i);
	const float y = 5.5f;
	bool res = v.CanConvert(y);  
	EXPECT_TRUE(res);
}

TEST(CAN_CONVERT, string_to_int) {
	int i = 5;
	Variant<int, double> v(i);
	const std::string  y = "ab";
	bool res = v.CanConvert(y); 
	EXPECT_FALSE(res);
}

TEST(CAN_CONVERT, int_to_int) {
	int i = 5;
	Variant<int, double> v(i);
	const int  y = 5;
	bool res = v.CanConvert(y);  
	EXPECT_TRUE(res);
}

TEST(CAN_CONVERT, double_to_float) {
	float i = 5.0f;
	Variant<float, double> v(i);
	const double y = 3.3;
	bool res = v.CanConvert(y);  
	EXPECT_TRUE(res);
}

TEST(CAN_CONVERT, char_to_float) {
	float i = 5.73f;
	Variant<float, double> v(i);
	const char y = 'a';
	bool res = v.CanConvert(y);  
	EXPECT_TRUE(res);
}

TEST(CAN_CONVERT, float_to_float) {
	float i = 5.0f;
	Variant<float, double> v(i);
	const float y = 5.5f;
	bool res = v.CanConvert(y);  
	EXPECT_TRUE(res);
}

TEST(CAN_CONVERT, string_to_float) {
	float i = 5.0f;
	Variant<float, double> v(i);
	const std::string  y = "ab";
	bool res = v.CanConvert(y);  
	EXPECT_FALSE(res);
}

TEST(CAN_CONVERT, int_to_float) {
	float i = 5.0f;
	Variant<float, double> v(i);
	const int  y = 5;
	bool res = v.CanConvert(y);  
	EXPECT_TRUE(res);
}


TEST(CAN_CONVERT, double_to_double) {
	double i = 5.047634;
	Variant<float, double> v(i);
	const double y = 3.3;
	bool res = v.CanConvert(y);  
	EXPECT_TRUE(res);
}

TEST(CAN_CONVERT, char_to_double) {
	double i = 5.7334;
	Variant<float, double> v(i);
	const char y = 'a';
	bool res = v.CanConvert(y);  
	EXPECT_TRUE(res);
}

TEST(CAN_CONVERT, float_to_double) {
	double i = 5.0345;
	Variant<float, double> v(i);
	const float y = 5.5f;
	bool res = v.CanConvert(y);  
	EXPECT_TRUE(res);
}

TEST(CAN_CONVERT, string_to_double) {
	double i = 5.0234;
	Variant<float, double> v(i);
	const std::string  y = "ab";
	bool res = v.CanConvert(y);  
	EXPECT_FALSE(res);
}

TEST(CAN_CONVERT, int_to_double) {
	double i = 5.4587;
	Variant<char, double> v(i);
	const int  y = 5;
	bool res = v.CanConvert(y);  
	EXPECT_TRUE(res);
}

TEST(CAN_CONVERT, double_to_char) {
	char i = 'a';
	Variant<char, double> v(i);
	const double y = 3.3;
	bool res = v.CanConvert(y);  
	EXPECT_TRUE(res);
}

TEST(CAN_CONVERT, char_to_char) {
	char i = 'a';
	Variant<char, double> v(i);
	const char y = 'a';
	bool res = v.CanConvert(y);  
	EXPECT_TRUE(res);
}

TEST(CAN_CONVERT, float_to_char) {
	char i = 'a';
	Variant<char, double> v(i);
	const float y = 5.5f;
	bool res = v.CanConvert(y);  
	EXPECT_TRUE(res);
}

TEST(CAN_CONVERT, string_to_char) {
	char i = 'a';
	Variant<char, double> v(i);
	const std::string  y = "ab";
	bool res = v.CanConvert(y);  
	EXPECT_FALSE(res);
}

TEST(CAN_CONVERT, int_to_char) {
	char i = 'a';
	Variant<char, double> v(i);
	const int  y = 5;
	bool res = v.CanConvert(y);  
	EXPECT_TRUE(res);
}


TEST(CAN_CONVERT, double_to_string) {
	std::string i("abc");
	Variant<std::string, double> v(i);
	const double y = 3.3;
	bool res = v.CanConvert(y);  
	EXPECT_FALSE(res);
}

TEST(CAN_CONVERT, char_to_string) {
	std::string i("abc");
	Variant<std::string, double> v(i);
	const char y = 'a';
	bool res = v.CanConvert(y);  
	EXPECT_FALSE(res);
}

TEST(CAN_CONVERT, float_to_string) {
	std::string i("abc");
	Variant<std::string, double> v(i);
	const float y = 5.5f;
	bool res = v.CanConvert(y);  
	EXPECT_FALSE(res);
}

TEST(CAN_CONVERT, string_to_string) {
	std::string i("abc");
	Variant<std::string, double> v(i);
	const std::string  y = "ab";
	bool res = v.CanConvert(y);  
	EXPECT_TRUE(res);
}

TEST(CAN_CONVERT, int_to_string) {
	std::string i("abc");
	Variant<std::string, double> v(i);
	const int  y = 5;
	bool res = v.CanConvert(y);  
	EXPECT_FALSE(res);
}

TEST(SET_VALUE, int_set) {
	Variant<int, double> v;
	TestHelper<int, double> h(&v);
	const int d = 5;
	v.SetValue(d);
	EXPECT_EQ(h.get_value<int>(), 5);
}

TEST(SET_VALUE, int_double_set) {
	Variant<int, double> v;
	TestHelper<int, double> h(&v);
	int i = 5;
	double d = 5.34289;
	v.SetValue(d);
	EXPECT_EQ(h.get_value<double>(), d);
	v.SetValue(i);
	EXPECT_EQ(h.get_value<int>(), i);
}

TEST(SET_VALUE, char_float_int_set) {
	Variant<int, float, char> v;
	TestHelper<int, float, char> h(&v);
	int i = 5;
	float d = 5.342f;
	char c = 'a';
	v.SetValue(d);
	EXPECT_EQ(h.get_value<float>(), d);
	v.SetValue(i);
	EXPECT_EQ(h.get_value<int>(), i);
	v.SetValue(c);
	EXPECT_EQ(h.get_value<char>(), c);
}

TEST(SET_VALUE, string_char_int_set) {
	Variant<int, std::string, char> v;
	TestHelper<int, std::string, char> h(&v);
	int i = 5;
	std::string str("abc");
	char c = 'a';
	v.SetValue(str);
	EXPECT_EQ(h.get_value<std::string>(), str);
	v.SetValue(i);
	EXPECT_EQ(h.get_value<int>(), i);
	v.SetValue(c);
	EXPECT_EQ(h.get_value<char>(), c);
}

TEST(OPERATOR_EQ_EQ, two_empty_variants) {
	Variant<int, std::string, char> v;
	Variant<int, std::string, char> v_;
	EXPECT_TRUE(v == v_);
}

TEST(OPERATOR_EQ_EQ, empty_variants_all_args) {
	Variant<int, std::string, char, double, float> v;
	Variant<int, std::string, char, double, float> v_;
	EXPECT_TRUE(v == v_);
}

TEST(OPERATOR_EQ_EQ, int_double_vs_set_values) {
	int i = 5;
	Variant<int, double> v(i);
	Variant<int, double> v_(i);
	EXPECT_TRUE(v == v_);
}

TEST(OPERATOR_EQ_EQ, int_double_vs_set_double_value) {
	double d = 5.23476234;
	Variant<int, double> v(d);
	Variant<int, double> v_(d);
	EXPECT_TRUE(v == v_);
}

TEST(OPERATOR_EQ_EQ, self_eq) {
	double d = 5.23476234;
	Variant<int, double> v(d);
	EXPECT_TRUE(v == v);
}

TEST(OPERATOR_EQ_EQ, int_double_vs_set_double_value_slight_difference) {
	double d = 5.23476234;
	double d_ = d + 0.000001;
	Variant<int, double> v(d);
	Variant<int, double> v_(d_);
	EXPECT_FALSE(v == v_);
}

TEST(OPERATOR_EQ_EQ, char_values) {
	char c = 'a';
	Variant<int, char> v(c);
	Variant<int, char> v_(c);
	EXPECT_TRUE(v == v_);
}

TEST(OPERATOR_EQ_EQ, string_values) {
	std::string c("abc");
	Variant<std::string, char> v(c);
	Variant<std::string, char> v_(c);
	EXPECT_TRUE(v == v_);
}

TEST(OPERATOR_EQ, self_equalize) {
	std::string c("abc");
	Variant<std::string, char> v(c);
	TestHelper<std::string, char>h (&v);
	v = v;
	EXPECT_EQ( h.get_value<std::string>(), c);
}

TEST(OPERATOR_EQ, int_double_call_operator) {
	double d = 5.2587;
	char ch = 'a';
	Variant<double, char> v(d);
	Variant<double, char> v_(ch);

	TestHelper<double, char>h(&v_);

	/*before*/
	EXPECT_EQ(h.get_value<char>(), ch);
	EXPECT_EQ(h.get_cur_type(), char_);
	EXPECT_FALSE(v == v_);

	v_ = v;
	/*after*/
	EXPECT_EQ(h.get_value<double>(), d);
	EXPECT_EQ(h.get_cur_type(), double_);
	EXPECT_TRUE(v == v_);
}

TEST(OPERATOR_EQ, both_constructed_call_operator) {
	int i = 5;
	char ch = 'a';
	Variant<int, char> v(i);
	Variant<int, char> v_(ch);

	TestHelper<int, char>h(&v_);

	/*before*/
	EXPECT_EQ(h.get_value<char>(), ch);
	EXPECT_EQ(h.get_cur_type(), char_);
	EXPECT_FALSE(v == v_);

	v_ = v;
	/*after*/
	EXPECT_EQ(h.get_value<int>(), i);
	EXPECT_EQ(h.get_cur_type(), int_);
	EXPECT_TRUE(v == v_);

}

TEST(MOVE_CONSTRUCTOR, int_move_ctor) {

	Variant<int, char> v(5);
	TestHelper<int, char>h(&v);
	EXPECT_EQ(h.get_value<int>(), 5);
	EXPECT_EQ(h.get_cur_type(), int_);
}

TEST(MOVE_CONSTRUCTOR, char_move_ctor) {

	Variant<int, char> v('a');
	TestHelper<int, char>h(&v);
	EXPECT_EQ(h.get_value<char>(), 'a');
	EXPECT_EQ(h.get_cur_type(), char_);
}

TEST(MOVE_CONSTRUCTOR, double_move_ctor) {

	Variant<int, double> v(5.7843);
	TestHelper<int, double>h(&v);
	EXPECT_EQ(h.get_value<double>(), 5.7843);
	EXPECT_EQ(h.get_cur_type(), double_);
}

TEST(MOVE_CONSTRUCTOR, float_move_ctor) {

	Variant<float, double> v(5.7843f);
	TestHelper<float, double>h(&v);
	EXPECT_EQ(h.get_value<float>(), 5.7843f);
	EXPECT_EQ(h.get_cur_type(), float_);
}

TEST(OPERATOR_EQ_SET_VALUE, set_int) {
	Variant<int>v;
	v = 5;
	
	TestHelper<int>h(&v);
	EXPECT_EQ(h.get_value<int>(), 5);
	EXPECT_EQ(h.get_cur_type(), int_);
}

TEST(OPERATOR_EQ_SET_VALUE, set_float) {
	Variant<float>v;
	v = 5.453f;

	TestHelper<float>h(&v);
	EXPECT_EQ(h.get_value<float>(), 5.453f);
	EXPECT_EQ(h.get_cur_type(), float_);
}

TEST(OPERATOR_EQ_SET_VALUE, set_double) {
	Variant<double>v;
	v = 5.453354;

	TestHelper<double>h(&v);
	EXPECT_EQ(h.get_value<double>(), 5.453354);
	EXPECT_EQ(h.get_cur_type(), double_);
}

TEST(OPERATOR_EQ_SET_VALUE, set_char) {
	Variant<char>v;
	v = 'a';

	TestHelper<char>h(&v);
	EXPECT_EQ(h.get_value<char>(), 'a');
	EXPECT_EQ(h.get_cur_type(), char_);
}

TEST(OPERATOR_EQ_SET_VALUE, rvalue_multiple_types_set) {
	Variant<double, float, char, int>v;
	TestHelper<double, float, char, int>h(&v);

	v = 'a';
	EXPECT_EQ(h.get_value<char>(), 'a');
	EXPECT_EQ(h.get_cur_type(), char_);

	v = 1;
	EXPECT_EQ(h.get_value<int>(), 1);
	EXPECT_EQ(h.get_cur_type(), int_);

	v = 1.3f;
	EXPECT_EQ(h.get_value<float>(), 1.3f);
	EXPECT_EQ(h.get_cur_type(), float_);

	v = 1.237624982735;
	EXPECT_EQ(h.get_value<double>(), 1.237624982735);
	EXPECT_EQ(h.get_cur_type(), double_);

}

TEST(OPERATOR_EQ_SET_VALUE, l_value_multiple_types_set) {
	Variant<double, float, char, int>v;
	TestHelper<double, float, char, int>h(&v);

	char ch = 'a';
	v = ch;
	EXPECT_EQ(h.get_value<char>(), 'a');
	EXPECT_EQ(h.get_cur_type(), char_);

	int i = 1;
	v = i;
	EXPECT_EQ(h.get_value<int>(), 1);
	EXPECT_EQ(h.get_cur_type(), int_);

	float f = 1.3f;
	v = f;
	EXPECT_EQ(h.get_value<float>(), 1.3f);
	EXPECT_EQ(h.get_cur_type(), float_);

	double d = 1.237624982735;
	v = d;
	EXPECT_EQ(h.get_value<double>(), 1.237624982735);
	EXPECT_EQ(h.get_cur_type(), double_);

}





int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	getchar();
	return 0;
}