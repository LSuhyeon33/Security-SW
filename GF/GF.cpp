// Week2_GF.cpp
//

#include <iostream>

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

//GF(2^8) xtime() 함수
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

//AES Affine Aw+b (w = x^(-1))
byte AES_Affine(byte w) {
	byte A[8][8] = {
	{1, 0, 0, 0, 1, 1, 1, 1},
	{1, 1, 0, 0, 0, 1, 1, 1},
	{1, 1, 1, 0, 0, 0, 1, 1},
	{1, 1, 1, 1, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 0, 0, 0},
	{0, 1, 1, 1, 1, 1, 0, 0},
	{0, 0, 1, 1, 1, 1, 1, 0},
	{0, 0, 0, 1, 1, 1, 1, 1}
	};
	byte b_vec[8] = { 1, 1, 0, 0, 0, 1, 1, 0 };
	byte w_vec[8], y_vec[8], y;

	for (int i = 0; i < 8; i++) {
		w_vec[i] = (w >> i) & 0x01;
	}

	for (int i = 0; i < 8; i++) {
		y_vec[i] = b_vec[i];
		for (int j = 0; j < 8; j++) {
			y_vec[i] ^= A[i][j] * w_vec[j];
		}
	}

	y = 0;
	byte temp_bit;
	for (int i = 0; i < 8; i++) {
		temp_bit = y_vec[i] << i;
		y ^= temp_bit;
	}
	return y;
}

//AES S-box 만들기
void Get_AES_Sbox(byte sbox[256]) {
	byte temp;
	// 0^(-1) = 0 으로 간주한다.
	sbox[0] = AES_Affine(0);
	for (int i = 1; i < 256; i++) {
		temp = GF_inv(i);
		sbox[i] = AES_Affine(temp);
	}
}

//AES Inv S-box 만들기
void Get_AES_Inv_Sbox(byte isbox[256]) {
	byte Sbox[256];
	Get_AES_Sbox(Sbox);
	for (int i = 0; i < 256; i++) {
		isbox[Sbox[i]] = i;
	}
}
//연습용 함수
void GF_test() {
	byte gf1, gf2, gf3;
	
	gf1 = 0x04; // x^2 = 0000 0100 = 0x04 = 4
	gf2 = 0x1b;

	GF_print(gf1);
	GF_print(gf2);

	gf3 = GF_add(gf1, gf2);
	GF_print(gf3);

	//xtime
	gf1 = 0x80; // 1000 0000 = 128 = x^7
	gf2 = GF_xtime(gf1);
	GF_print(gf1);
	GF_print(gf2);
	
	gf1 = 0x10; // 0001 0000
	gf2 = 0x08; // 0000 1000
	gf3 = GF_mul(gf1, gf2);
	GF_print(gf1);
	GF_print(gf2);
	GF_print(gf3);
	
	gf2 = GF_inv(gf1);
	gf3 = GF_mul(gf1, gf2);
	GF_print(gf1);
	GF_print(gf2);
	GF_print(gf3);
}

void Sbox_test() {
	byte Sbox[256];
	Get_AES_Sbox(Sbox);

	std::cout << "Sbox = ";
	for (int i = 0; i < 256; i++) {
		if ((i % 16) == 0) printf("\n");
		printf("%02x ", Sbox[i]);
	}

	byte ISbox[256];
	Get_AES_Inv_Sbox(ISbox);

	std::cout << "\nISbox = ";
	for (int i = 0; i < 256; i++) {
		if ((i % 16) == 0) printf("\n");
		printf("%02x ", ISbox[i]);
	}
}

int main()
{
	//GF_test();
	Sbox_test();

	return 0;
}


