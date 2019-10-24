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