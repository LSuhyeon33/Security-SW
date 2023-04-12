// complex.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
using namespace std;

class Complex {
private:
	double real;
	double imag;
	static int Counter; // 정적변수 --> Data segment에 저장
public:
	//constructor(생성자)
	//Complex() {}; // default constructor
	Complex(double x = 0., double y = 0.); // parameterized constructor
	// destructor(소멸자)
	~Complex();
	// Copy Constructor
	Complex(Complex& c); // default copy constructor: 멤버변수의 복사(shallow copy)

	void SetValue(Complex c);
	void SetValue(double x=0, double y=0); // default parameter(argument) => =0은 값이 주어지지 않을 때
	void Print(const char* pStr = nullptr);
	void static CounterPrint() { cout << "Counter = " << Counter << endl; };

	// 연산들..
	double Re() { return real; };
	double Im() { return imag; };
	double Abs() { return sqrt(real * real + imag * imag); };
	Complex static Add(Complex c1, Complex c2);
	Complex static Mul(Complex c1, Complex c2);
	Complex Conjugate();
};

Complex::Complex(double x, double y) {
	Counter++; // 카운터: 생성될때마다 1증가
	printf("(Constructor) Counter = %d\n", Counter);
	real = x;
	imag = y;
};

Complex::Complex(Complex& c) {
	Counter++; // 카운터: 생성될때마다 1증가
	printf("(Copy Constructor) Counter = %d\n", Counter);
	real = c.real;
	imag = c.imag;
};

Complex::~Complex() {
	Counter--;
	printf("(Destructor) Counter = %d\n", Counter);
};

Complex Complex::Add(Complex c1, Complex c2) {
	Complex z;
	z.SetValue(c1.Re() + c2.Re(), c1.Im() + c2.Im()); // z.real = c1.real + c2.real;
	return z;
}
 
Complex Complex::Mul(Complex c1, Complex c2) {
	Complex z;
	// 각자 계산하세요.
	return z;
}

inline void Complex::SetValue(Complex c) {
	real = c.real;
	imag = c.imag;
}

inline void Complex::SetValue(double x, double y) { // 함수 이름이 같음 => overloading
	real = x;
	imag = y;
}

void Complex::Print(const char* pStr) {
	if (pStr != nullptr) {
		printf("%s = ", pStr);
	}
	printf("%6.3f + %6.3f i\n", real, imag);
}

Complex Complex::Conjugate() {
	Complex z;
	z.real = real;
	z.imag = - imag;

	return z;
}

/*
void struct_like_class_test()
{
	Complex c1, c2, c3;

	c1.real = 1.;
	c1.imag = 2.;
	c2.real = 2.;
	c2.imag = 5.;

	c3.real = c1.real + c2.real;
	c3.imag = c1.imag + c2.imag;

	printf("c1 = %6.3f + %6.3f i\n", c1.real, c1.imag);
	printf("c2 = %6.3f + %6.3f i\n", c2.real, c2.imag);
	printf("c3 = %6.3f + %6.3f i\n", c3.real, c3.imag);

}
*/

void complex_class_test() {
	Complex c1, c2, c3;

	c1.SetValue(1., 2.);
	c1.Print("c1");
	c2 = c1; // 대입 ==> Shallow Copy 얕은 복사
	c2.Print("c2");

	c3 = Complex::Add(c1, c2);
	c3.Print("c3");

	Complex::CounterPrint();
}

void complex_ftn_test() {
	Complex c1(1., 2.), c2, c3;

	c2.SetValue(c1);
	c3.SetValue(10.);

	c1.Print("c1");
	c2.Print("c2");
	c3.Print("c3");

	cout << "c1 = " << c1.Re() << " + " << c1.Im() << "i" << endl;
	cout << "|c1| = " << c1.Abs() << endl;

	c3 = c1.Conjugate();
	c3.Print();

	c1.CounterPrint();
}

int Complex::Counter = 0; // Class의 정적멤버 초기화 (함수영역 밖에서)

int main()
{
	//struct_like_class_test();
	complex_class_test();
	//complex_ftn_test();
	Complex::CounterPrint();
}