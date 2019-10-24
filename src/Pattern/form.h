#include <string>
#pragma once

class form
{
public:
	virtual double estimate_cost(std::map<std::string, uint8_t>&) = 0;
};