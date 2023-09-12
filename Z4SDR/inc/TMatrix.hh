#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "Complex.hh"
/*
	Klasa zawiera 2D array zrobiona z std::vector
	w ten sposob mozna ja dynamicznie zwiekszac
	i nie potrzebny jest znany rozmiar w trakcie deklaracji.
	Wszystkie metody klasy sluza do obslugi tej macierzy.
 */

#ifndef HH_TMATRIX
#define HH_TMATRIX



template<typename T>
T string_to_template(std::string str);

template<typename type>
class TMatrix
{
private:
	std::vector<std::vector<type>> matrix;
public:
	TMatrix();
	TMatrix(std::vector<std::vector<type>>& m);
	~TMatrix();
	int size() const;
	void PrintMatrix() const;
	void Transposition();
	type Determinant();
	type DeterminantP();
	std::vector<std::vector<type>>& GetMatrix();
	TMatrix operator*(const TMatrix& other) const;
	TMatrix operator*(const double other) const;
	std::vector<type> operator[](const unsigned int index) const;
	std::vector<type>& operator[](const unsigned int index);
	//Matrix operator!();
	friend std::ostream& operator<<(std::ostream& stream, const TMatrix& matrix)
	{
		for (std::vector<type> vector : matrix.matrix)
		{
			stream << " |";
			for (auto element : vector) {
				stream << " " << element;
			}
			stream << " | " << std::endl;;
		}
		return stream;
	}
	friend std::istream& operator>>(std::istream& stream, TMatrix& matrix)
	{
		//funkcja przetestowana, dziala bez zarzutow
		std::vector<type> temp(0); //tymczasowy wektor do ulatwienia pracy
		std::string element; // potrzebne do pobrania danych
		type input;
		int vecsize = 0;
		bool pass = 0;
		std::cout << "Starting input, enter \"=\" to input last element in row, enter \"stop\" to stop" << std::endl;
		while (true) {										//potrzeba 2 loopy rzeby wypelnic 2D tablice (tutaj vectory)
			while (true)
			{
				std::cout << "Input element: ";
				stream >> element;
				if ("stop" == element) break;
				else if ("=" == element) {						// = sluzy za loop breaker
					std::cout << "Input last element: ";
					stream >> element;
					input = string_to_template<type>(element);
					temp.emplace_back(input);
					break;
				}
				else
				{
					input = string_to_template<type>(element);
					temp.emplace_back(input);
				}
			}
			if (pass == false) {							//ten caly kawalek odpowiada za sprawdzanie rozmiaru macierzy
				vecsize = temp.size(); pass = true;
			}
			if (temp.size() != vecsize)
			{
				temp.clear();
				if ("stop" == element) break;
				std::cerr << "Wrong vector size, try again" << std::endl;
				continue;
			}												//tu sie konczy sprawdzanie rozmiaru
			matrix.matrix.emplace_back(temp);				//wrzucam vektor do macierzy
			temp.clear();									//czyszcze wektor do pozniejszego uzytku
			if ("stop" == element) break;
		}
		return stream;
	}
};

template<typename type>
TMatrix<type>::TMatrix()
{
}

template<typename type>
TMatrix<type>::TMatrix(std::vector<std::vector<type>>& m) : matrix{ m }
{
	for (int i = 0; i<this->matrix.size();++i)
	{
		matrix[i].emplace_back(0);
	}
}

template<typename type>
TMatrix<type>::~TMatrix()
{
}

template<typename type>
int TMatrix<type>::size() const
{
	return this->matrix.size();
}

template<typename type>
void TMatrix<type>::PrintMatrix() const
{
	for (std::vector<type> vector : matrix)
	{
		for (auto element : vector) {
			std::cout << " | " << element;
		}
		std::cout << " | " << std::endl;
	}
}

template<typename type>
void TMatrix<type>::Transposition()
{
}

