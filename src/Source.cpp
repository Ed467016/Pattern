#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cassert>
#include <algorithm>

const int INF = 1000 * 1000;

int minCost[9][8][8]; // [orientation][i][j]

// 0 #

// 1 ##

// 2 #
//   #

// 3 ###

// 4 #
//   #
//   #

// 5 ##
//   #.

// 6 #.
//   ##

// 7 ##
//   .#

// 8 .#
//   ##

int sizeJ;

void go(int i, int pos, int code0, int code1, int code2, int cost, std::vector<int>& profileCost) {
	if (pos == sizeJ) {
		assert(1 <= sizeJ && sizeJ <= 8);
		profileCost[(code1 << 8) + code2] = std::min(profileCost[(code1 << 8) + code2], cost);
		return;
	}
	assert(0 <= pos && pos <= sizeJ);
	if (((code0 >> pos) & 1) == 1) {
		go(i, pos + 1, code0, code1, code2, cost, profileCost);
		return;
	}
	assert(((code0 >> pos) & 1) == 0);
	{
		// 0 #
		if (minCost[0][i][pos] < INF) {
			go(i, pos + 1, code0 | (1 << pos), code1, code2, cost + minCost[0][i][pos], profileCost);
		}
	}
	{
		// 1 ##
		if (minCost[1][i][pos] < INF && ((code0 >> pos) & 3) == 0) {
			go(i, pos + 2, code0 | (3 << pos), code1, code2, cost + minCost[1][i][pos], profileCost);
		}
	}
	{
		// 2 #
		//   #
		if (minCost[2][i][pos] < INF && ((code0 >> pos) & 1) == 0 && ((code1 >> pos) & 1) == 0) {
			go(i, pos + 1, code0 | (1 << pos), code1 | (1 << pos), code2, cost + minCost[2][i][pos], profileCost);
		}
	}
	{
		// 3 ###
		if (minCost[3][i][pos] < INF && ((code0 >> pos) & 7) == 0) {
			go(i, pos + 3, code0 | (7 << pos), code1, code2, cost + minCost[3][i][pos], profileCost);
		}
	}
	{
		// 4 #
		//   #
		//   #
		if (minCost[4][i][pos] < INF && ((code0 >> pos) & 1) == 0 && ((code1 >> pos) & 1) == 0 && ((code2 >> pos) & 1) == 0) {
			go(i, pos + 1, code0 | (1 << pos), code1 | (1 << pos), code2 | (1 << pos), cost + minCost[4][i][pos], profileCost);
		}
	}
	{
		// 5 ##
		//   #.
		if (minCost[5][i][pos] < INF && ((code0 >> pos) & 3) == 0 && ((code1 >> pos) & 1) == 0) {
			go(i, pos + 2, code0 | (3 << pos), code1 | (1 << pos), code2, cost + minCost[5][i][pos], profileCost);
		}
	}
	{
		// 6 #.
		//   ##
		if (minCost[6][i][pos] < INF && ((code0 >> pos) & 3) == 0 && ((code1 >> (pos + 1)) & 1) == 0) {
			go(i, pos + 2, code0 | (3 << pos), code1 | (1 << (pos + 1)), code2, cost + minCost[6][i][pos], profileCost);
		}
	}
	{
		// 7 ##
		//   .#
		if (minCost[7][i][pos] < INF && ((code0 >> pos) & 1) == 0 && ((code1 >> (pos - 3)) & 1) == 0) {
			go(i, pos + 1, code0 | (1 << pos), code1 | (3 << (pos - 1)), code2, cost + minCost[7][i][pos], profileCost);
		}
	}
	{
		// 8 .#
		//   ##
		if (minCost[8][i][pos] < INF && ((code0 >> pos) & 1) == 0 && ((code1 >> pos) & 3) == 0) {
			go(i, pos + 1, code0 | (1 << pos), code1 | (3 << pos), code2, cost + minCost[8][i][pos], profileCost);
		}
	}
}

