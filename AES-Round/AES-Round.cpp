// Week4-AES-Round.cpp : AES 암호화 함수 (키스케줄 제외)
//

#include <iostream>
using namespace std;

//====== (Week 2) GF 연산 함수들 (시작)

typedef unsigned char byte; //새로운 데이터 타입 : byte = GF(2^8)

//GF 다항식 출력
void GF_print(byte gf)
{
    int coef;

    printf("%d = %02x = ", gf, gf);
    for (int i = 7; i >= 0; i--)
    {
        coef = (gf >> i) & 0x01;
        if (coef == 1)
        {
            std::cout << " + " << " x^" << i;
        }
    }
    std::cout << std::endl;
}

//GF(2^8) 덧셈
byte GF_add(byte gf1, byte gf2)
{
    return gf1 ^ gf2; //덧셈 = XOR
}

//GF(2^8) xtime()함수
byte GF_xtime(byte gf)
{
    int msb; //x^7의 계수
    byte result; //결과

    msb = (gf >> 7) & 0x01;
    if (msb == 1)
    {
        result = (gf << 1) ^ 0x1b;
    }
    else
    {
        result = gf << 1;
    }
    return result;
}

//GF(2^8) xtime()함수
byte GF_xtime_simple(byte gf)
{
    return ((gf >> 7) & 0x01 == 1 ? (gf << 1) ^ 0x1b : gf << 1);
}

//GF(2^8) 곱셈
// f(x) = a0 + a1*x + a2*x^2 + a3*x^3 + ... + a7*x^7
// h(x) = g(x)*f(x)
//      = g(x)*a0 + g(x)*a1*x + g(x)*a2*x^2 + g(x)*a3*x^3 + ... + g(x)*a7*x^7
//      = g(x)*a0 + x*( g(x)*a1 + g(x)*a2*x + g(x)*a3*x^2 + ... + g(x)*a7*x^6 )
//      = g(x)*a0 + x*( g(x)*a1 + x*( g(x)*a2 + g(x)*a3*x + ... + g(x)*a7*x^5)  )
//      = g(x)*a0 + x*( ...    + x* (g(x)*a7) ) )
byte GF_mul(byte f, byte g)
{
    byte h; //곱셈 결과 h(x) = f(x)*g(x)
    int coef; //계수
    h = 0x00;
    for (int i = 7; i >= 0; i--)
    {
        coef = (f >> i) & 0x01; // a7, a6, a5, ... ,a0
        h = GF_xtime(h);
        if (coef == 1)
        {
            h = GF_add(h, g);

        }
    }
    return h;
}

//GF(2^8) 역원 : (a^255 = 1)임을 이용한다
// a^(-1) = a^(254) = a^(1111 1110) = a^2*a^4*a^8*a^16*... *a^128
// a^(1111 1110) = a^(1000 0000) * a^(0100 0000) * a^(0010 0000) * ... * a^(0000 0010)
byte GF_inv(byte f) {
    byte f_inv; // 역원(결과값)
    byte temp; //중간에 곱할 값(a^n) : a^2, a^4, a^8, a^16, ... , a^128
    f_inv = 1;
    temp = f;
    for (int i = 0; i < 7; i++)
    {
        temp = GF_mul(temp, temp);
        f_inv = GF_mul(f_inv, temp);
    }
    return f_inv;
}

//====== (Week 2) GF 연산 함수들 (끝)

//AES Affine Aw+b (w = x^(-1))
byte AES_Affine(byte w) {
    byte A[8][8] = {
    {1, 0, 0, 0, 1, 1, 1, 1},
    {1, 1, 0, 0, 0, 1, 1, 1},
    {1, 1, 1, 0, 0, 0, 1, 1},
    {1, 1, 1, 1, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 0, 0, 0},
    {0, 1, 1, 1, 1, 1, 0, 0},
    {0, 0, 1, 1, 1, 1, 1, 0},
    {0, 0, 0, 1, 1, 1, 1, 1}
    };
    byte b_vec[8] = { 1, 1, 0, 0, 0, 1, 1, 0 };
    byte w_vec[8], y_vec[8], y;

    for (int i = 0; i < 8; i++) {
        w_vec[i] = (w >> i) & 0x01;
    }

    for (int i = 0; i < 8; i++) {
        y_vec[i] = b_vec[i];
        for (int j = 0; j < 8; j++) {
            y_vec[i] ^= A[i][j] * w_vec[j];
        }
    }

    y = 0;
    byte temp_bit;
    for (int i = 0; i < 8; i++) {
        temp_bit = y_vec[i] << i;
        y ^= temp_bit;
    }
    return y;
}

