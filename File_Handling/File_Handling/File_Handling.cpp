// File_Handling.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>  // 콘솔화면, 키보드용
#include <fstream>  // 파일 입출력용
using namespace std;

void textfile_test_1() {
	ifstream myFile;
	char line1[256], line2[256], line3[256];

	myFile.open("my-text.txt");
	if (myFile.fail()) {
		cout << "File Open Error." << endl;
		return;
	}
	myFile >> line1; // ' '(공백)을 기준으로 구분
	myFile >> line2; // ' '(공백)을 기준으로 구분
	myFile >> line3; // ' '(공백)을 기준으로 구분
	cout << "[OUTPUT] " << line1;
	cout << "[OUTPUT] " << line2;
	cout << "[OUTPUT] " << line3;

	myFile.close();
}

void textfile_test_2() {
	ifstream fin;
	char ch;
	fin.open("my-text.txt");
	if (fin.fail()) {
		cout << "File Open Error." << endl;
		return;
	}

	// f(char x)   -- call by value
	// f(char *x)  -- call by address (x의 주소)
	// f(char &x)  -- call by reference (x의 참조) = (x의 별명)

	char buffer[1024];
	int counter = 0;

	while (fin.get(ch) && (counter < 1024)) {  // .get(char &x) (참조)
		buffer[counter] = ch;
		counter++;
	}

	// 문자열: null trerminating string -- "Hello, world.\0" -- null(\0)=0x00
	buffer[counter] = 0x00;
	cout << buffer;

	fin.close();
}

void iostream_test() {
    printf("Hello, world\n");  // 함수 printf() --> 화면 출력

	cout << "Hello, world." << endl;
	// cout: 클래스 ostream의 특별한 객체(인스턴스, 변수)
	// cout: 콘솔(화면) 출력, cin(istream의 객체): 키보드 입력
	// 구분할 것!  클래스(int)와 객체(num) <----- int num;
	// <<: 연산자(operator) --- 연산자 예: >>, +, -, *, /, %, = (대입연산자)
}

void textfile_test_3() {
	ofstream fout;

	fout.open("output.txt");
	if (fout.fail()) {
		cout << "File Open Error." << endl;
		return;
	}

	const char *line1 = "My string is to be written to a file.";  // literal pool
	char line2[256];

	cout << "Input your line : ";
	cin >> line2; // 사용자 입력 - ' '(공백)으로 구분된 단어 1개만 입력

	fout << line1 << endl;
	fout << line2 << endl;

	fout.close();
}

void textfile_copy() {
	ifstream fin;
	ofstream fout;

	char ch;

	fin.open("C:\\Users\\gus98\\Desktop\\대학\\2학년 2학기\\보안SW구현\\보안_c++\\file-in.txt");
	if (fin.fail()) {
		cout << "Input file open error!" << endl;
		return;
	}
	fout.open("C:\\Users\\gus98\\Desktop\\대학\\2학년 2학기\\보안SW구현\\보안_c++\\file-out.txt");
	if (fout.fail()) {
		cout << "Input file open error!" << endl;
		return;
	}

	while (fin.get(ch)) {
		fout.put(ch);
	}

	fin.close();
	fout.close();
}

// text.file: 문자를 ASCII코드 값으로 저장하는 방식 (A -> 65, 0 -> 49)
// binary file: 바이트 값을 그대로 저장하는 방식 (0 -> 0, 255 -> 255) 실행파일(exe)

void binfile_test_1() {
	ofstream fout;
	char ch;

	fout.open("file1.bin");
	if (fout.fail()) {
		cout << "Binary file open error." << endl;
		return;
	}

	ch = 'A';
	fout.write(&ch, 1);
	unsigned int x = 0xff010203;
	fout.write((char*)&x, sizeof(x)); // sizeof(int)

	fout.close();
}

void binfile_test_2() {
	ofstream fout;
	char ch;

	fout.open("file2.bin", ios::binary);  // c언어 fopen(... ,"wb")
	if (fout.fail()) {
		cout << "Binary file open error." << endl;
		return;
	}

	char block[16];

	for (int j = 0; j < 10; j++) {
         for (int i = 0; i < 16; i++) {
			 block[i] = (char)j * 16 + i;
	     }
		 fout.write(block, 16);  // block[0] == *block, block[1] == *(block+1)
	     // == fout.write(&block[0], 16);
	}

	fout.close();
}

void binfile_copy() {
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

	//while (fin.get(ch)) {
	//	  fout.put(ch);
	//}

	while (fin.read(&ch, 1)) {
		fout.write(&ch, 1);
	}

	fin.close();
	fout.close();
}

int main()
{
	//textfile_test_1();
	//textfile_test_2();
	//textfile_test_3();
	//textfile_copy();
	//binfile_test_1();
	//binfile_test_2();
	binfile_copy();
}
