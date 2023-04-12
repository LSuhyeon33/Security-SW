﻿// File_Enc.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <fstream> 
#include "AES32.h"
using namespace std;
typedef unsigned char byte;

// in[]: 16바이트 이하의 바이트열
// out[16]: 16바이트 (0x80 패딩) 0x80 = 1000 0000
void padding(byte in[], int in_length, byte out[16]) {
    byte pad_byte = 0x80;
    for (int i = 0; i < in_length; i++) {
        out[i] = in[i];
    }
    out[in_length] = 0x80;
    for (int i = in_length + 1; i < 16; i++) {
        out[i] = 0x00;
    }
} 

int pt_length(byte padded[16]) {
    int position80;
    position80 = 15;
    for (int i = 15; i > 0; i--) {
        if (padded[i] != 0x00) break;
        position80--;
    }
    if (padded[position80] != 0x80) {
        cout << "Padding error: 0x80 not found." << endl;
        // (1) 0x00이 끝나는 지점에서 0x80이 없을 때,
        // (2) 0x00이 계속 나올 때
        return -1;  // (1) or (2)
    }
    else {
        return position80;
    }
}

// 암호화
void AES_Enc_ECB(const char* pPT, byte key[16], const char* pCT) {
    ifstream fin;
    ofstream fout;

    char ch;

    fin.open(pPT, ios::binary);
    if (fin.fail()) {
        cout << "Input file open error!" << endl;
        return;
    }
    fout.open(pCT, ios::binary);
    if (fout.fail()) {
        cout << "Input file open error!" << endl;
        return;
    }

    // 파일의 크기 알아보기
    int file_size;
    fin.seekg(0, fin.end);  // 파일포인터를 맨 뒤로
    file_size = fin.tellg();  // 현재 파일 포인터의 위치를 말하면
    cout << "Input File Size = " << file_size << endl;
    fin.seekg(0, fin.beg);  // 파일포인터를 맨 앞으로

    int num_block, remainder;
    num_block = file_size / 16 + 1;
    remainder = file_size - (num_block - 1) * 16;
     
    byte pt[16], ct[16];
    u32 rk[11][4];

    AES32_Enc_KeySchedule(key, rk);

    for (int i = 0; i < num_block - 1; i++) {
        fin.read((char*)pt, 16);
        AES32_Encrypt(pt, rk, ct);  // 암호화
        fout.write((char*)ct, 16);
    }

    byte pt_pad[16];
    for (int i = 0; i < remainder; i++) {
        fin.read(&ch, 1);
        pt[i] = ch;
    }
    padding(pt, remainder, pt_pad);
    AES32_Encrypt(pt_pad, rk, ct);  // 암호화
    fout.write((char*)ct, 16);

    fin.close();
    fout.close();
}

// 복호화
void AES_Dec_ECB(const char* pCT, byte key[16], const char* pDecPT) {
    ifstream fin;
    ofstream fout;

    char ch;

    fin.open(pCT, ios::binary);
    if (fin.fail()) {
        cout << "Input file open error!" << endl;
        return;
    }
    fout.open(pDecPT, ios::binary);
    if (fout.fail()) {
        cout << "Input file open error!" << endl;
        return;
    }

    // 파일의 크기 알아보기
    int file_size;
    fin.seekg(0, fin.end);  // 파일포인터를 맨 뒤로
    file_size = fin.tellg();  // 현재 파일 포인터의 위치를 말하면
    cout << "Input File SIze = " << file_size << endl;
    fin.seekg(0, fin.beg);  // 파일포인터를 맨 앞으로

    int num_block, remainder;
    num_block = file_size / 16;  // 암호화된 블록의 개수
    remainder = file_size - num_block * 16; 
    if (remainder != 0) {
        cout << "File size Error (Not a multiple fo 16)" << endl;
        return;
    }

    byte pt[16], ct[16];
    u32 rk[11][4];

    AES32_Dec_KeySchedule(key, rk);

    for (int i = 0; i < num_block - 1; i++) {
        fin.read((char*)ct, 16);
        AES32_EqDecrypt(ct, rk, pt);  // 복호화
        fout.write((char*)pt, 16);
    }

    // 마지막 블록
    int last_pt_len;  // 마지막 블록의 실제 데이터 길이 (0~15)
    fin.read((char*)ct, 16);
    AES32_EqDecrypt(ct, rk, pt);
    last_pt_len = pt_length(pt);

    for (int i = 0; i < last_pt_len; i++) {
        ch = pt[i];
        fout.write(&ch, 1);
    }

    fin.close();
    fout.close();
}

void File_ECB_test() {
    const char* pPT = "C:\\Users\\gus98\\Desktop\\대학\\2학년 2학기\\보안SW구현\\보안_c++\\PT.bin";
    const char* pCT = "C:\\Users\\gus98\\Desktop\\대학\\2학년 2학기\\보안SW구현\\보안_c++\\CT.bin";
    const char* pDecPT = "C:\\Users\\gus98\\Desktop\\대학\\2학년 2학기\\보안SW구현\\보안_c++\\DecPT.bin";

    byte key[16] = { 0, };
    for (int i = 0; i < 16; i++) {
        key[i] = i;
    }

    cout << "AES ECB Encrypt..." << endl;
    AES_Enc_ECB(pPT, key, pCT);

    cout << "AES ECB Decrypt..." << endl;
    AES_Dec_ECB(pCT, key, pDecPT);
 
}

int main()
{
    File_ECB_test();
}
