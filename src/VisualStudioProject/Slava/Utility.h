#pragma once
#ifndef UTILITY_H
#define UTILITY_H
#include <iostream>
#include <sstream>

namespace slava
{
	template<typename T>
	std::string toString(T t) {
		std::stringstream ss;
		ss << t;
		std::string s;
		ss >> s;
		return s;
	}
}

#endif
