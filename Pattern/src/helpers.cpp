#include <string>
#include <algorithm>
#include "helpers.h"

using namespace std;

void removeWhiteSpaces(string& s) {
	s.erase(remove_if(s.begin(), s.end(), isspace), s.end());
}

pair<string, double> key_value_builder(const string& c) {
	string temp = c.substr(2, c.size() - 2);
	size_t cut_index = temp.find_first_of(' ', 0) + 1;
	string key = temp.substr(cut_index, temp.size() - cut_index);
	removeWhiteSpaces(key);
	double cost = stoi(temp);

	pair<string, double> result;
	result.first = key;
	result.second = cost;

	return result;
}

bool getCorners(const vector<string>& m, bool** v, matrix_corners& mc, const uint8_t x, const uint8_t y)
{
	if (v[x][y])
		return false;

	v[x][y] = true;

	if (x - 1 >= 0 && getCorners(m, v, mc, x - 1, y))
	{
		if (x - 1 < mc.x0)
		{
			mc.x0 = x - 1;
		}
	}

	if (y - 1 >= 0 && getCorners(m, v, mc, x, y - 1))
	{
		if (y - 1 < mc.y0)
		{
			mc.y0 = y - 1;
		}
	}

	if (x + 1 <= getCorners(m, v, mc, x + 1, y))
	{
		if (x + 1 > mc.x1)
		{
			mc.x1 = x + 1;
		}
	}

	if (getCorners(m, v, mc, x, y + 1))
	{
		if (y + 1 > mc.y1)
		{
			mc.y1 = y + 1;
		}
	}

	return true;
}
