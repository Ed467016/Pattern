#include "parser.h"

namespace pattern
{
	parser::parser()
	{
	}

	vector<form>* parser::parse_forms(const vector<string>& floor)
	{
		uint8_t floor_height = floor.size();
		uint8_t floor_width = floor.at(0).length();
		visited = new bool*[floor_height];

		for (uint8_t i = 0; i < floor_height; i++)
		{
			visited[i] = new bool[floor_width];
			memset(visited[i], 0, floor_width * sizeof(bool));
		}

		vector<matrix_corners> temp_corners;

		for (uint8_t i = 0; i < floor_height; i++)
		{
			size_t j = floor[i].find_first_not_of(__NONE, 0);

			if (!visited[i][j])
			{
				auto mc = matrix_corners(i, j);
				getCorners(floor, visited, mc, i, j, floor_width, floor_height);

				temp_corners.push_back(mc);
			}

			visited[i][j] = true;
		}

		vector<vector<string*>> sections;

		for (size_t i = 0; i < temp_corners.size(); i++)
		{
			auto x = getSection(floor, temp_corners[i]);
			sections.push_back(x);
		}

		return nullptr;
	}

	bool parser::getCorners(
		const vector<string>& m,
		bool** v,
		matrix_corners& mc,
		const uint8_t x,
		const uint8_t y,
		const uint8_t& vw,
		const uint8_t& vh)
	{
		if (x >= vh || y >= vw || x < 0 || y < 0)
		{
			return false;
		}

		if (v[x][y])
			return false;

		v[x][y] = true;

		if (m[x][y] == __NONE)
		{
			return false;
		}

		// UPPER CORNER
		if (!getCorners(m, v, mc, x - 1, y, vw, vh) && x < mc.x0)
			mc.x0 = x;

		// LEFT CORNER
		if (!getCorners(m, v, mc, x, y - 1, vw, vh) && y < mc.y0)
			mc.y0 = y;

		// BOTTOM CORNER
		if (!getCorners(m, v, mc, x + 1, y, vw, vh) && x > mc.x1)
			mc.x1 = x;

		// RIGHT CORNER
		if (!getCorners(m, v, mc, x, y + 1, vw, vh) && y > mc.y1)
			mc.y1 = y;

		return true;
	}

	vector<string*> parser::getSection(const vector<string>& v, const matrix_corners& mc)
	{
		vector<string*> result;

		for (uint8_t i = mc.x0; i <= mc.x1; i++)
			result.push_back(new string(v[i].substr(mc.y0, mc.y1 + 1)));

		return result;
	}
}

