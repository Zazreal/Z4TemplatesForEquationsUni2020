#include <iostream>
#include <iomanip>
#include "..\inc\SystemOfLinearEquations.hh"

void Test_SzablonMacierzWyznacznik_double();
void Test_SzablonMacierzWyznacznik_LZespolona();
void SoLE();
void SoLE_Double();
void SoLE_Complex();
void ComplexToMatrix();

int main()
{
	//Test_SzablonMacierzWyznacznik_double();
	//Test_SzablonMacierzWyznacznik_LZespolona();
	ComplexToMatrix();
	SoLE();
	return EXIT_SUCCESS;
}



void Test_SzablonMacierzWyznacznik_double()
{
	TMatrix<double> test;
	std::cin >> test;
	std::cout << test << std::endl;
	std::cout <<"Determinant = " << test.Determinant() << std::endl;
}
void Test_SzablonMacierzWyznacznik_LZespolona()
{
	TMatrix<Complex> test;
	std::cin >> test;
	std::cout << test << std::endl;
	std::cout << "Determinant = " << test.Determinant() << std::endl;
}

void SoLE()
{
	std::cout << std::fixed << std::setprecision(3);
	char str;
	while (true)
	{
		str = 0;
		std::cout << "r or z?\n";
		std::cin >> str;
		if ('r' == str)
		{
			SoLE_Double();
		}
		else if ('z' == str)
		{
			SoLE_Complex();
		}
		else
		{
			std::cout << "Are you sure you want to abort?\n Y/N?" << std::endl;
			str = 0;
			std::cin >> str;
			if ('Y' == str)
			{
				break;
			}
			else if ('N' == str)
			{
				continue;
			}
			else
			{
				continue;
			}
		}


	}
}

void SoLE_Double()
{
	SystemOfLinearEquations<double> test;
	std::cin >> test;
	test.Gauss();
	std::cout << test << std::endl << test.Result();
}

void SoLE_Complex()
{
	SystemOfLinearEquations<Complex> test;
	std::cin >> test;
	test.Gauss();
	std::cout << test << std::endl << test.Result();
}

void ComplexToMatrix()
{
	Complex comp;
	std::cout << "Input Complex number:" << std::endl;
	std::cin >> comp;
	std::vector<std::vector<double>> vec = { { comp.re,-comp.im }, {comp.im, comp.re} };
	TMatrix<double> CM(vec);
	if (comp.Magnitude() == CM.Determinant())
	{
		std::cout << "The Determinant is equal to the Magnitude" << std::endl;
	}
	else
	{
		std::cout << "The Determinant is diffrent from the Magnitude" << std::endl;
	}
}