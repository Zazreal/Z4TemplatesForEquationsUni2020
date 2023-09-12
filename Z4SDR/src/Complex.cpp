#define _USE_MATH_DEFINES
#include "..\inc\Complex.hh"
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <math.h>
//funkcja pokazujaca pobieranie complex bez string parsingu
void InputComplex(Complex& com)
{	//mam pomysl tutaj na skrocona notacje za pomoca _getch() ale raczej nie o to chodzi, poza tym getch ma swoje problemy
	//w innym wypadku mam inny pomysl, ale bedzie to po prostu brzydkie
	char n, n2, i;
	std::cin >> n >> com.re >> com.im >> i >> n2;
	if (n != '(' || n2 != ')')
	{
		std::cerr << "Error: Wrong input" << std::endl;
	}
}

Complex abs(Complex & given)
{
	Complex TR;
	TR = given;
	if (given.re < 0)
		TR.re = given.re * -1;
	if (given.im < 0)
		TR.im = given.im * -1;
	return  TR;
}

double Arg(Complex& z)
{
	double return_value = 0;
	if (z.re > 0) return_value = atan2(z.im, z.re);
	else if (z.re < 0 && z.im >= 0) return_value = atan2(z.im, z.re) + M_PI;
	else if (z.re < 0 && z.im < 0) return_value = atan2(z.im, z.re) - M_PI;
	else if (z.re == 0 && z.im > 0) return_value = M_PI_2;
	else if (z.re == 0 && z.im < 0) return_value = -M_PI_2;
	else std::cerr << "The argument is indeterminant!" << std::endl;
	return return_value;
}


std::ostream& operator<<(std::ostream& stream,const Complex& com){
  
	stream << "("  << com.re << std::showpos << com.im
		<< "i)" << std::noshowpos; //std::setprecision(2)
  return stream;
}

//operator overload, ktory robi string parsing
std::istream& operator>>(std::istream& stream, Complex& com) {
	/*
	To jest moja nadinterpretacja polecen
	Wczytuje podane dane jako string (w jednej linijce wszystko)
	i parsuje na liczbe zespolona. wydaje mi sie, ze roznica miedzy sugerowanym a tym to jest tylko wpisywanie
	dane podaje sie tak: (x+-yi) ex: (4+3i), (432523-52345i), (-765+412i). w jednej linii jako string!!!
	*/
	std::string input = " ";
	std::string input2 = " ";
	stream >> input;
	input.erase(std::remove_if(input.begin(), input.end(), isspace), input.end()); // usuwam wszelkie spacje
	if (input[0] != '(' || input[input.size() - 1] != ')')  // sprawdzam czy sa dobre nawiasy i czy wogole sa
	{
		std::cerr << "blad: zle podana liczba urojona" << std::endl;
	}
	else
	{
		//std::cout << "input: " << input << std::endl;
		input2 = input.substr(1,input.size()-2); //usuwam nawiasy
		//std::cout << "input2: " << input2 << std::endl;
	}
	if (input2[0] == '-')   //zrobilem tak bo nie wiedzialem jak inaczej to sparsowac
	{						//jesli czesc RE jest ujemna to usuwam ten minus zebym nie musial pisac 2 roznych rzeczy
							//w ten sposob czesc parsujaca kiedy RE jest ujemne i dodatnie jest praktycznie taka sama, co bylo dla mnie latwiesze
		input2 = input2.substr(1, input.size() - 1);
		if(input2.find('+') != std::string::npos)   //sprawdzam czy IM jest dodatnie
		{
			int pos = input2.find('+');				//dostaje lokacje znaku +
			std::string re = input2.substr(0,pos);  //rozdzielam input2 na 2 rozne stringi RE i IM, ktore sa juz tylko liczbami
			std::string im = input2.substr(pos,input2.size()-pos-2);
			try {						  //to wszystko w try blocku bo stod moze rzucic exception
				com.re = stod(re) * (-1); //funkcja stod przetwarza string na double, tutaj prof. Janiec mowil ze jest jakas utrata danych, (tutaj RE bylo ujemne dlatego * (-1))
				com.im = stod(im);		  //ale ja o niczym nie wiem
			}
			catch (std::invalid_argument &e) //lapie exception
			{
				std::cerr << e.what() << std::endl;  //wyswietlam je
			}
			//std::cout << "Complex number:" << com << std::endl;
		}
		else if (input2.find('-') != std::string::npos) // tutaj powtorka z tego co wczesniej tylko ze IM jest ujemne
		{
			int pos = input2.find('-');
			std::string re = input2.substr(0, pos);
			std::string im = input2.substr(pos, input2.size() - pos - 2);
			try {
				 com.re= stod(re) * (-1);
				com.im = stod(im);
			}
			catch (std::invalid_argument &e)
			{
				std::cerr << e.what() << std::endl;
			}
			//std::cout << "Complex number:" << com << std::endl;
		}
		else if (input2[input2.size() - 1] == 'i') // skrocona notacja jest w tym momencie banalna,
		{										   // bo jesli poprzednie przypadki nie istnieja to input musial byc w skroconej notacji
			std::string im = input2.substr(0, input2[input2.size() - 2]); //usuwam 'i'
			try {														  //reszta jest mniej wiecej taka sama jak poprzednio
				com.im = stod(im);
			}
			catch (std::invalid_argument &e)
			{
				std::cerr << e.what() << std::endl;
			}
		}
		else
		{
			try {
				com.re= stod(input2) * (-1);
			}
			catch (std::invalid_argument &e)
			{
				std::cerr << e.what() << std::endl;
			}
		}
	}
	else //to jest kiedy RE jest dodatnie, dzieje sie prawie to samo co kiedy jest ujemne, tylko ze nie mnoze RE przez -1
	{	 //zdaje sobie sprawe ze moglem z tego zrobic funkcje, ale napisalem to tak to juz zostawie, i tak to bylo ctrl+c , ctrl+v
		if (input2.find('+') != std::string::npos)
		{
			int pos = input2.find('+');
			std::string re = input2.substr(0, pos);
			std::string im = input2.substr(pos, input2.size() - pos - 1);
			try{
			com.re = stod(re);
			com.im = stod(im);
			}
			catch (std::invalid_argument &e)
			{
			std::cout << e.what();
			}
			//std::cout << "Complex number:" << com << std::endl;
		}
		else if (input2.find('-') != std::string::npos)
		{
			int pos = input2.find('-');
			std::string re = input2.substr(0, pos);
			std::string im = input2.substr(pos, input2.size() - pos - 1);
			try{
			com.re = stod(re);
			com.im = stod(im);
			}
			catch (std::invalid_argument &e)
			{
				std::cout << e.what();
			}
			//std::cout << "Complex number:" << com << std::endl;
		}
		else if (input2[input2.size() - 1] == 'i')
		{				
			//std::cout << "input2: " << input2 << std::endl;
			std::string im = input2.substr(0, input2[input2.size() - 2]); 
			try {														  
				com.im = stod(im);
			}
			catch (std::invalid_argument &e)
			{
				std::cout << e.what();
			}
		}
		else
		{
			//std::cout << "input2: " << input2 << std::endl;
			try {
				com.re = stod(input2);
			}
			catch (std::invalid_argument &e)
			{
				std::cout << e.what();
			}
		}
	}
	return stream;
}


