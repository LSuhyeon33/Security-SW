// Matrix_Struct.cpp : 구조체를 이용한 행렬
//

#include <iostream>
using namespace std;

#define MAX 10
#define NEARLY_ZERO 1e-10

struct Matrix {
    double M[MAX][MAX];
    int row;
    int col;
};

Matrix Mat_init() {
    Matrix M;
    M.row = MAX;
    M.col = MAX;
    for (int i = 0; i < M.row; i++)
        for (int j = 0; j < M.col; j++)
            M.M[i][j] = (i == j) ? 1.0 : 0.0;
    return M;
}

void Mat_print(Matrix M) {
    for (int i = 0; i < M.row; i++) {
        printf("[");
        for (int j = 0; j < M.col; j++) {
            printf("%7.3f", M.M[i][j]);
        }
        printf("]\n");
    }
    printf("\n");
}

void Mat_Mul_1(Matrix A, Matrix B, Matrix& AB) {  // Matrix& AB : call by reference
    if (A.col != B.row) {
        cout << "Matrix size error!\n";
        return;
    }
    AB.row = A.row;
    AB.col = B.col;
    for (int i = 0; i < AB.row; i++) {
        for (int j = 0; j < AB.col; j++) {
            AB.M[i][j] = 0, 0;
            for (int k = 0; k < A.col; k++) {
                AB.M[i][j] += A.M[i][k] * B.M[k][j];
            }
        }
    }
}

Matrix Mat_Mul(Matrix A, Matrix B) {
    Matrix AB;

    if (A.col != B.row) {
        cout << "Matrix size error!\n";
        return A;
    }
    AB.row = A.row;
    AB.col = B.col;
    for (int i = 0; i < AB.row; i++) {
        for (int j = 0; j < AB.col; j++) {
            AB.M[i][j] = 0, 0;
            for (int k = 0; k < A.col; k++) {
                AB.M[i][j] += A.M[i][k] * B.M[k][j];
            }
        }
    }
    return AB;
}

void Mat_Exchange_Row(Matrix& A, int row1, int row2) {
    double temp;
    for (int i = 0; i < A.col; i++) {
        temp = A.M[row1][i];
        A.M[row1][i] = A.M[row2][i];
        A.M[row2][i] = temp;
    }
}

void Mat_Scalar_Mul(Matrix& A, double scalar, int row) {
    for (int i = 0; i < A.col; i++) {
        A.M[row][i] *= scalar;
    }
}

void Mat_Row_Add(Matrix& A, double scalar, int row_src, int row_target) {
    for (int i = 0; i < A.col; i++) {
        A.M[row_target][i] += scalar * A.M[row_src][i];
    }
}

Matrix Mat_inverse(Matrix A) {
    Matrix AA; // [A|I]
    AA.row = A.row;
    AA.col = A.col * 2;
    for (int i = 0; i < A.row; i++) {
        for (int j = 0; j < A.col; j++) {
            AA.M[i][j] = A.M[i][j];
            AA.M[i][A.col + j] = (i == j) ? 1.0 : 0.0;
        }
    }

    int pivot_row;
    for (int j = 0; j < A.col; j++) {
        pivot_row = -1;
        for (int i = j; i < A.row; i++) {
            if (abs(AA.M[i][j]) > NEARLY_ZERO) {
                pivot_row = i;
                break;
            }
        }
        if (pivot_row == -1) {
            cout << "Not invertible!\n";
            return A; // 의미없는 출력
        }
        if (pivot_row != j) { // j번째 행 <-> pivot 행
            Mat_Exchange_Row(AA, j, pivot_row);
        }
        Mat_Scalar_Mul(AA, 1. / AA.M[j][j], j);
        for (int i = 0; i < A.row; i++) {
            if ((i != j) && (abs(AA.M[i][j]) > NEARLY_ZERO)) {
                Mat_Row_Add(AA, -AA.M[i][j], j, i);
            }
        }
    }
    Matrix Inv;
    Inv.row = A.row;
    Inv.col = A.col;
    for (int i = 0; i < A.row; i++) {
        for (int j = 0; j < A.col; j++) {
            Inv.M[i][j] = AA.M[i][j + A.col];
        }
    }
    return Inv;
}

void Run_Matrix_Test() {
    Matrix MA, MB, MC;
    
    MA.row = 3; MA.col = 3;
    MB.row = 3; MB.col = 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            MA.M[i][j] = i + j;
            MB.M[i][j] = j;
        }

    Mat_print(MA);
    Mat_print(MB);
    //Mat_Mul_1(MA, MB, MC);
    MC = Mat_Mul(MA, MB);
    Mat_print(MC);
}

void Run_Matrix_Inverse_Test() {
    Matrix A, InvA;
    double Data[3][3] = { {0.5, -0.25, 0}, {-0.25, 0.5, -0.25}, {0, -0.25, 0.5} };
    A.row = 3;
    A.col = 3;
    for (int i = 0; i < A.row; i++) {
        for (int j = 0; j < A.col; j++) {
            A.M[i][j] = Data[i][j];
        }
    }

    Mat_print(A);
    InvA = Mat_inverse(A);
    Mat_print(InvA);
}

int main()
{
    //Run_Matrix_Test();
    Run_Matrix_Inverse_Test();
}

