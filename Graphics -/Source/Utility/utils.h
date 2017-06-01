#pragma once

#include <strstream>

#define VALIDATE(a) if (!a) return (false)


template<typename T>
std::string ToString(const T& _value)
{
	std::strstream theStream;
	theStream << _value << std::ends;
	return (theStream.str());
}
