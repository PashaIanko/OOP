#pragma once
#include <math.h>
#include <typeinfo>
#include <string>
#include <cstring>
#include <type_traits>
#include <exception>
#include <initializer_list>
#include <type_traits>
#include <utility>
#include <cctype>
#include <cstdlib>
#include <algorithm>
#include "Types.h"

#undef max
#undef min

template<size_t a, size_t... Args>
struct static_max;

template<size_t a>
struct static_max<a> {
	static const size_t value = a;
};

template<size_t a, size_t b, size_t... Args>
struct static_max<a, b, Args...> {
	static const size_t value = a >= b ? static_max<a, Args...>::value : static_max<b, Args...>::value;
};

template<typename T, typename... Ts>
struct is_one_of {
	static constexpr bool value = std::disjunction<std::is_same<T, Ts>...>::value;
};

template<typename T, typename... Ts>
struct extract_first {
	using type = T;
};

template<typename T, typename... Ts>
using is_one_of_remove_ref = is_one_of<typename std::remove_reference<T>::type, Ts...>;

template<typename... Ts>
using first_Type = typename extract_first<Ts...>::type;

template<typename... Ts>
class Variant {
public:

	template<typename FstType = extract_first<Ts...>::type>
	Variant() {
		size_t max_size = static_max<sizeof(Ts)...>::value;
		data_size = max_size;

		/*extracting the first type*/
		new(static_cast<void*>(std::addressof(value))) FstType{};
		set_cur_type<FstType>();
	}

	~Variant() {
		destroy_current();
	};

	template<typename T>
	using is_one_of_remove_ref = is_one_of<typename std::remove_reference<T>::type, Ts...>;


	template<typename T,
		typename = typename std::enable_if<is_one_of_remove_ref<T>::value, void>::type>
		Variant(const T& val) {
		size_t max_size = static_max<sizeof(Ts)...>::value;
		data_size = max_size;
		new(static_cast<void*>(std::addressof(value))) T{ val };
		set_cur_type<T>();
	};

	template<typename T,
		typename = typename std::enable_if<is_one_of_remove_ref<T>::value, void>::type>
		Variant(T &&v) {
		set<T>(std::forward<T>(v));
	}

	template<typename T,
		typename = typename std::enable_if<is_one_of_remove_ref<T>::value, void>::type >

		void SetValue(const T& val) {
		destroy_current();
		new(static_cast<void*>(std::addressof(value))) T(val); /*copy_ctor*/
		set_cur_type<T>();
	};


	int ToInt(bool* res)  {
		*res = true;
		switch (current_type) {
		case int_: {
			int* val_ = reinterpret_cast<int*>(&value);
			return *val_;
		}

		case char_: {
			char* val = reinterpret_cast<char*>(&value);
			int val_ = static_cast<int>(*val); //ASCII code;
			return val_;
		}
		case float_: {
			if (check_limits_internal_<float, int>()){//check_limits_internal<float, int, false>()) {
				float* val = reinterpret_cast<float*>(&value);
				int int_v = static_cast<int>(*val);
				return int_v;
			}
			else {
				*res = false;
				return -1;
			}
			
		}
		case double_: {
			if (check_limits_internal_<double, int>()){//check_limits_internal<double, int, false>()) {
				double* val = reinterpret_cast<double*>(&value);
				int int_v = static_cast<int>(*val);
				return int_v;
			}
			else {
				*res = false;
				return -1;
			}
		}
		case string_: {
			int val = ToInt_internal(res);
			if (*res)
				return val;
			else {
				*res = false;
				return -1;
			}
		}
		default: {
			*res = false;
			return -1;
		}
	}
	};