//Sa dwie funkcje wyznacznika, jedna zmienia macierz (P) , a druga nie
//Determinant Liczy wyznacznik
template<typename type>
type TMatrix<type>::Determinant()
{
	auto matrix = this->matrix;
	const int unsigned ms = matrix.size();
	for (unsigned int i = 0; i < ms; i++) {
		// szuka maximum w kolumnie
		type maxEl = abs(matrix[i][i]);
		int maxRow = i;
		for (unsigned int k = i + 1; k < ms; k++) {
			if (abs(matrix[k][i]) > maxEl) {
				maxEl = abs(matrix[k][i]);
				maxRow = k;
			}
		}
		
		// zamienia maxymalny rzad z bierzacym
		for (unsigned int k = i; k < ms + 1; k++) {
			type temp = matrix[maxRow][k];
			matrix[maxRow][k] = matrix[i][k];
			matrix[i][k] = temp;
		}

		// wyzerowuje rzedy ponizej bierzacego
		for (unsigned int k = i + 1; k < ms; k++) {
			type c = (matrix[k][i] / matrix[i][i]) * -1;
			for (unsigned int j = i; j < ms + 1; j++) {
				if (i == j) {
					matrix[k][j] = matrix[k][j] * 0;
				}
				else {
					matrix[k][j] += (c * matrix[i][j]);
				}
			}
		}
	}

	type det = 1;
	for (unsigned int i = 0; i < ms; ++i) {
		det *= matrix[i][i];
	}
	return det;
}

template<>
inline Complex TMatrix<Complex>::Determinant()
{
	auto matrix = this->matrix;
	const int unsigned ms = this->matrix.size();
	for (int i = 0; i < ms; ++i) {
		// szuka maximum w kolumnie
		Complex maxEl = matrix[i][i];
		int maxRow = i;
		for (int k = i + 1; k < ms; ++k) {
			if (matrix[k][i] > maxEl) {
				maxEl = matrix[k][i];
				maxRow = k;
			}
		}

		// zamienia maxymalny rzad z bierzacym
		for (int k = i; k < ms + 1; ++k) {
			Complex temp = matrix[maxRow][k];
			matrix[maxRow][k] = matrix[i][k];
			matrix[i][k] = temp;
		}

		// wyzerowuje rzedy ponizej bierzacego
		for (int k = i + 1; k < ms; ++k) {
			Complex c = (matrix[k][i] / matrix[i][i]) * -1;
			for (int j = i; j < ms + 1; ++j) {
				if (i == j) {
					matrix[k][j] = matrix[k][j] * 0;
				}
				else {
					matrix[k][j] = matrix[k][j] + (c * matrix[i][j]);
				}
			}
		}
	}

	Complex det(0, 0);
	for (int i = 0; i < ms; ++i) {
		if (0 == det.re)
		{
			if (0 != matrix[i][i].re)
			{
				det.re += 1;
			}
		}
		if (0 == det.im)
		{
			if (0 != matrix[i][i].im)
			{
				det.im += 1;
			}
		}
		det = det * matrix[i][i];
	}
	return det;
}
//DeterminantP liczy wyznacznik I zmienia tablice (P == pointer)
template<typename type>
inline type TMatrix<type>::DeterminantP()
{
	const int unsigned ms = this->matrix.size();
	for (unsigned int i = 0; i < ms; ++i) {
		// szuka maximum w kolumnie
		type maxEl = abs(matrix[i][i]);
		int maxRow = i;
		for (unsigned int k = i + 1; k < ms; ++k) {
			if (abs(matrix[k][i]) > maxEl) {
				maxEl = abs(matrix[k][i]);
				maxRow = k;
			}
		}

		// zamienia maxymalny rzad z bierzacym
		for (unsigned int k = i; k < ms + 1; ++k) {
			type temp = matrix[maxRow][k];
			matrix[maxRow][k] = matrix[i][k];
			matrix[i][k] = temp;
		}

		// wyzerowuje rzedy ponizej bierzacego
		for (unsigned int k = i + 1; k < ms; ++k) {
			type c = (matrix[k][i] / matrix[i][i]) * -1;
			for (unsigned int j = i; j < ms + 1; ++j) {
				if (i == j) {
					matrix[k][j] = matrix[k][j] * 0;
				}
				else {
					matrix[k][j] += (c * matrix[i][j]);
				}
			}
		}
	}

	type det = 1;
	for (unsigned int i = 0; i < ms; ++i) {
		det *= matrix[i][i];
	}
	return det;
}

