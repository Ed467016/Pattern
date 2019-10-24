#include <iostream>
#include <algorithm>
#include <time.h>
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

	clock_t t;
	cout << "Input:: " << "\n";
	auto input = ih.get_inputs(cin, n, m, k, costs);
	auto forms = prs.parse_forms(input);
	t = clock() - t;
	t = t / (CLOCKS_PER_SEC / 1000);
	cout << t;
	getchar();
}