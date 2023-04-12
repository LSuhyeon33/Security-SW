// Week3_Matrix.cpp : 행렬 기본 연산
//

#include <iostream>
using namespace std;

//=========(Week 2) GF 연산 함수들 (시작)

typedef unsigned char byte;

//GF 다항식 출력
void GF_print(byte gf) {
	int coef;

	printf("%d = %02x = ", gf, gf);
	for (int i = 7; i >= 0; i--) {
		coef = (gf >> i) & 0x01;
		if (coef == 1) {
			std::cout << " + " << "x^" << i;
		}
	}
	std::cout << std::endl;
}

//GF(2^8) 덧셈
byte GF_add(byte gf1, byte gf2) {
	return gf1 ^ gf2; // XOR
}

//GF(2^8) xtime() 함수
byte GF_xtime(byte gf) {
	int msb; // x^7의 계수
	byte result; // 결과

	msb = (gf >> 7) & 0x01;
	if (msb == 1) {
		result = (gf << 1) ^ 0x1b;
	}
	else {
		result = gf << 1;
	}
	return result;
}

//GF(2^8) xtime_simple() 함수
byte GF_xtime_simple(byte gf) {
	return(((gf >> 7) & 0x01) == 1 ? (gf << 1) ^ 0x1b : gf << 1);
}

//GF(2^8) 곱셈
byte GF_mul(byte f, byte g) {
	byte h; // 곱셈 결과 h(x) = f(x)*g(x)
	int coef; // 계수
	h = 0x00;
	for (int i = 7; i >= 0; i--) {
		coef = (f >> i & 0x01); // a7, a6, a5, ... , a0
		h = GF_xtime(h);
		if (coef == 1) {
			h = GF_add(h, g);
		}
	}
	return h;
}

//GF(2^8) 역원: (a^255 = 1)임을 이용한다.
// a^(-1) = a^(254) = a^(1111 1110) = a^2*a^4*a^8*a^16*...*a^128
// a^(1111 1110) = a^(1000 0000) * a^(0100 0000) *...* a^(0000 0010)
byte GF_inv(byte f) {
	byte f_inv; // 역원(결과값)
	byte temp; // 중간에 곱할 값(a^n): a^2, a^4, a^8, ... , a^128
	f_inv = 1;
	temp = f;
	for (int i = 0; i < 7; i++) {
		temp = GF_mul(temp, temp);
		f_inv = GF_mul(f_inv, temp);
	}
	return f_inv;
}

//=========(Week 2) GF 연산 함수들 (끝)

int main()
{
    cout << "Hello World!\n";
}