Complex::Complex()
{
}

Complex::Complex(double z) : re{z}, im{z}
{
}

Complex::Complex(double x, double y) : re{ x }, im{ y }
{
}

Complex::~Complex(){}

Complex Complex::operator+(Complex other)
{
	return Complex(this->re + other.re, this->im + other.im);
}

/*Complex Complex::operator-(Complex & other)
{
	return Complex(this->re - other.re, this->im - other.im);
}*/

Complex Complex::operator-(Complex other)
{
	return Complex(this->re - other.re, this->im - other.im);
}

Complex Complex::operator*(Complex & other)
{
	return Complex(this->re * other.re - this->im * other.im,
		this->im * other.re + this->re * other.im);
}

Complex Complex::operator*(const double & other)
{
	return Complex(this->re * other, this->im * other);
}

Complex Complex::operator/(Complex & other)
{
	Complex temp;
	Complex other2 = !other;
	temp = *this * other2;
	double mod = other.re * other.re + other2.im * other2.im;
	if (0 == mod)
	{
		std::cerr << "Error: Division by 0 is impossible" << std::endl;
		return Complex(0, 0);
	}
	return Complex(temp.re/mod , temp.im/mod);
}

Complex Complex::operator!()
{
	return Complex(this->re, -(this->im));;
}

bool Complex::operator==(Complex & other)
{
	if (this->re == other.re && this->im == other.im) return true;
	else return false;
}

Complex& Complex::operator*=(Complex & other)
{
	*this = *this - other;
	return *this;
}

Complex& Complex::operator-=(Complex & other)
{
	*this = *this - other;
	return *this;
}

Complex& Complex::operator+=(const Complex & other)
{
	*this = *this + other;
	return *this;
}


bool Complex::operator==(const Complex& other) const
{
	if (abs(this->re - other.re) < pow(10, -15) && abs(this->im - other.im) < pow(10, -15)) return true;
	else return false;
}

bool Complex::operator==(const double & other) const
{
	if (abs(this->re - other) < pow(10, -15) && this->im == 0) return true;
	else return false;
}

bool Complex::operator>(const Complex & other) const
{
	double C1 = sqrt(pow(this->re, 2) + pow(this->im, 2));
	double C2 = sqrt(pow(other.re, 2) + pow(other.im, 2));
	if (C1 > C2) return true;
	else return false;
}

bool Complex::operator<(const Complex & other) const
{
	double C1 = sqrt(pow(this->re, 2) + pow(this->im, 2));
	double C2 = sqrt(pow(other.re, 2) + pow(other.im, 2));
	if (C1 < C2) return true;
	else return false;
}

double Complex::Magnitude()
{
	return sqrt(pow(this->re, 2) + pow(this->im, 2));
}
