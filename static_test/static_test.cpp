// static_test.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

using namespace std;

//int counter; // 전역 변수

// Fibonacci 수열
static int f(int n) {
    static int counter;  // 정적 변수 (초기화 할 수 없다.(0으로 자동 초기화))

    counter++;
    if ((counter % 5) == 0) {
         cout << "counter = " << counter << endl;
    }
    if (n <= 1) {
        return 1;
    }
    else {
        return f(n - 1) + f(n - 2);
    }
}

void static_c_test() {

    int n = 10;
    cout << "f(" << n << ")=" << f(n) << endl;
    //cout << "counter = " << counter;
}

int main()
{
    static_c_test();
}
