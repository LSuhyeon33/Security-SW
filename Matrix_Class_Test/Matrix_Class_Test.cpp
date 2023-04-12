// Matrix_Class_Test.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include "CMatrix.h"

void matrix_test() {
    CMatrix A;
    CMatrix B(2, 2);
    CMatrix C, D;

    A.ReSize(2, 2);
    double a[2][2] = { 1, 2, 3, 4 };
    double b[2][2] = { 10, 20, 30, 40 };

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            A.SetValue(i, j, a[i][j]);
            B.SetValue(i, j, b[i][j]);
        }
    }

    A.Print();
    B.Print();

    C = A.Add(B);
    C.Print();

    D = CMatrix::Add(A, B);
    D.Print();

    cout << "Matrix Counter = " << CMatrix::GetCounter() << endl;
}

// 전역변수처럼 설정이 필요 (CMatrix::counter 정적변수)
int CMatrix::counter = 0;

int main()
{
    matrix_test();
}
