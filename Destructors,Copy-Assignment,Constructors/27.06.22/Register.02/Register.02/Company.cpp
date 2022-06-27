#include "Company.h"
#include <sstream>
#include <string>

std::istream& operator>>(std::istream& in, Company& company)
{
	in >> company.id;
	in >> company.name;
	return in;
}

std::ostream& operator<<(std::ostream& out, const Company& company)
{
	out << company.id << " " << company.name;
	return out;
}