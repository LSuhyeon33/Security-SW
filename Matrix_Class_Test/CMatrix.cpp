#include "CMatrix.h"

void CMatrix::Print() {
    for (int i = 0; i < row; i++) {
        printf("[");
        for (int j = 0; j < col; j++) {
            printf("%7.3f", M[i][j]);
        }
        printf(" ]\n");
    }
    printf("\n");
}

CMatrix CMatrix::Add(CMatrix A) {
    // HW2: 함수 내용 채우기
    CMatrix c;  // 생성자 CMatrix() 호출

    c.ReSize(row, col);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            c.SetValue(i, j, M[i][j] + A.GetValue(i, j));
        }
    }
    return c;
}

CMatrix CMatrix::Add(CMatrix A, CMatrix B) {
    CMatrix C;
    int r, c;
    r = A.GetRow();
    c = A.GetCol();

    C.ReSize(r, c);
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            C.SetValue(i, j, A.GetValue(i, j) + B.GetValue(i, j));
        }
    }
    return C;
}

/*
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
    //HW2: 정사각행렬인지 확인하는 코드
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            M[i][j] = A.GetValue(i, j);
        }
    }
}

void CMatrix::Print(const char* pName) {
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
    // HW2: 함수 내용 채우기
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
    // HW2: 함수 내용 채우기
}
*/