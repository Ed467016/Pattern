#include <map>
#include <vector>
#include "global.h"
#include "form.h"
#include "matrix_corners.h"
#include "helpers.h"
#pragma once

using namespace std;

namespace pattern {
	class parser
	{
	public:
		parser();
		vector<form>* parse_forms(const vector<string>&);

	private:
		bool** visited = nullptr;

		string one_square[2] = { string("x00"), string("000") }; // x
		string two_square[2] = { string("xx0"), string("000") }; // xx
		string three_square[2] = { string("xxx"), string("000") }; // xxx
		string three_lined_square[2] = { string("xx0"), string("x00") }; // xx
	};
}
