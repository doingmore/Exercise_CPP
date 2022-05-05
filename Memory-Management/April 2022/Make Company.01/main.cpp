#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "Company.h"
#include "MakeCompany.h"

std::vector<std::string> readStringsLine() {
	std::vector<std::string> values;

	std::string line;
	std::getline(std::cin, line);

	std::istringstream lineIn(line);

	std::string value;
	while (lineIn >> value) {
		values.push_back(value);
	}

	return values;
}

int main() {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // this line added by Svetozar, flag for memory leak, exercise

	std::cin.sync_with_stdio(false);
	std::cout.sync_with_stdio(false);

	std::vector<std::string> properties = readStringsLine();
	while (properties[0] != "end") {
		auto company = makeCompany(properties);

		auto copy = company;

		std::cout << copy->toString() << std::endl;

		properties = readStringsLine();
	}

	return 0;
}