//====== GF의 행렬 연산 (시작)

#define MAX 10

struct GF_Matrix {
    byte M[MAX][MAX];
    int row;
    int col;
};

GF_Matrix GF_Mat_init()
{
    GF_Matrix M;
    M.row = MAX;
    M.col = MAX;
    for (int i = 0; i < M.row; i++)
        for (int j = 0; j < M.col; j++)
            M.M[i][j] = (i == j) ? 0x01 : 0x00;
    return M;
}

void GF_Mat_print(GF_Matrix M)
{
    for (int i = 0; i < M.row; i++)
    {
        printf("[");
        for (int j = 0; j < M.col; j++)
        {
            printf(" %02x", M.M[i][j]);
        }
        printf(" ]\n");
    }
    printf("\n");
}

GF_Matrix GF_Mat_Mul(GF_Matrix A, GF_Matrix B)   // return GF_Matrix
{
    GF_Matrix AB;
    byte temp;

    if (A.col != B.row)
    {
        cout << "Matrix size error ! \n";
        return A;
    }
    AB.row = A.row;
    AB.col = B.col;
    for (int i = 0; i < AB.row; i++)
    {
        for (int j = 0; j < AB.col; j++)
        {
            AB.M[i][j] = 0x00;
            for (int k = 0; k < A.col; k++)
            {
                //AB.M[i][j] += A.M[i][k] * B.M[k][j];
                temp = GF_mul(A.M[i][k], B.M[k][j]);
                AB.M[i][j] = GF_add(AB.M[i][j], temp);
            }
        }
    }
    return AB;
}

void GF_Mat_Exchange_Row(GF_Matrix& A, int row1, int row2)
{
    byte temp;
    for (int i = 0; i < A.col; i++)
    {
        temp = A.M[row1][i];
        A.M[row1][i] = A.M[row2][i];
        A.M[row2][i] = temp;
    }
}

void GF_Mat_Scalar_Mul(GF_Matrix& A, byte scalar, int row)
{
    byte temp;
    for (int i = 0; i < A.col; i++)
    {
        //A.M[row][i] *= scalar;
        temp = GF_mul(A.M[row][i], scalar);
        A.M[row][i] = temp;
    }
}

void GF_Mat_Row_Add(GF_Matrix& A, byte scalar, int row_src, int row_target)
{
    byte temp;
    for (int i = 0; i < A.col; i++)
    {
        //A.M[row_target][i] += scalar * A.M[row_src][i];
        temp = GF_mul(scalar, A.M[row_src][i]);
        A.M[row_target][i] = GF_add(A.M[row_target][i], temp);
    }
}

GF_Matrix GF_Mat_inverse(GF_Matrix A)
{
    GF_Matrix AA;
    AA.row = A.row;
    AA.col = A.col * 2;

    for (int i = 0; i < A.row; i++)
    {
        for (int j = 0; j < A.col; j++)
        {
            AA.M[i][j] = A.M[i][j];
            AA.M[i][A.col + j] = (i == j) ? 0x01 : 0x00;
        }
    }

    int pivot_row;
    for (int j = 0; j < A.col; j++)
    {
        pivot_row = -1;
        for (int i = j; i < A.row; i++)
        {
            if (AA.M[i][j] != 0x00)
            {
                pivot_row = i;
                break;
            }
        }
        if (pivot_row == -1)
        {
            cout << "Not inertible!\n";
            return A; //의미없는 출력
        }
        if (pivot_row != j) //j번째 행 <-> pivot 행
        {
            GF_Mat_Exchange_Row(AA, j, pivot_row);
        }

        byte temp;
        temp = GF_inv(AA.M[j][j]);
        GF_Mat_Scalar_Mul(AA, temp, j);

        for (int i = 0; i < A.row; i++)
        {
            if ((i != j) && (AA.M[i][j] != 0))
            {
                GF_Mat_Row_Add(AA, AA.M[i][j], j, i); // x+x=0 in GF

            }
        }
    }


    GF_Matrix Inv;
    Inv.row = A.row;
    Inv.col = A.col;
    for (int i = 0; i < A.row; i++)
    {
        for (int j = 0; j < A.col; j++)
        {
            Inv.M[i][j] = AA.M[i][j + A.col];
        }
    }
    return Inv;
}

