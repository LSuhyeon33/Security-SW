// Week5-struct.cpp : 
//

#include <iostream>
#define MAX_SIZE 10

struct stVector {  // 구조체 - 사용자가 정의한 데이터 타입
    int size;
    double v[MAX_SIZE];
};

void stVector_Print(stVector vec) {
    printf("[");
    for (int i = 0; i < vec.size; i++) {
        printf("%7.3f", vec.v[i]);
    }
    printf("]\n");
}

int main()
{
    stVector my_vector;

    my_vector.size = 3;
    my_vector.v[0] = 1.0;
    my_vector.v[1] = 2.0;
    my_vector.v[2] = 3.0;

    stVector_Print(my_vector);
}