	double ToDouble(bool* res) {
		*res = true;
		switch (current_type) {
		case int_: {
			int* val_ = reinterpret_cast<int*>(&value);
			double d_val = static_cast<double>(*val_);
			return d_val;
		}

		case char_: {
			char* val = reinterpret_cast<char*>(&value);
			double val_ = static_cast<double>(*val); //ASCII
			return val_;
		}
		case float_: {
			float* val = reinterpret_cast<float*>(&value);
			double v = static_cast<double>(*val);
			return v;
		}
		case double_: {
			double* val = reinterpret_cast<double*>(&value);
			return *val;
		}
		case string_: {
			double val = ToFloatingPoint_internal<double>(res);//ToDouble_internal(res);
			if (*res)
				return val;
			else {
				*res = false;
				return -1;
			}
		}
		default: {
			*res = false;
			return -1;
		}
		}
	};
	float ToFloat(bool* res) {
		*res = true;
		switch (current_type) {
		case int_: {
			int* val_ = reinterpret_cast<int*>(&value);
			float val = static_cast<float>(*val_);
			return val;
		}

		case char_: {
			char* val_ = reinterpret_cast<char*>(&value);
			float val = static_cast<float>(*val_); //ASCII
			return val;
		}
		case float_: {
			float* val = reinterpret_cast<float*>(&value);
			return *val;
		}
		case double_: {
			if (check_limits_internal_<double, float>()){//check_limits_internal<float, double>()) {
				double* val_ = reinterpret_cast<double*>(&value);
				float val = static_cast<float>(*val_);
				return val;
			}
			else {
				*res = false;
				return -1;
			}
		}
		case string_: {
			float val = ToFloatingPoint_internal<float>(res);//ToFloat_internal(res);
			if (*res)
				return val;
			else {
				*res = false;
				return -1;
			}
		}
		default: {
			*res = false;
			return -1;
		}
		}
	};

	std::string ToString(bool* res) {
		*res = true;
		switch (current_type) {
		case int_: {
			int* val_ = reinterpret_cast<int*>(&value);
			std::string str = std::to_string(*val_);
			return str;
		}

		case char_: {
			const char* val_ = reinterpret_cast<const char*>(&value);
			std::string str(val_, sizeof(char));
			return str;
		}
		case float_: {
			float* val = reinterpret_cast<float*>(&value);
			std::string str = std::to_string(*val);
			return str;
		}
		case double_: {
			double* val = reinterpret_cast<double*>(&value);
			std::string str = std::to_string(*val);
			return str;
		}
		case string_: {
			auto str = reinterpret_cast<std::string*>(&value);
			return *str;
		}
		default: {
			*res = false;
			return "";
		}
		}
	};
	char ToChar(bool* res) {
		*res = true;
		switch (current_type) {
		case int_: {
			if (check_limits_internal_<int, char>()){//check_limits_internal<int, char, false>()) {
				int* val_ = reinterpret_cast<int*>(&value);
				char ch = (char)*val_;// +'0';
				return ch;
			}
			else {
				*res = false;
				return (char)0;
			}
		}

		case char_: {
			char* val_ = reinterpret_cast<char*>(&value);
			return *val_;
		}
		case float_: {
			if (check_limits_internal_<float, char>()){//check_limits_internal<float, char, false>()) {
				float* val_ = reinterpret_cast<float*>(&value);
				char ch = (char)*val_;// +'0';
				return ch;
			}
			else {
				*res = false;
				return (char)0;
			}
		}
		case double_: {
			if (check_limits_internal_<double, char>()){//check_limits_internal<double, char, false>()) {
				double* val_ = reinterpret_cast<double*>(&value);
				char ch = (char)*val_;// +'0';
				return ch;
			}
			else {
				*res = false;
				return (char)0;
			}
		}
		case string_: {
			auto str_ptr = reinterpret_cast<std::string*>(&value);
			if (str_ptr->length() == 1) {
				char ch = str_ptr->at(0);
				return ch;
			}
			else {
				*res = false;
				return '0';
			}
		}
		default: {
			*res = false;
			return '0';
		}
		}
	};

