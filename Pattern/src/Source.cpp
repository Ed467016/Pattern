#include <iostream>
#include <algorithm>
#include "global.h"
#include "parser.h"
#include "form.h"
#include "input_handler.h"

using namespace std;
using namespace pattern;

int main() {
	uint8_t n, m, k;
	map<string, double> costs;
	input_handler ih;
	parser prs;

	cout << "Input:: " << "\n";
	auto input = ih.get_inputs(cin, n, m, k, costs);
	auto forms = prs.parse_forms(input);
	getchar();
}