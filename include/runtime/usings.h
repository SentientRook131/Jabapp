#pragma once
#include <string>
#include <array>
#include <vector>
#include <iostream>
#include <any>
#include <map>

using String = std::string;
template<typename T, std::size_t N>
using Array = std::array<T, N>;
template<typename T>
using List = std::vector<T>;
using Object = std::any;
template<typename K, typename V>
using Map = std::map<K, V>;
static std::ostream& operator<<(std::ostream& os, Object obj) {
	if (obj.has_value()) {
		if (obj.type() == typeid(int)) os << std::any_cast<int>(obj);
		else if (obj.type() == typeid(float)) os << std::any_cast<float>(obj);
		else if (obj.type() == typeid(double)) os << std::any_cast<double>(obj);
		else if (obj.type() == typeid(short)) os << std::any_cast<short>(obj);
		else if (obj.type() == typeid(bool)) os << std::any_cast<bool>(obj);
		else if (obj.type() == typeid(long long)) os << std::any_cast<long long>(obj);
		else if (obj.type() == typeid(long int)) os << std::any_cast<long int>(obj);
		else if (obj.type() == typeid(long double)) os << std::any_cast<long double>(obj);
		else if (obj.type() == typeid(long)) os << std::any_cast<long>(obj);
		else if (obj.type() == typeid(unsigned int)) os << std::any_cast<unsigned int>(obj);
		else if (obj.type() == typeid(unsigned long int)) os << std::any_cast<unsigned long int>(obj);
		else if (obj.type() == typeid(unsigned long long)) os << std::any_cast<unsigned long long>(obj);
		else if (obj.type() == typeid(unsigned long)) os << std::any_cast<unsigned long>(obj);
		else if (obj.type() == typeid(char)) os << std::any_cast<char>(obj);
	}
	return os;
}
static bool isNumberType(const Object& obj) {
	if (obj.type() == typeid(int)) return true;
	else if (obj.type() == typeid(float)) return true;
	else if (obj.type() == typeid(double)) return true;
	else if (obj.type() == typeid(short)) return true;
	else if (obj.type() == typeid(bool)) return true;
	else if (obj.type() == typeid(long long)) return true;
	else if (obj.type() == typeid(long int)) return true;
	else if (obj.type() == typeid(long double)) return true;
	else if (obj.type() == typeid(long)) return true;
	else if (obj.type() == typeid(unsigned int)) return true;
	else if (obj.type() == typeid(unsigned long int)) return true;
	else if (obj.type() == typeid(unsigned long long)) return true;
	else if (obj.type() == typeid(unsigned long)) return true;
	else if (obj.type() == typeid(char)) return true;
	return false;
}
template<typename T, typename B>
static bool instanceof(B* b) {
	return dynamic_cast<B*>(b) != nullptr;
}
