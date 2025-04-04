
#include <customstring.h>

#include <algorithm>
#include <iostream>
#include <vector>


int main(int argc, char** argv)
{
	std::vector<String> strings = std::vector<String>();

	for(int t = 1; t < argc; ++t)
		strings.push_back(String(argv[t]));

	std::sort(strings.begin(), strings.end(), [](const String& a, const String& b) -> bool { return !compare_ignore_case(a, b); });

	for(const auto& str : strings)
		std::cout << str << '\n';

	return 0;
}
