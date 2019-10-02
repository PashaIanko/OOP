#pragma once
#include <math.h>
#include <typeinfo>

template<typename... Args>
class variant;

template<typename Head, typename... Tail>
class variant<Head, Tail...> : variant<Tail...>
{

	typedef variant<Tail...> base_type;
	typedef Head           value_type;

public:
	variant() {}
	variant(Head h, Tail... tail) : variant<Tail...>(tail...), head_(h)	{}

	void SetValue(Head val);

	
public:
	base_type& base = static_cast<base_type&>(*this);
public:
	Head       head_;
};

template<>
class variant<>
{};


/*template<typename T>
class Variant {
public:
	enum Type { int_t, double_t };
	
	Variant() : type_id (typeid(void).hash_code()) {};
	Variant(const Variant & v) : data(v.data), type_id(v.type_id) {};
	Variant(T val) : data(val), type_id(typeid(val).hash_code()) {}; // конструктор


	void SetValue(const T val); // выставить значение
	T ToType(bool* res) const; // ѕривести значение к T. res - true, если приведение возможно.
	

	
	bool CanConvert(Type t) const; //возвращает true, если можно привести к данному типу
	bool operator!= (const Variant & v) const;
	bool operator== (const Variant & v) const;
	Variant& operator= (const Variant & variant);

private:
	size_t type_id;
	T data;
};

template<typename T>
inline void Variant<T>::SetValue(const T val) {
	data = val;
}

template<typename T>
inline T Variant<T>::ToType(bool * res) const
{
	if (*res) {
		T casted_val = static_cast<T> (data);
		return casted_val;
	}
	else
		return T{}; //»ли запретить еЄ?
}

template<typename T>
inline bool Variant<T>::CanConvert(Type t) const {
	return false;
}

template<typename T>
inline bool Variant<T>::operator!=(const Variant & v) const
{
	return (type_id != v.type_id || data != v.data);
}

template<typename T>
inline bool Variant<T>::operator==(const Variant & v) const
{
	return (data == v.data && type_id == v.type_id);
}

template<typename T>
inline Variant<T>& Variant<T>::operator=(const Variant & variant)
{
	if (this != &variant) {
		data = variant.data;
		type_id = variant.type_id;
	}
	return *this;
}*/

template<typename Head, typename ...Tail>
inline void variant<Head, Tail...>::SetValue(Head val) {
	head_ = val;
	auto b = base; 
	decltype(val);
}
