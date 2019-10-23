#include "input_handler.h"

namespace pattern {
	vector<string> input_handler::get_inputs(istream& is, uint8_t& n, uint8_t& m, uint8_t& k, map<string, double>& costs, clock_t& t)
	{
		string temp;
		is >> temp;
		n = stoi(temp);

		is >> temp;
		m = stoi(temp);

		is >> temp;
		k = stoi(temp);
		t = clock();

		uint8_t rows_count = n + k;
		vector<string> result;

		for (uint8_t i = 0; i < n; i++)
		{
			getline(is, temp);
			if (temp.empty())
			{
				i--;
				continue;
			}
			removeWhiteSpaces(temp);
			result.push_back(temp);
		}

		for (uint8_t i = 0; i < k; i++)
		{
			getline(is, temp);
			if (temp.empty())
			{
				i--;
				continue;
			}

			auto kv_pair = key_value_builder(temp);
			costs.insert(costs.end(), kv_pair);
		}

		return result;
	}
}