	template<typename T>
	bool CanConvert() {
		if (std::is_same<std::string, T>::value) {
			return true;
		}
		switch (current_type) {
		case int_: {
			/*к инту кастится всё.но надо посмотреть текущее значение если попадает в пределы по чару,
			то ок*/
			if (std::is_same<T, char>::value)
				return check_limits_internal_<int, char>();//check_limits_internal<int, char, false>();
			else
				return std::is_convertible_v<int, T>;
		}
		case double_: {
			if (std::is_same<T, char>::value)
				return check_limits_internal_<double, char>();//check_limits_internal<double, char, false>();
			if (std::is_same<T, int>::value)
				return check_limits_internal_<double, int>();//check_limits_internal<double, int, false>();
			if (std::is_same<T, float>::value)
				return check_limits_internal_<double, float>();//check_limits_internal<double, float, false>();
			else
				return std::is_convertible_v<double, T>;
		}
		case float_: {
			if (std::is_same<T, char>::value){
				return check_limits_internal_<float, char>();//check_limits_internal<float, char, false>();
			}
			if (std::is_same<T, int>::value) {
				return check_limits_internal_<float, int>();//check_limits_internal<float, int, false>();
			}
			else
				return std::is_convertible_v<float, T>;
		}
		case char_:
			return true; // std::is_convertible_v<char, T>;
		case string_: {
			auto s_ptr = reinterpret_cast<std::string*>((void*)&value);
			bool res_ = false;
			using no_const_T = typename std::remove_const<T>::type;
			if (std::is_same<no_const_T, int>::value) {
				int val = ToInt_internal(&res_);
				return res_;
			}
			if (std::is_same<no_const_T, float>::value) {
				float val = ToFloatingPoint_internal<float>(&res_);//ToFloat_internal(&res_);
				return res_;
			}
			if (std::is_same<no_const_T, double>::value) {
				double val = ToFloatingPoint_internal<double>(&res_);//ToDouble_internal(&res_);
				return res_;
			}
			else {
				return true;//std::is_convertible_v<std::string, T>;
			}
			
		}
		
		default:
			return false;
		}

	};

	void destroy_current()
	{
		switch (current_type) {
		case string_:
		{
			auto str = reinterpret_cast<std::string*>(&value);
			str->~basic_string();
			break;
		}
		default:
			break;
		}
	}

	template<typename T,
		typename = typename std::enable_if<is_one_of_remove_ref<T>::value, void>::type>
		Variant &operator=(T &&v) {
		destroy_current();
		new(static_cast<void*>(std::addressof(value))) typename std::remove_reference<T>::type(std::forward<T>(v));
		set_cur_type<T>();
		return *this;
	}

	bool operator!= (const Variant & v) const {
		return !(this->operator==(v));
	};
	bool operator== (const Variant & v) const {
		if (data_size != v.data_size || current_type != v.current_type)
			return false;
		else {
			switch (current_type) {
			case string_: {
				auto l_str = reinterpret_cast<std::string*>((void*)&value);
				auto r_str = reinterpret_cast<const std::string*>(static_cast<const void*>(&v.value));
				return !(l_str->compare(r_str->c_str()));
			}
			default: {
				size_t cur_size = size_of_cur_type(current_type);
				int cmp_res = memcmp(&value, &v.value, cur_size);
				return !cmp_res;
			}

			}

		}
	};

	Variant & operator=(const Variant & variant) {
		if (*this != variant) {
			destroy_current();
			switch (variant.current_type) {
			case string_: {
				auto right_str = reinterpret_cast<const std::string*>(&variant.value);
				new(static_cast<void*>(std::addressof(value))) std::string(*right_str); /*copy_ctor*/
				break;
			}
			default: {
				memcpy(&value, &variant.value, size_of_cur_type(variant.current_type));
			}

			}
			data_size = variant.data_size;
			current_type = variant.current_type;
		}
		return *this;
	};


protected:
	size_t get_data_size() { return data_size; };

	template<typename ...Ts>
	friend class TestHelper;


private:
	template<typename T>
	void set_cur_type(/*T& val*/) {
		if (
			std::is_same<std::remove_const<std::remove_reference<T>::type>::type, int>::value) {
			current_type = int_;
		}
		if (
			std::is_same<std::remove_const<std::remove_reference<T>::type>::type, float>::value) {
			current_type = float_;
		}
		if (
			std::is_same<std::remove_const<std::remove_reference<T>::type>::type, char>::value) {
			current_type = char_;
		}
		if (
			std::is_same<std::remove_const<std::remove_reference<T>::type>::type, double>::value) {
			current_type = double_;
		}
		if (
			std::is_same<std::remove_const<std::remove_reference<T>::type>::type, std::string>::value) {
			current_type = string_;
		}
	};

