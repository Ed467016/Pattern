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
		visited = new bool* [floor_height];

		for (uint8_t i = 0; i < floor_height; i++)
		{
			visited[i] = new bool[floor_width];
			memset(visited[i], 0, floor_width * sizeof(bool));
		}

		matrix_corners* temp_corners = new matrix_corners[0];
		uint8_t temp_corners_iterator = 0;

		for (uint8_t i = 0; i < floor_height; i++)
		{
			uint8_t j = floor[i].find_first_not_of(__NONE, 0);

			if (!visited[i][j])
			{
				auto mc = matrix_corners(i, j);
				temp_corners[temp_corners_iterator++] = mc;

				getCorners(floor, visited, mc, i, j);
			}

			visited[i][j] = true;
		}

		return nullptr;
	}
}

