#include "..\inc\SystemOfLinearEquations.hh"
#include <vector>
/*
 *  Tutaj nalezy zdefiniowac odpowiednie metody
 *  klasy SystemOfLinearEquations, ktore zawieraja
 *  wiecej kodu niz dwie linijki.
 *  Mniejsze metody mozna definiwac w ciele klasy.
 */
/*
std::istream & operator>>(std::istream& stream, SystemOfLinearEquations& system)
{
	std::cout << "Please input the matrix of equations." << std::endl;
	std::cin >> system.Mmatrix;
	return stream;
}

std::ostream & operator<<(std::ostream& stream, const SystemOfLinearEquations& system)
{
	const unsigned int ms = system.Mmatrix.size();
	const unsigned int vs = system.Mmatrix[0].size();
	for (unsigned int i = 0; i < ms; ++i)
	{
		std::cout << "| ";
		for (unsigned int k = 0; k < vs; ++k)
		{
		if(k != ms)
		std::cout << system.Mmatrix[i][k] << " ";
		else if (k == ms) 
		{
			if(i == (ms/2))
				std::cout << "| x_" << i+1 << " | = |" << system.Mmatrix[i][k] << " |";
			else std::cout << "| x_" << i+1 << " |   |" << system.Mmatrix[i][k] << " |";
		}
		}
		std::cout << std::endl;
	}
	return stream;
}

SystemOfLinearEquations::SystemOfLinearEquations(){}

void SystemOfLinearEquations::MatrixInput(Matrix mat)
{
	//uzywa domyslnego copy constructor
	this->Mmatrix = mat;
}

void SystemOfLinearEquations::Gauss()//std::vector < std::vector<double>> matrix) {
{	// tworze zmienna zamiast urzywac matrix.size() wszedzie
	auto matrix = this->Mmatrix.GetMatrix();
	const int unsigned ms = matrix.size();
		for (unsigned int i = 0; i < ms; i++) {
			// szuka maximum w kolumnie
			double maxEl = abs(matrix[i][i]);
			int maxRow = i;
			for (unsigned int k = i + 1; k < ms; k++) {
				if (abs(matrix[k][i]) > maxEl) {
					maxEl = abs(matrix[k][i]);
					maxRow = k;
				}
			}

			// zamienia maxymalny rzad z bierzacym
			for (unsigned int k = i; k < ms + 1; k++) {
				double temp = matrix[maxRow][k];
				matrix[maxRow][k] = matrix[i][k];
				matrix[i][k] = temp;
			}

			// wyzerowuje rzedy ponizej bierzacego
			for (unsigned int k = i + 1; k < ms; k++) {
				double c = -matrix[k][i] / matrix[i][i];
				for (unsigned int j = i; j < ms + 1; j++) {
					if (i == j) {
						matrix[k][j] = 0;
					}
					else {
						matrix[k][j] += c * matrix[i][j];
					}
				}
			}
		}

	// rozwiazuje Ax=b na macierz trojkatna A (matrix)
	std::vector<double> GResult(ms);
	for (int i = ms - 1; i >= 0; i--) {
		GResult[i] = matrix[i][ms] / matrix[i][i];
		for (int k = i - 1; k >= 0; k--) {
			matrix[k][ms] -= matrix[k][i] * GResult[i];
		}
	}
	for (auto el : GResult)
	{
		std::cout << "| " << el << " |" << std::endl;
	}
	//this->result = GResult;
}

/*
TVector<double> SystemOfLinearEquations::Result() const
{
	return this->result;
}
*/
