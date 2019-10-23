#pragma once
#include <stdint.h>

namespace pattern {
	struct matrix_corners
	{
		matrix_corners();
		matrix_corners(uint8_t x, uint8_t y);
		uint8_t x0, y0, x1, y1;
	};
}