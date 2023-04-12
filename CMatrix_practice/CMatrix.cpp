#include <iostream>
#include "CMatrix.h"

CMat::CMat(int r, int c, double data[MAX][MAX]) {
    row = r;
    col = c;
    if ((r > MAX) || (c > MAX)) {
        printf("[Error] The size (%d, %d) is too Large!\n", r, c);
        return;
    }
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            M[i][j] = data[i][j];
        }
    }
    IncreaseCounter();
}


CSQMat::CSQMat(CMat A) { // cast 연산자처럼 사용한다.
    row = A.GetRow();
    col = A.GetCol();

    if (row == col) {
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                M[i][j] = A.GetValue(i, j);
            }
        }
    }
    else {
        cout << "The sizes of two matrixes are not equal!\n";
    }
}


void CMat::Print(const char* pName) {
    if (pName != nullptr) {
        cout << pName << " = " << endl;
    }
    for (int i = 0; i < row; i++) {
        printf("[");
        for (int j = 0; j < col; j++) {
            printf("%7.3f", M[i][j]);
        }
        printf(" ]\n");
    }
    printf("\n");
}

void CMat::ScalarMul(double value) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            M[i][j] *= value;
        }
    }
}

CMat CMat::Add(CMat M1, CMat M2) {
    CMat A;
    int r1 = M1.GetRow();
    int c1 = M1.GetCol();
    int r2 = M2.GetRow();
    int c2 = M2.GetCol();
    CMat C;

    if ((r1 == r2) && (c1 == c2)) {
        for (int i = 0; i < r1; i++) {
            for (int j = 0; j < c1; j++) {
                C.SetValue(i, j, M1.GetValue(i, j) + M2.GetValue(i, j));
            }
        }
        return C;
    }
    else {
        printf("[Error]The sizes of two matrixes are not equal!\n");
        printf("%s + %s = %s = \n", 'A', 'D', 'F');
        return A;
    }
}


void CMat::Mat_Exchange_Row(int row1, int row2) {
    double temp;
    for (int i = 0; i < col; i++) {
        temp = M[row1][i];
        M[row1][i] = M[row2][i];
        M[row2][i] = temp;
    }
}

void CMat::Mat_Scalar_Mul(double scalar, int row) {
    for (int i = 0; i < col; i++) {
        M[row][i] *= scalar;
    }
}

void CMat::Mat_Row_Add(double scalar, int row_src, int row_target) {
    for (int i = 0; i < col; i++) {
        M[row_target][i] += scalar * M[row_src][i];
    }
}

CMat CMat::Mul(CMat A, CMat B) {
    CSQMat AB;
    double result = 0.0;
    int r = A.GetRow();
    int c = A.GetCol();

    if ((CSQMat(A).GetSize()) != (CSQMat(B).GetSize())) {
        cout << "The sizes of two matrixes are not equal!\n";
    }
    AB.SetSize(r);
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < r; j++) {
            for (int k = 0; k < c; k++) {
                result += A.GetValue(i, k) * B.GetValue(k, j);
            }
            AB.SetValue(i, j, result);
            result = 0;
        }
    }
    return AB;
}

//===============
double CSQMat::Det() {
    double det;
    int sign, c_pos;
    CSQMat Adj(row - 1);

    if (row == 1) return GetValue(0, 0);

    //Adj.SetSize(row - 1, col - 1);
    det = 0.0;
    sign = -1;

    for (int c = 0; c < col; c++) {
        sign = sign * (-1);
        for (int i = 1; i < row; i++) {
            c_pos = 0;
            for (int j = 0; j < col; j++) {
                if (j != c) {
                    Adj.SetValue(i - 1, c_pos, M[i][j]);
                    c_pos++;
                }
            }
        }
        //Adj.Print();
        det += sign * GetValue(0, c) * Adj.Det();
        //cout << "sign*det(Adj) = " << sign*Adj.Det() << endl;
    }
    return det;
}


CSQMat CSQMat::Inv() {
    CSQMat MatInv(row);
    if (GetSize() * 2 > MAX) {
        cout << "[Error] Matrix is too large!" << endl;
        return MatInv;  //의미없는 출력
    }
    CMat AA(row, 2 * col);

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            AA.SetValue(i, j, GetValue(i, j));
            AA.SetValue(i, col + j, (i == j) ? 1.0 : 0.0);
        }
    }

    int pivot_row;
    for (int j = 0; j < col; j++) {
        pivot_row = -1;
        for (int i = j; i < row; i++) {
            if (abs(AA.GetValue(i, j)) > NEARLY_ZERO) {
                pivot_row = i;
                break;
            }
        }
        if (pivot_row == -1) {
            cout << "[Error] Not invertible!\n";
            return MatInv;  //의미없는 출력
        }
        if (pivot_row != j) {  // j번째 행 <--> pivot 행
            AA.Mat_Exchange_Row(j, pivot_row);
        }
        AA.Mat_Scalar_Mul(1. / AA.GetValue(j, j), j);
        for (int i = 0; i < row; i++) {
            if ((i != j) && (abs(AA.GetValue(i, j)) > NEARLY_ZERO)) {
                AA.Mat_Row_Add(-AA.GetValue(i, j), j, i);
            }
        }
    }
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            MatInv.SetValue(i, j, AA.GetValue(i, j + col));
        }
    }
    return MatInv;
}

double CSQMat::Tr() {
    CSQMat M;
    double sum = 0.0;
    int r = M.GetRow();

    for (int i = 0; i < r; i++) {
        sum += M.GetValue(i, i);
    }
    return sum;
}