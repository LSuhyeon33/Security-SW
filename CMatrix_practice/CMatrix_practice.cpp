#include "CMatrix.h"

// 정적 변수의 초기화 (함수밖에서)
//The initialisation of the static variable must be done outside of any function.
int CMat::Counter = 0;

void CMat_test() {
    double dataA[3][3] = { 1, 0, 0, 0, 1, 2, 0, 2, 1 };
    double dataB[3][3] = { 1, 2, 3, 2, 3, 1, 3, 1, 2 };

    CSQMat A(3);
    CSQMat B(3);
    CSQMat C(3);
    CSQMat D(3);
    CMat F(2, 3);
    CMat G;
    double tr_a = 0, tr_b = 0;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            A.SetValue(i, j, dataA[i][j]);
            B.SetValue(i, j, dataB[i][j]);
        }
    }
    printf("A = \n");
    A.Print();
    printf("B = \n");
    B.Print();

    tr_a = A.Tr();
    tr_b = B.Tr();
    printf("Trace Tr(A) = %7.6f\n", tr_a);
    printf("Trace Tr(B) = %7.6f\n", tr_b);

    C = CMat::Mul(A, B);
    printf("\nAB = \n");
    C.Print();
    D = CMat::Mul(B, A);
    printf("BA = \n");
    D.Print();

    double dataC[2][3] = { 1, 2, 3, 0, 1, 2 };

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            F.SetValue(i, j, dataC[i][j]);
        }
    }

    printf("\nA = \n");
    A.Print();
    printf("D = \n");
    F.Print();

    G = CMat::Add(A, F);
    G.Print();
    
    printf("\nDet(A) = %1.0f", A.Det());

}

void Matrix_Inv_test() {

}

int main()
{

    CMat_test();
    //Matrix_Inv_test();

    /*
    CMat C;
    CSQMat D;
    //
    D = (CSQMat) C;  // 생성자 CSQMat(CMat A) 호출
    */

    cout << endl << "Matrix Counter = " << CMat::GetConter() << endl;
}
