// Week5-Class.cpp : 
//

#include <iostream>
#define MAX_SIZE 10

/*
struct stVector {  // 구조체 - 사용자가 정의한 데이터 타입
    int size;
    double v[MAX_SIZE];
};
*/

// C++ OOP (Object Oriented Programming): Encapsulation, Polymorphism, Inheritance
// Encapsulation: Data (Set) + Operations (structure, relation...)

class CVector {  // 클래스 벡터
private:
    // 멤버 변수들 (Data)
    int mSize;
    double mVec[MAX_SIZE];
public:   // 3가지 선택: private(기본), public, protected
    // 생성자(constructor) : 변수가 생성될 때 호출되는 함수
    // 오버로딩(over loading) <= CVector() / CVector(int size)
    CVector() { mSize = 1; };
    CVector(int size) { mSize = size; };  // 함수의 본문까지 class 정의에 쓰는 경우 -> inline 함수로
    CVector(int size, double arr[]); 
    void SetValue(int nPos, double value);
    double GetValue(int nPos);
    // 멤버 함수들 (function, operation)
    void Print();
    void SetSize(int size) { mSize = size; };
    int Size() { return mSize; };

    void ScalarMul(double value);
    CVector Add(CVector cv);  // (현재) v3 = v1.Add(v2); => (개선) v3 = v1 + v2; (가능! 연산자 재정의)
};

CVector::CVector(int size, double arr[]) {
    mSize = size;
    for (int i = 0; i < size; i++) {
        mVec[i] = arr[i];
    }
}

void CVector::ScalarMul(double value) {
    for (int i = 0; i < mSize; i++) {
        mVec[i] *= value;
    }
}

CVector CVector::Add(CVector cv) {
    CVector result;

    if (cv.Size() != mSize) {
        printf("Vector size mismatch!\n");
        return result;  // 의미없는 결과
    }
    result.SetSize(mSize);
    for (int i = 0; i < mSize; i++) {
        result.SetValue(i, mVec[i] + cv.GetValue(i));
        // result.mVec[i] = mVec[i] + cv.mVec[i];
    }

    return result;
}

void CVector::SetValue(int nPos, double value) {
    if (nPos >= mSize) {
        printf("Range error!\n");
        return;
    }
    mVec[nPos] = value;
}

double CVector::GetValue(int nPos) {
    if (nPos >= mSize) {
        printf("Range error!\n");
        return -1.0;
    }
    return mVec[nPos];
}

void CVector::Print() {  // (리턴타입)(클래스명)::(멤버함수이름)(....) {}
    printf("[");
    for (int i = 0; i < mSize; i++) {
        printf("%7.3f", mVec[i]);
    }
    printf("]\n");
}

/*
void CVector_Print(CVector vec) {
    printf("[");
    for (int i = 0; i < vec.size; i++) {
        printf("%7.3f", vec.v[i]);
    }
    printf("]\n");
}
*/

void class_test() {
    CVector my_vector(3);
    // cVector : 클래스명 (int, double)
    // my_vector : 변수 (인스턴스, 객체 object)

    printf("Start class_test()...\n");

    //my_vector.mSize = 3;
    my_vector.SetValue(0, 1.0);
    my_vector.SetValue(1, 2.0);
    my_vector.SetValue(2, 3.0);
    //my_vector.SetValue(3, 4.0);

    //CVector_Print(my_vector);
    my_vector.Print();

    printf("Start class_test() : 2nd test...\n");

    CVector vec2;  // 기본 생성자
    vec2.SetSize(5);

    double a[5] = { 0.1, 0.2, 0.3, 0.4, 0.5 };
    CVector vec3(5, a);
    vec3.Print();

    vec3.ScalarMul(10);
    vec3.Print();
    CVector vec4(5, a);
    CVector vec5;

    vec5 = vec3.Add(vec4);
    vec5.Print();
}

int main()
{
    class_test();
}