template<>
inline Complex TMatrix<Complex>::DeterminantP()
{
	const int unsigned ms = this->matrix.size();
	for (int i = 0; i < ms; ++i) {
		// szuka maximum w kolumnie
		Complex maxEl = matrix[i][i];
		int maxRow = i;
		for (int k = i + 1; k < ms; ++k) {
			if (matrix[k][i] > maxEl) {
				maxEl = matrix[k][i];
				maxRow = k;
			}
		}

		// zamienia maxymalny rzad z bierzacym
		for (int k = i; k < ms + 1; ++k) {
			Complex temp = matrix[maxRow][k];
			matrix[maxRow][k] = matrix[i][k];
			matrix[i][k] = temp;
		}

		// wyzerowuje rzedy ponizej bierzacego
		for (int k = i + 1; k < ms; ++k) {
			Complex c = (matrix[k][i] / matrix[i][i]) * -1;
			for (int j = i; j < ms + 1; ++j) {
				if (i == j) {
					matrix[k][j] = matrix[k][j] * 0;
				}
				else {
					matrix[k][j] = matrix[k][j] + (c * matrix[i][j]);
				}
			}
		}
	}

	Complex det(0, 0);
	for (int i = 0; i < ms; ++i) {
		if (0 == det.re)
		{
			if (0 != matrix[i][i].re)
			{
				det.re += 1;
			}
		}
		if (0 == det.im)
		{
			if (0 != matrix[i][i].im)
			{
				det.im += 1;
			}
		}
		det = det * matrix[i][i];
	}
	return det;
}


template<typename type>
std::vector<std::vector<type>>& TMatrix<type>::GetMatrix()
{
	return this->matrix;
}

template<typename type>
TMatrix<type> TMatrix<type>::operator*(const TMatrix & other) const
{
	//Probowalem zrobic algorytm Strassena, ale mi nie wychodzilo
	//wiec postanowilem zrobic zwyklym sposobem
	const unsigned int msr1 = this->matrix.size();
	const unsigned int msc2 = other.matrix[0].size();
	const unsigned int msc1 = this->matrix[0].size();
	//Szczerze mowiac, lepiej sie czuje z std::vector niz zwyklymi 2D array
	std::vector<type> vec(0, msr1);
	std::vector < std::vector<type> > temp(msc2, vec);
	if (msr1 == msc2)
	{
		for (int i = 0; i < msr1; ++i)
		{
			for (int j = 0; j < msc2; ++j)
			{
				for (int k = 0; k < msc1; ++k)
				{
					temp[i][j] += (*this)[i][k] * other[k][j];
				}
			}
		}
	}
	else std::cerr << "Wrong Matrix sizes" << std::endl;
	return Matrix(temp);
}

template<typename type>
TMatrix<type> TMatrix<type>::operator*(const double other) const
{
	std::vector<type> vec;
	std::vector < std::vector<type> > temp;
	for (auto vec : this->matrix)
	{
		for (auto el : vec)
		{
			vec.emplace_back(el*other);
		}
		temp.emplace_back(vec);
		vec.clear();
	}
	return Matrix(temp);
}

template<typename type>
std::vector<type> TMatrix<type>::operator[](const unsigned int index) const
{
	try {
		return (this->matrix).at(index % this->matrix.size());
	}
	catch (std::out_of_range& e) {
		std::cerr << e.what() << std::endl;
		return (this->matrix).at(0);
	}
}

template<typename type>
std::vector<type>& TMatrix<type>::operator[](const unsigned int index)
{
	try {
		return (this->matrix).at(index % this->matrix.size());
	}
	catch (std::out_of_range& e) {
		std::cerr << e.what() << std::endl;
		return (this->matrix).at(0);
	}
}
#endif // !HH_TMATRIX