	size_t size_of_cur_type(Types current_t) const {
		switch (current_t) {
		case int_: {
			return sizeof(int);
		}
		case char_: {
			return sizeof(char);
		}
		case float_: {
			return sizeof(float);
		}
		case double_: {
			return sizeof(double);
		}
		case string_: {
			return sizeof(std::string);
		}
		default: {
			return (size_t)-1;
		}

		}
	}

	template<typename T, typename Args, /*typename... Args*/
		typename = typename std::enable_if<is_one_of_remove_ref<T>::value, void>::type>
		void set(Args && args) { /*Args &&... args*/
		size_t max_size = static_max<sizeof(Ts)...>::value;
		new(static_cast<void*>(std::addressof(value))) typename std::remove_reference<T>::type(std::forward<Args>(args)); /*(std::forward<Args>(args)...)*/
		data_size = max_size;
		if (
			std::is_same<std::remove_reference<T>::type, int>::value) {
			current_type = int_;
		}
		if (
			std::is_same<std::remove_reference<T>::type, float>::value) {
			current_type = float_;
		}
		if (
			std::is_same<std::remove_reference<T>::type, char>::value) {
			current_type = char_;
		}
		if (
			std::is_same<std::remove_reference<T>::type, double>::value) {
			current_type = double_;
		}
		if (
			std::is_same<std::remove_reference<T>::type, std::string>::value) {
			current_type = string_;
		}

	};

	bool consists_of_digits(/*const std::string& str*/ const char* str) const {
		if (str == nullptr) {
			return false;
		}
		else {
			size_t len = strlen(str);
			if (len == 0)
				return false;
			for (size_t i = 0; i < len; i++) {
				if (!std::isdigit(str[i])) {
					return false;
				}
			}
		}
		return true;
	}

	bool no_letters(const char* str) const {
		if (str == nullptr) {
			return false;
		}
		else {
			size_t len = strlen(str);
			if (len == 0)
				return false;
			for (size_t i = 0; i < len; i++) {
				if (std::isalpha(str[i])) {
					return false;
				}
			}
		}
		return true;
	}

	size_t count_dots(const char* str) const {
		if (str == nullptr) {
			return 0;
		}
		else {
			size_t len = strlen(str);
			size_t count = 0;
			if (len == 0)
				return 0;
			for (size_t i = 0; i < len; i++) {
				if (str[i] == '.') {
					count++;
				}
			}
			return count;
		}
	}

	int ToInt_internal(bool* res) const {
		*res = true;
		auto str = reinterpret_cast<std::string*>((void*)&value);
		if (!str->empty()) {
			long long val;
			try {
				val = std::stoll(*str);
			}
			catch (...) {
				*res = false;
				return -1;
			}
			long long min = std::min(std::max(val, (long long)std::numeric_limits<int>::min()), 
									(long long)std::numeric_limits<int>::max());
			if (min == (long long)std::numeric_limits<int>::min() ||
				min == (long long)std::numeric_limits<int>::max()) {
				*res = false;
				return (int)min;
			}
			else {
				const char* cstr = str->c_str();
				int val = std::atoi(cstr);
				if (val == 0 && *cstr != '0') {
					/*atoi did not work correctly for some reason*/
					*res = false;
					return -1;
				}
				else if (val == 0 && *cstr != '0') {
					return val;
				}
				else {
					/*necessitates additional check,
					because "-123a" --> -123 by atoi, we want false*/
					const char* cstr_ = cstr;
					if(no_letters(cstr) &&
						count_dots(cstr)<=1 &&
						*cstr != '.')
					{
						*res = true;
						return val;
					}
					else {
						*res = false;
						return -1;
					}
					
				}
			}
		}
		*res = false;
		return -1;
	}

