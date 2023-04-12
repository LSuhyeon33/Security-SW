// Matrix_Basic.cpp : 행렬 기본 연산
//

#include <iostream>

#define MAX 4 // 4x4 행렬

//행렬 출력
void Mat_print(double M[MAX][MAX], int row, int col) {
    for (int i = 0; i < row; i++) {
        printf("[");
        for (int j = 0; j < col; j++) {
            printf("%7.3f", M[i][j]);
        }
        printf("]\n");
    }
}

//행렬 곱셈
void Mat_mul(double MA[MAX][MAX], double MB[MAX][MAX], double MC[MAX][MAX], int row, int col) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            MC[i][j] = 0.0;
            for (int k = 0; k < col; k++) {
                MC[i][j] += MA[i][k] * MB[k][j];
            }
        }
    }
}

void Run_matrix_test() {
    double MA[MAX][MAX] = { {1, 1, 1, 1}, {2, 2, 2, 2}, {3, 3, 3, 3}, {4, 4, 4, 4} };
    double MB[MAX][MAX] = { {1, 0, 1, 1}, {2, 2, 0, 2}, {3, 3, 0, 3}, {4, 4, 4, 0} };
    double MC[MAX][MAX];

    //Mat_print(MA, 4, 4);
    //printf("\n");
    //Mat_print(MB, 4, 4);
    Mat_mul(MA, MB, MC, 4, 4);
    printf("\n");
    Mat_print(MC, 4, 4);
}

int main()
{
    Run_matrix_test();

    return 0;
}
