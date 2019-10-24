#include "form.h";
#pragma once

class three_square_form : public form
{
public:
	double estimate_cost(std::map<std::string, uint8_t>&) override;
};
