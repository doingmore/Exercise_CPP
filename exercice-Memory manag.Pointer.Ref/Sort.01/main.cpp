#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>


#include "Company.h"

std::vector<Company> filling_vector()
{
	std::vector<Company> answer;
	std::string input;
	std::string name;
	int id{0};
	std::getline(std::cin, input);
	while (input != "end")
	{
		std::istringstream in(input);
		in >>name>>id ;
		answer.emplace_back(Company{ id,name });
		std::getline(std::cin, input);
	}
	return answer;
}


bool sort_by_id(const Company& left,const Company& right)
{
	return left.getId() < right.getId();
}

bool sort_by_name(const Company& left, const Company& right)
{
	return left.getName() < right.getName();
}

int main()
{
	std::vector<Company> list = filling_vector();
	std::string choice;
	std::getline(std::cin, choice);

	if (choice == "id")
	{
	std::sort(list.begin(), list.end(), sort_by_id);
	}
	else if (choice == "name")
	{
	std::sort(list.begin(), list.end(), sort_by_name);
	}
	else
	{
		throw _EXCEPTION_;
	}

	for (Company c : list)
	{
		std::cout << c.toString() << '\n';
	}

	return 0;
}