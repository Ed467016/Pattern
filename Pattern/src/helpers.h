#pragma once
#include <string>
#include <algorithm>
#include <vector>
#include "matrix_corners.h"
#include "global.h"

using namespace std;
using namespace pattern;

pair<string, double> key_value_builder(const string& c);
void removeWhiteSpaces(string& s);