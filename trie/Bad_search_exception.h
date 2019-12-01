#pragma once
#include <string>
class BadSearchException {
public:
	BadSearchException(const std::string& str_) : str(str_) {};
private:
	std::string str;
};