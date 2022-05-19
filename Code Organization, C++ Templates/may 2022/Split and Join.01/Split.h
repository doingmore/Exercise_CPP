#ifndef SPLIT_H
#define SPLIT_H
#include <vector>
#include <string>
#include <sstream>

template<typename T>
std::vector<T> split(std::string& line, char& separator) // for int,double,float and string
{
	std::vector<T> answer;
	std::string pureLine;
	for (size_t i = 0; i < line.size(); i++)
	{
		if (line[i] != separator)
		{
			pureLine += line[i];
		}
		else if (line[i] == separator)
		{
			pureLine += ' ';
		}
	}
	std::stringstream stream;
	stream << pureLine;
	T element;
	while (stream >> element )
	{
		answer.push_back(element);
	}
	return answer;
}

#endif // !SPLIT_H