	template<typename T = std::enable_if<std::is_floating_point<T>::type>>
	T ToFloatingPoint_internal(bool* res) const {
		*res = true;
		auto str = reinterpret_cast<std::string*>((void*)&value);
		if (!str->empty()) {
			long double val;
			try {
				val = std::stold(*str);
			}
			catch (...) {
				*res = false;
				return -1;
			}
			long double min_ = (long double)std::numeric_limits<T>::lowest();
			long double max_ = (long double)std::numeric_limits<T>::max();
			long double min = std::min(std::max(val, min_), max_);
			if (min == min_ || min == max_) {
				*res = false;
				return (T)min;
			}
			else {
				const char* cstr = str->c_str();
				T val = std::atof(cstr);
				if (val == 0 && *cstr != '0') {
					/*atoi did not work correctly for some reason*/
					*res = false;
					return -1;
				}
				else if (val == 0 && *cstr != '0') {
					return val;
				}
				else {
					/*necessitates additional check,
					because "-123a" --> -123 by atoi, we want false*/
					const char* cstr_ = cstr;
					if (no_letters(cstr) &&
						count_dots(cstr) <= 1 &&
						*cstr != '.')
					{
						*res = true;
						return val;
					}
					else {
						*res = false;
						return -1;
					}

				}
			}
		}
		*res = false;
		return -1;
	}

	template<typename T, typename V, bool if_V_higher = true>
	bool check_limits_internal() {
		if (if_V_higher) {
			/*for instance, check_limits_intenal<int, float>()*/
			V Ts_min = std::numeric_limits<V>::min();
			V Ts_max = std::numeric_limits<V>::max();
			V* temp = reinterpret_cast<V*>(&value);
			V min = std::min(std::max(*temp, Ts_min), Ts_max);
			return min != Ts_min && min != Ts_max;
		}
		else {
			/*call with check_type<char, int>*/
			T* val_ = reinterpret_cast<T*>(&value);
			T T_max = (T)std::numeric_limits<V>::max();
			T T_min;
			if (std::is_floating_point<T>::value) {
				T_min = (T)std::numeric_limits<V>::lowest();
			}
			else {
				T_min = (T)std::numeric_limits<V>::min();
			}
			T min = std::min(std::max(*val_, T_min), T_max);
			return min != T_min && min != T_max;
		}
		
	}

	template<typename T> 
	T get_value() {
		T* val = reinterpret_cast<T*>(reinterpret_cast<void*>(&value));
		return *val;
	}

	template<typename T, typename V, typename K>
	bool convert_internal() {
		/*K Ts_lowest = std::numeric_limits<T>::lowest();
		K Ts_max = std::numeric_limits<T>::max();
		K temp = (long long)reinterpret_cast<V*>(&value);
		K res = std::min(std::max(*temp, Ts_lowest), Ts_max);
		return res != Ts_lowest && res != Ts_max;*/

		auto v = get_value<T>();
		return  v >= std::numeric_limits<V>::lowest() && v <= std::numeric_limits<V>::max();
	}

	template<typename T, typename V>
	bool check_limits_internal_() {
		if (std::is_integral<T>::value) {
			return convert_internal<T, V, long long>();
		}
		else if (std::is_floating_point<T>::value) {
			return convert_internal<T,V, long double>();
		}
	};

	template<typename From, typename To>
	To ToXXX_Internal(bool* res) {

	}

	template<typename T>
	T toXXX(bool *res) {
		switch (current_type) {
		case int_: 
			return ToXXX_Internal<int, T>(res);
		case char_: 
			return ToXXX_Internal<char, T>(res);
		case float_: 
			return ToXXX_Internal<float, T>(res);
		case double_: 
			return ToXXX_Internal<double, T>(res);
		case string_: 
			return ToXXX_Internal<std::string, T>(res);
		default: {
			*res = false;
			return -1;
		}
		}
	}

	std::aligned_union_t<1, Ts...> value;
	size_t data_size = 0;
	Types current_type{};
	size_t current_index{ std::numeric_limits<size_t>::max() };
};



template<typename... Ts>
class TestHelper {
public:
	TestHelper(Variant<Ts...>* v) : v_ptr(v) {};
	size_t get_v_data_size() { return (v_ptr->get_data_size()); }

	template<typename T>
	T get_value() {
		T* val = reinterpret_cast<T*>(&v_ptr->value);
		return *val;
	}

	Types get_cur_type() {
		return v_ptr->current_type;

	}

private:
	Variant<Ts...>* v_ptr;
};

