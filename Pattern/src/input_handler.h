#include <istream>
#include <map>
#include <time.h>
#include <vector>
#include "helpers.h"
using namespace std;

#pragma once

namespace pattern {
	class input_handler
	{
	public:
		vector<string> get_inputs(istream&, uint8_t&, uint8_t&, uint8_t&, map<string, double>&, clock_t&);
	};
}