void Run_GF_matrix_test()
{
    byte MixCol[4][4] = { {0x02, 0x03, 0x01, 0x01}, {0x01, 0x02, 0x03, 0x01},
                            {0x01, 0x01, 0x02, 0x03}, {0x03, 0x01, 0x01, 0x02} };


    GF_Matrix MC, InvMC;

    MC.row = 4;
    MC.col = 4;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            MC.M[i][j] = MixCol[i][j];
        }
    }
    GF_Mat_print(MC);

    InvMC = GF_Mat_inverse(MC);
    GF_Mat_print(InvMC);

    //
    GF_Matrix MC2, MC4, InvMC2, InvMC4;
    MC2 = GF_Mat_Mul(MC, MC);
    MC4 = GF_Mat_Mul(MC2, MC2);
    GF_Mat_print(MC2);
    GF_Mat_print(MC4);

    InvMC2 = GF_Mat_Mul(InvMC, InvMC);
    InvMC4 = GF_Mat_Mul(InvMC2, InvMC2);
    GF_Mat_print(InvMC2);
    GF_Mat_print(InvMC4);
}

//====== GF의 행렬 연산 (끝)

//====== AES 암호화 라운드 함수 (시작)

// 암호화 중간값 출력
void AES_print_state(byte state[16], const char *msg = nullptr) {
    if (msg != nullptr) {
        printf("%s = ", msg);
    }
    for (int i = 0; i < 16; i++) {
        printf("%02x ", state[i]);
    }
    printf("\n");
}

void AES_AddRoundKey(byte in[16], byte key[16], byte out[16]) {  // 라운드 키를 XOR 연산
    for (int i = 0; i < 16; i++) {
        out[i] = in[i] ^ key[i];
    }
}

// y = Sbox(x) = Aw + b, (w = x^{-1})
void AES_SubByte(byte in[16], byte out[16]) {  // 각 바이트에서 8x8 S-box 적용
    byte temp1, temp2;

    for (int i = 0; i < 16; i++) {
        temp1 = GF_inv(in[i]);
        temp2 = AES_Affine(temp1);
        out[i] = temp2;
    }
}

void AES_ShiftRows(byte in[16], byte out[16]) {  // 바이트의 위치 변환
    out[0] = in[0]; out[4] = in[4]; out[8] = in[8]; out[12] = in[12];  // 4의 배수는 그대로
    out[1] = in[5]; out[5] = in[9]; out[9] = in[13]; out[13] = in[1];  // 나머지가 1이면 << 1
    out[2] = in[10]; out[6] = in[14]; out[10] = in[2]; out[14] = in[6];  // 나머지가 2이면 << 2
    out[3] = in[15]; out[7] = in[3]; out[11] = in[7]; out[15] = in[11];  // 나머지가 3이면 << 3  => 코드 짜보기
}

void AES_MixCol(byte x[4], byte y[4]) {
    byte MixCol[4][4] = { {0x02, 0x03, 0x01, 0x01}, {0x01, 0x02, 0x03, 0x01},
                            {0x01, 0x01, 0x02, 0x03}, {0x03, 0x01, 0x01, 0x02} };
    GF_Matrix MC;

    MC.row = 4;
    MC.col = 4;

    for (int i = 0; i < 4; i++) 
        for (int j = 0; j < 4; j++) 
            MC.M[i][j] = MixCol[i][j];

    GF_Matrix X, Y;
    X.col = 1; Y.col = 1;
    X.row = 4; Y.row = 4;

    for (int i = 0; i < 4; i++)
        X.M[i][0] = x[i];
    Y = GF_Mat_Mul(MC, X);
    for (int i = 0; i < 4; i++)
        y[i] = Y.M[i][0];
}

