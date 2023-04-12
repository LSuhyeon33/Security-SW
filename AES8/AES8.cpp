#include <iostream>
#include <time.h>

using namespace std;

typedef unsigned char byte; //새로운 데이터 타입 : byte = GF(2^8)

byte Sbox[256] = {
	0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
	0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
	0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
	0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
	0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
	0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
	0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
	0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
	0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
	0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
	0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
	0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
	0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
	0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
	0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
	0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 };
byte ISbox[256] = {
	0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
	0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
	0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
	0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
	0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
	0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
	0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
	0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
	0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
	0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
	0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
	0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
	0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
	0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
	0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
	0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d };

void AES8_SubBytes(byte in[16], byte out[16]) {
	for (int i = 0; i < 16; i++) {
		out[i] = Sbox[in[i]];
	}
}

void AES8_ShiftRows(byte in[16], byte out[16]) {
	out[0] = in[0];
	out[4] = in[4];
	out[8] = in[8];
	out[12] = in[12];

	out[1] = in[5];
	out[5] = in[9];
	out[9] = in[13];
	out[13] = in[1];

	out[2] = in[10];
	out[6] = in[14];
	out[10] = in[2];
	out[14] = in[6];

	out[3] = in[15];
	out[7] = in[3];
	out[11] = in[7];
	out[15] = in[11];
}

//GF(2^8) xtime() 함수
byte GF_xtime(byte gf) {
	return ((((gf >> 7) & 0x01) == 1) ? (gf << 1) ^ 0x1b : gf << 1);
}

void AES_MixColumn(byte in[16], byte out[16]) {
	out[0] = GF_xtime(in[0]) ^ GF_xtime(in[1]) ^ in[1] ^ in[2] ^ in[3];
	out[1] = in[0] ^ GF_xtime(in[1]) ^ GF_xtime(in[2]) ^ in[2] ^ in[3];
	out[2] = in[0] ^ in[1] ^ GF_xtime(in[2]) ^ GF_xtime(in[3]) ^ in[3];
	out[3] = GF_xtime(in[0]) ^ in[0] ^ in[1] ^ in[2] ^ GF_xtime(in[3]);

	out[4] = GF_xtime(in[4]) ^ GF_xtime(in[5]) ^ in[5] ^ in[6] ^ in[7];
	out[5] = in[4] ^ GF_xtime(in[5]) ^ GF_xtime(in[6]) ^ in[6] ^ in[7];
	out[6] = in[4] ^ in[5] ^ GF_xtime(in[6]) ^ GF_xtime(in[7]) ^ in[7];
	out[7] = GF_xtime(in[4]) ^ in[4] ^ in[5] ^ in[6] ^ GF_xtime(in[7]);

	out[8] = GF_xtime(in[8]) ^ GF_xtime(in[9]) ^ in[9] ^ in[10] ^ in[11];
	out[9] = in[8] ^ GF_xtime(in[9]) ^ GF_xtime(in[10]) ^ in[10] ^ in[11];
	out[10] = in[8] ^ in[9] ^ GF_xtime(in[10]) ^ GF_xtime(in[11]) ^ in[11];
	out[11] = GF_xtime(in[8]) ^ in[8] ^ in[9] ^ in[10] ^ GF_xtime(in[11]);

	out[12] = GF_xtime(in[12]) ^ GF_xtime(in[13]) ^ in[13] ^ in[14] ^ in[15];
	out[13] = in[12] ^ GF_xtime(in[13]) ^ GF_xtime(in[14]) ^ in[14] ^ in[15];
	out[14] = in[12] ^ in[13] ^ GF_xtime(in[14]) ^ GF_xtime(in[15]) ^ in[15];
	out[15] = GF_xtime(in[12]) ^ in[12] ^ in[13] ^ in[14] ^ GF_xtime(in[15]);
}

void AES8_AddRoundkey(byte in[16], byte roundkey[16], byte out[16]) {
	for (int i = 0; i < 16; i++) {
		out[i] = in[i] ^ roundkey[i];
	}
}

void AES8_Round(byte in[16], byte rk[16], byte out[16]) {
	byte state1[16], state2[16];

	AES8_SubBytes(in, state1);
	AES8_ShiftRows(state1, state2);
	AES_MixColumn(state2, state1);
	AES8_AddRoundkey(state1, rk, out);
}

void AES8_Encrypt(byte PT[16], byte RK[11][16], byte CT[16]) {
	byte state1[16], state2[16];

	AES8_AddRoundkey(PT, RK[0], state1);
	for (int i = 1; i < 10; i++) {
		AES8_Round(state1, RK[i], state2);
		for (int j = 0; j < 16; j++) {
			state1[j] = state2[j];
		}
	}
	// 10R
	AES8_SubBytes(state1, state2);
	AES8_ShiftRows(state2, state1);
	AES8_AddRoundkey(state1, RK[10], CT);
}

// 암호화 중간값 출력
void AES_print_state(byte state[16], const char* msg = nullptr) {
	if (msg != nullptr) {
		printf("%s = ", msg);
	}
	for (int i = 0; i < 16; i++) {
		printf("%02x ", state[i]);
	}
	printf("\n");
}