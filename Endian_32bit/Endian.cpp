// Endian 연습

#include <iostream>

typedef unsigned char byte;
typedef unsigned int u32;
typedef unsigned char u8;

#define GETU32(b)  ((u32)(b)[0] << 24) ^ ((u32)(b)[1] << 16) ^ ((u32)(b)[2] << 8) ^ ((u32)(b)[3])
#define PUTU32(b, x) { \
(b)[0] = (byte)((x) >> 24); \
(b)[1] = (byte)((x) >> 16); \
(b)[2] = (byte)((x) >> 8); \
(b)[3] = (byte)(x); }

void Endian_test1() {
    byte b[4] = { 0xf1, 0xf2, 0xf3, 0xf4 };
    u32* pint;
    int x;

    pint = (u32*)b;
    x = *pint;

    printf("b = %02x, %02x, %02x, %02x\n", b[0], b[1], b[2], b[3]);
    printf("x = %08x\n", x);

    u32 y;
    y = ((u32)b[0] << 24) ^ ((u32)b[1] << 16) ^ ((u32)b[2] << 8) ^ ((u32)b[3]);
    // y= f1000000 ^ 00f20000 ^ 0000f300 ^ 000000f4 = f1f2f3f4
    printf("y = %08x\n", y);

    u32 z;
    z = GETU32(b);
    printf("z = %08x\n", z);

    byte c[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
    u32 w;
    w = GETU32(c + 4);
    printf("w = %08x\n", w);
}

void Endian_test2() {
    u32 x = 0xf1f2f3f4;  // --> {f1, f2, f3, f4}
    byte b[4];

    b[0] = (byte)(x >> 24);
    b[1] = (byte)(x >> 16);
    b[2] = (byte)(x >> 8);
    b[3] = (byte)x;

    printf("x = %08x\n", x);
    printf("b = %02x, %02x, %02x, %02x\n", b[0], b[1], b[2], b[3]);

    byte c[4];
    PUTU32(c, x);
    printf("c = %02x, %02x, %02x, %02x\n", c[0], c[1], c[2], c[3]);

    byte d[16] = { 0, };
    PUTU32(d + 12, x);
    printf("d = ");
    for (int i = 0; i < 16; i++) printf("%02x, ", d[i]);
}

int main() {
    Endian_test2();
}
