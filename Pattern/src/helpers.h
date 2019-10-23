#pragma once
#include <string>
#include <algorithm>
#include <vector>
#include "matrix_corners.h"

using namespace std;
using namespace pattern;

pair<string, double> key_value_builder(const string& c);
void removeWhiteSpaces(string& s);
bool getCorners(const vector<string>&, bool**, matrix_corners&, const uint8_t, const uint8_t);