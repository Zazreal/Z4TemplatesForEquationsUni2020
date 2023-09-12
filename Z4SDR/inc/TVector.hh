#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#ifndef HH_TVECTOR
#define HH_TVECTOR

/*
	Klasa Vector zawiera std::vector
	dzieki czemu nie potrzebny jest znany rozmiar.
	Wszystkie metody klasy sluza do jego obslugi.
 */
template<typename T>
T string_to_template(std::string str);

template<typename type>
class TVector
{
private:
	std::vector<type> vector;
public:
	TVector();
	TVector(std::vector<type>& vec);
	~TVector();
	void SetVector(std::vector<type>& other);
	TVector operator=(const std::vector<type>& other);
	TVector operator+(const TVector& other) const;
	TVector operator-(const TVector& other) const;
	TVector operator-();
	TVector operator*(const TVector& other) const;
	TVector operator*(const double multiplier) const;
	TVector operator/(const double divider) const;
	double operator[](const int index) const;
	double& operator[](const int index);
	friend std::istream & operator>>(std::istream& stream, TVector& vec)
	{
		std::string temp;
		type temp2;
		std::cout << "Inputing Vector, write \"stop\" to end input. " << std::endl;
		while (true)
		{
			getline(stream, temp);
			if ("stop" == temp) break;
			temp2 = string_to_template<type>(temp);
			vec.vector.emplace_back(temp2);
		}
		std::cout << "Vector input ended" << std::endl;
		return stream;
	}

	friend std::ostream &operator<<(std::ostream& stream, const TVector& vec)
	{
		for (unsigned int i = 0; i < vec.vector.size(); i++) {
			std::cout << "| x" << i + 1 << " | " << vec.vector[i] << " |" << std::endl;
		}
		return stream;
	}
};

template<typename type>
TVector<type>::TVector()
{
}
template<typename type>
TVector<type>::TVector(std::vector<type>& vec) : vector{ vec }
{
}

template<typename type>
TVector<type>::~TVector<type>()
{
}

template<typename type>
void TVector<type>::SetVector(std::vector<type>& other)
{
	this->vector = other;
}

template<typename type>
TVector<type> TVector<type>::operator=(const std::vector<type>& other)
{
	this->vector = other;
	return *this;
}

template<typename type>
TVector<type> TVector<type>::operator+(const TVector& other) const
{
	//std::transform(this->vector.begin(), this->vector.end(), other.vector.begin(), this->vector.begin(), std::plus<int>());
	std::vector<type> vec;
	if (this->vector.size() == other.vector.size()) {
		for (int i = 0; i < this->vector.size(); ++i)
		{
			vec.emplace_back(this->vector[i] + other.vector[i]);
		}
	}
	else std::cerr << "You Cant add vectors of diffrent sizes" << std::endl;
	return Vector(vec);
}

template<typename type>
TVector<type> TVector<type>::operator-(const TVector& other) const
{
	std::vector<type> vec;
	if (this->vector.size() == other.vector.size()) {
		for (int i = 0; i < this->vector.size(); ++i)
		{
			vec.emplace_back(this->vector[i] - other.vector[i]);
		}
	}
	else std::cerr << "You Cant subtract vectors of diffrent sizes" << std::endl;
	return Vector(vec);
}

template<typename type>
TVector<type> TVector<type>::operator-()
{
	for (type element : this->vector)
		element *= (-1);
	return Vector(this->vector);
}

template<typename type>
TVector<type> TVector<type>::operator*(const TVector& other) const
{
	std::vector<type> vec;
	if (this->vector.size() == other.vector.size()) {
		for (unsigned int i = 0; i < this->vector.size(); ++i)
		{
			vec.emplace_back(this->vector[i] * other.vector[i]);
		}
	}
	return Vector(vec);
}

template<typename type>
TVector<type> TVector<type>::operator*(const double multiplier) const
{
	std::vector<type> vec;
	for (auto element : this->vector)
		vec.emplace_back(element * multiplier);
	return Vector(vec);
}

template<typename type>
TVector<type> TVector<type>::operator/(const double divider) const
{
	std::vector<type> vec;
	for (auto element : this->vector)
		vec.emplace_back(element / divider);
	return TVector<type>(vec);
}

template<typename type>
double TVector<type>::operator[](const int index) const
{
	try {
		return (this->vector).at(index % this->vector.size());
	}
	catch (std::out_of_range& e) {
		std::cerr << e.what() << std::endl;
		return (this->vector).at(0);
	}
}

template<typename type>
double& TVector<type>::operator[](const int index)
{
	try {
		return (this->vector).at(index % this->vector.size());
	}
	catch (std::out_of_range& e) {
		std::cerr << e.what() << std::endl;
		return (this->vector).at(0);
	}
}


template<typename T>
T string_to_template(std::string str)
{
	T TC;
	std::stringstream convert(str);
	convert >> TC;
	return TC;
}

#endif