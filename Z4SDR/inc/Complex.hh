#ifndef HH_COMPLEX
#define HH_COMPLEX

#include <iostream>

struct Complex
{
	double re = 0; /*! Pole repezentuje czesc rzeczywista. */
	double im = 0; /*! Pole repezentuje czesc urojona. */
	Complex();
	Complex(double z);
	Complex(double x,double y);
	~Complex();
	Complex operator+(Complex other);
	//Complex operator-(Complex& other);
	Complex operator-(Complex other);
	Complex operator*(Complex& other);
	Complex operator*(const double& other);
	Complex operator/(Complex& other);
	Complex operator!(); //sprzezenie
	bool operator==(Complex& other);
	Complex& operator*=(Complex& other);
	Complex& operator-=(Complex& other);
	Complex& operator+=(const Complex& other);
	//Complex operator=(std::string& str); //nie dokonczone
	bool operator==(const Complex & other) const;
	bool operator==(const double& other) const;
	bool operator>(const Complex& other) const;
	bool operator<(const Complex& other) const;
	double Magnitude();
};

double Arg(Complex& z);
std::istream& operator>>(std::istream& strea, Complex& com);
std::ostream& operator<<(std::ostream& stream,const Complex& com);
//funkcja pokazujaca pobieranie complex bez string parsingu
void InputComplex(Complex& com);
Complex abs(Complex& given);


//atan2 look up == arctg
#endif // !HH_COMPLEX