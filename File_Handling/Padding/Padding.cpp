// Padding.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <fstream> 
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

void padding_test() {
	ifstream fin;
	ofstream fout;

	char ch;

	fin.open("C:\\Users\\gus98\\Desktop\\대학\\2학년 2학기\\보안SW구현\\보안_c++\\file-in.bin", ios::binary);
	if (fin.fail()) {
		cout << "Input file open error!" << endl;
		return;
	}
	fout.open("C:\\Users\\gus98\\Desktop\\대학\\2학년 2학기\\보안SW구현\\보안_c++\\file-out.bin", ios::binary);
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
	num_block = file_size / 16 + 1;
	remainder = file_size - (num_block - 1) * 16;

	byte buffer[16];
	for (int i = 0; i < num_block - 1; i++) {
		fin.read((char*)buffer, 16);
		fout.write((char*)buffer, 16);
	}

	byte out_buffer[16];

	for (int i = 0; i < remainder; i++) {
		fin.read(&ch, 1);
		buffer[i] = ch;
	}
	padding(buffer, remainder, out_buffer);
	fout.write((char*)out_buffer, 16);

	fin.close();
	fout.close();
}

int main()
{
    padding_test();
}
