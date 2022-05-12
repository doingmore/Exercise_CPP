#ifndef CAR_H
#define CAR_H

using namespace std;

class Car
{
private:
	std::string m_brand;
	std::string m_model;
	int m_year;
public:
	Car(std::string brand, std::string model, int year) : m_brand{brand}, m_model{model}, m_year{ year }
	{
	}

	std::string getBrand() const { return m_brand; }
	std::string getModel() const { return m_model; }
	int getYear() const { return m_year; }

};



#endif // !CAR_H