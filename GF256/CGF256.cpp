#include <iostream>
#include "CGF256.h"

//GF 16���� ���
void CGF256::PrintAsHex() {
	printf(" %02x ", mData);
}

//GF ���׽� ���
void CGF256::PrintAsPolynomial() {
	int coef;

	for (int i = 7; i >= 0; i--) {
		coef = (mData >> i) & 0x01;
		if (coef == 1) {
			std::cout << " + " << "x^" << i;
		}
	}
	std::cout << std::endl;
}

//GF(2^8) ����
CGF256 CGF256::Add(CGF256 x) {
	CGF256 result;

	result.SetValue(mData ^ x.GetValue());  // z = y ^ x
	return result;
}

//GF(2^8) xtime() �Լ�
CGF256 CGF256::xtime() {
	byte gf = mData;
	return ((((gf >> 7) & 0x01) == 1) ? (gf << 1) ^ 0x1b : gf << 1);
}

//GF(2^8) ����
// f(x) = a0 + a1*x + a2*x^2 + ... + a7*x^7
// h(x) = g(x)*f(x)
//      = g(x)*a0 + g(x)*a1*x + g(x)*a2*x^2 + ... + g(x)*a7*x^7
//      = g(x)*a0 + x*( g(x)*a1* + g(x)*a2*x + ... + g(x)*a7*x^6 )
//      = g(x)*a0 + x*( g(x)*a1* + x*( g(x)*a2 + ... + g(x)*a7*x^5 ) )
//      = g(x)*a0 + x*( ... + x*( g(x)*a7 ) )
CGF256 CGF256::Mul(CGF256 x) {
	CGF256 result;

	int coef; // ���
	byte f = mData;
	result.SetValue(0x00);
	for (int i = 7; i >= 0; i--) {
		coef = (f >> i & 0x01); // a7, a6, a5, ... , a0
		result = result.xtime();
		if (coef == 1) {
			result = result.Add(x);
		}
	}
	return result;
}

//GF(2^8) ����: (a^255 = 1)���� �̿��Ѵ�.
// a^(-1) = a^(254) = a^(1111 1110) = a^2*a^4*a^8*a^16*...*a^128
// a^(1111 1110) = a^(1000 0000) * a^(0100 0000) *...* a^(0000 0010)
CGF256 CGF256::Inv() {
	CGF256 f_inv; // ����(�����)
	CGF256 temp; // �߰��� ���� ��(a^n): a^2, a^4, a^8, ... , a^128
	f_inv.SetValue(0x01);
	temp.SetValue(mData);
	for (int i = 0; i < 7; i++) {
		temp = temp.Mul(temp); // temp = temp*temp
		f_inv = f_inv.Mul(temp);
	}
	return f_inv;
}