void AES_MixColumns(byte in[16], byte out[16]) {  // 유한체 GF(2^8)상의 32비트 선형 변환(열 변환)
    byte x[4], y[4];

    for (int col = 0; col < 4; col++) {
        for (int i = 0; i < 4; i++) {
            x[i] = in[col * 4 + i];
        }
        AES_MixCol(x, y);
        for (int i = 0; i < 4; i++) {
            out[col * 4 + i] = y[i];
        }
    }
}

void AES_Round_Function(byte round_in[16], byte rkey[16], byte round_out[16]) {
    byte state1[16], state2[16];

    AES_SubByte(round_in, state1);
    AES_ShiftRows(state1, state2);
    AES_MixColumns(state2, state1);
    AES_AddRoundKey(state1, rkey, round_out); 
}

void AES_Encrypt(byte pt[16], byte rk[11][16], byte ct[16]) {
    byte state1[16], state2[16];

    AES_AddRoundKey(pt, rk[0], state1);

    for (int i = 1; i < 10; i++) {  // 1R~9R
        AES_Round_Function(state1, rk[i], state2);
        for (int j = 0; j < 16; j++) {
            state1[j] = state2[j];
        }
    }
    // 10R
    AES_SubByte(state1, state2);
    AES_ShiftRows(state2, state1);
    AES_AddRoundKey(state1, rk[10], ct);
}

void Run_AES_round_test() {
    byte pt[16] = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
                    0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff };
    byte rk[11][16] = { {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                         0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f},
                        {0xd6, 0xaa, 0x74, 0xfd, 0xd2, 0xaf, 0x72, 0xfa,
                         0xda, 0xa6, 0x78, 0xf1, 0xd6, 0xab, 0x76, 0xfe},
                        {0xb6, 0x92, 0xcf, 0x0b, 0x64, 0x3d, 0xbd, 0xf1,
                         0xbe, 0x9b, 0xc5, 0x00, 0x68, 0x30, 0xb3, 0xfe},
                        {0xb6, 0xff, 0x74, 0x4e, 0xd2, 0xc2, 0xc9, 0xbf,
                         0x6c, 0x59, 0x0c, 0xbf, 0x04, 0x69, 0xbf, 0x41},
                        {0x47, 0xf7, 0xf7, 0xbc, 0x95, 0x35, 0x3e, 0x03,
                         0xf9, 0x6c, 0x32, 0xbc, 0xfd, 0x05, 0x8d, 0xfd},
                        {0x3c, 0xaa, 0xa3, 0xe8, 0xa9, 0x9f, 0x9d, 0xeb,
                         0x50, 0xf3, 0xaf, 0x57, 0xad, 0xf6, 0x22, 0xaa},
                        {0x5e, 0x39, 0x0f, 0x7d, 0xf7, 0xa6, 0x92, 0x96,
                         0xa7, 0x55, 0x3d, 0xc1, 0x0a, 0xa3, 0x1f, 0x6b},
                        {0x14, 0xf9, 0x70, 0x1a, 0xe3, 0x5f, 0xe2, 0x8c,
                         0x44, 0x0a, 0xdf, 0x4d, 0x4e, 0xa9, 0xc0, 0x26},
                        {0x47, 0x43, 0x87, 0x35, 0xa4, 0x1c, 0x65, 0xb9,
                         0xe0, 0x16, 0xba, 0xf4, 0xae, 0xbf, 0x7a, 0xd2},
                        {0x54, 0x99, 0x32, 0xd1, 0xf0, 0x85, 0x57, 0x68,
                         0x10, 0x93, 0xed, 0x9c, 0xbe, 0x2c, 0x97, 0x4e},
                        {0x13, 0x11, 0x1d, 0x7f, 0xe3, 0x94, 0x4a, 0x17,
                         0xf3, 0x07, 0xa7 ,0x8b, 0x4d, 0x2b, 0x30, 0xc5} };

    byte ct[16];

    AES_Encrypt(pt, rk, ct);
    AES_print_state(ct, "ct");

}
//====== AES 암호화 라운드 함수 (끝)

int main()
{
    Run_AES_round_test();
}