int main() {
	int sizeI, nTypes;
	scanf_s("%d %d %d", &sizeI, &sizeJ, &nTypes);
	std::vector<std::vector<int>> room(sizeI + 2, std::vector<int>(sizeJ, 2));
	for(int i = 0; i < sizeI; i++){
		for (int j = 0; j < sizeJ; j++) {
			scanf_s("%d", &room[i][j]);
		}
	}
	for (int o = 0; o < 9; o++) {
		for (int i = 0; i < sizeI; i++) {
			for (int j = 0; j < sizeJ; j++) {
				minCost[o][i][j] = INF;
			}
		}
	}
	for (int t = 0; t < nTypes; t++) {
		int form, cost;
		scanf_s("%d %d", &form, &cost);
		if (form == 1) {
			int color;
			scanf_s("%d", &color);
			for (int i = 0; i < sizeI; i++) {
				for (int j = 0; j < sizeJ; j++) {
					if (room[i][j] == color) {
						minCost[0][i][j] = std::min(minCost[0][i][j], cost);
					}
				}
			}
		} else if (form == 2) {
			int color1, color2;
			scanf_s("%d %d", &color1, &color2);
			for (int i = 0; i < sizeI; i++) { // 1 ##
				for (int j = 0; j + 1 < sizeJ; j++) {
					if ((room[i][j] == color1 && room[i][j + 1] == color2) || (room[i][j] == color2 && room[i][j + 1] == color1)) {
						minCost[1][i][j] = std::min(minCost[1][i][j], cost);
					}
				}
			}
			for (int i = 0; i + 1 < sizeI; i++) { // 2 #
				for (int j = 0; j < sizeJ; j++) { //   #
					if ((room[i][j] == color1 && room[i+1][j] == color2) || (room[i][j] == color2 && room[i + 1][j] == color1)) {
						minCost[2][i][j] = std::min(minCost[2][i][j], cost);
					}
				}
			}
		} else if (form == 3) {
			int color1, color2, color3;
			scanf_s("%d %d %d", &color1, &color2, &color3);
			for (int i = 0; i < sizeI; i++) { // 3 ###
				for (int j = 0; j + 2 < sizeJ; j++) {
					if ((room[i][j] == color1 && room[i][j + 1] == color2 && room[i][j + 2] == color3) || 
						(room[i][j] == color3 && room[i][j + 1] == color2 && room[i][j + 2] == color1)) {
						minCost[3][i][j] = std::min(minCost[3][i][j], cost);
					}
				}
			}									  //   #
			for (int i = 0; i + 2 < sizeI; i++) { // 4 #
				for (int j = 0; j < sizeJ; j++) { //   #
					if ((room[i][j] == color1 && room[i][j + 1] == color2 && room[i][j + 2] == color3) ||
						(room[i][j] == color3 && room[i][j + 1] == color2 && room[i][j + 2] == color1)) {
						minCost[4][i][j] = std::min(minCost[4][i][j], cost);
					}
				}
			}
		} else {
			assert(form == 4);
			int color1, color2, color3;
			scanf_s("%d %d %d", &color1, &color2, &color3);
			for (int i = 0; i + 1 < sizeI; i++) {     // 6 ##
				for (int j = 0; j + 1 < sizeJ; j++) { //   .#
					if (room[i][j] == color1 && room[i][j + 1] == color2 && room[i+1][j+1] == color3) { 
						minCost[6][i][j] = std::min(minCost[6][i][j], cost);
					}
				}
			}
			for (int i = 0; i + 1 < sizeI; i++) {     // 5 ##
				for (int j = 0; j + 1 < sizeJ; j++) { //   #.
					if (room[i][j] == color2 && room[i][j + 1] == color3 && room[i + 1][j] == color1) {
						minCost[5][i][j] = std::min(minCost[5][i][j], cost);
					}
				}
			}
			for (int i = 0; i + 1 < sizeI; i++) {     // 8 #.
				for (int j = 0; j + 1 < sizeJ; j++) { //   ##
					if (room[i][j] == color3 && room[i + 1][j] == color2 && room[i + 1][j + 1] == color1) {
						minCost[8][i][j] = std::min(minCost[8][i][j], cost);
					}
				}
			}
			for (int i = 0; i + 1 < sizeI; i++) {     // 7 .#
				for (int j = 0; j + 1 < sizeJ; j++) { //   ##
					if (room[i][j] == color1 && room[i + 1][j] == color2 && room[i + 1][j - 1] == color3) {
						minCost[7][i][j] = std::min(minCost[7][i][j], cost);
					}
				}
			}
		}
	}
	std::vector<int> profileCost(1 << 16, INF);
	int code0 = 0;
	int code1 = 0;
	for (int j = 0; j < sizeJ; j++) {
		if (room[0][j] == 2) {
			code0 |= 1 << j;
		}
		if (room[1][j] == 2) {
			code1 |= 1 << j;
		}
	}
	profileCost[(code0 << 8) + code1] = 0;
	std::vector<int> prevProfileCost(1 << 16, INF);
	for (int i = 0; i < sizeI; i++) {
		profileCost.swap(prevProfileCost);
		for (int code = 0; code < (int)profileCost.size(); code++) {
			profileCost[code] = INF;
		}
		int code2 = 0;
		for (int j = 0; j < sizeJ; j++) {
			if (room[i+2][j] == 2) {
				code2 |= 1 << j;
			}
		}
		for (int code = 0; code < (int)prevProfileCost.size(); code++) {
			if (prevProfileCost[code] < INF) {
				go(i, 0, code >> 8, code & 0xFF, code2, prevProfileCost[code], profileCost);
			}
		}
	}
	int cost = profileCost[(((1 << sizeJ) - 1) << 8) + ((1 << sizeJ) - 1)];
	if (cost >= INF) {
		cost = -1;
	}
	printf("%d", cost);
	return 0;
}