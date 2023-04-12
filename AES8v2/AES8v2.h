#pragma once
typedef unsigned char byte; //새로운 데이터 타입 : byte = GF(2^8)

byte GF_xtime(byte gf);

void AES8v2_SubBytes(byte state[16]);
void AES8v2_ShiftRows(byte state[16]);
void AES8v2_MixColumn(byte state[16]);
void AES8v2_AddRoundkey(byte state[16], byte roundkey[16]);
void AES8_Round(byte state[16], byte rk[16]);
void AES8_Encrypt(byte PT[16], byte RK[11][16], byte CT[16]);

void AES_print_state(byte state[16], const char* msg = nullptr);