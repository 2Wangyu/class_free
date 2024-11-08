#include <iostream>
#include <cmath>
using namespace std;

class Complex {
private:
    //实数部分
    double real;
    //虚数部分
    double imag;

public:
    Complex(double real, double imag) : real(real), imag(imag) {}

    // 四则运算
    //
    // +
    Complex operator+(const Complex& other) const {
        //Complex now= Complex(real + other.real, imag + other.imag);

        //加法
        return Complex(real + other.real, imag + other.imag);
    }


    //-
    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }


    //*
    Complex operator*(const Complex& other) const {

        return Complex(real * other.real - imag * other.imag, real * other.imag + imag * other.real);
    }


    //\

    Complex operator/(const Complex& other) const {
        //分子实数化
        double temp = other.real * other.real + other.imag * other.imag;
        
        return Complex((real * other.real + imag * other.imag) / temp,
            ( - real * other.imag+ imag * other.real) / temp);

    }

    // +=, -=, *=, /= 版本
    Complex& operator+=(const Complex& other) {
        real += other.real;
        imag += other.imag;

        return *this;
    }

    Complex& operator-=(const Complex& other) {
        real -= other.real;
        imag -= other.imag;
        return *this;
    }

    Complex& operator*=(const Complex& other) {
        double tempReal = real * other.real - imag * other.imag;
        double tempimag = real * other.imag + imag * other.real;
        imag = tempimag;
        real = tempReal;
        return *this;
    }

    Complex& operator/=(const Complex& other) {
        double temp = other.real * other.real + other.imag * other.imag;
        double tempReal = (real * other.real + imag * other.imag) / temp;
        double tempimag = (imag * other.real - real * other.imag) / temp;
        imag = tempimag;
        real = tempReal;
        return *this;
    }

    // 判断相等和不等
    bool operator==(const Complex& other) const {
        return (real == other.real) && (imag == other.imag);
    }

    bool operator!=(const Complex& other) const {
        return !(*this == other);
    }

    // 计算复数的模
    double magnitude() const {
        return sqrt(real * real + imag * imag);
    }

    // 输出复数
    friend ostream& operator<<(ostream& os, const Complex& complex) {
        os << complex.real << "+" << complex.imag << "i";
        return os;
    }
};

int main() {
    Complex complexArray[5] = {
        {1, 2},
        {3, -4},
        {-5, 6},
        {12, 5},
        {2, -3}
    };
    cout << "计算复数：" << complexArray[0] << ",加" << complexArray[1] << "为" << complexArray[0] + complexArray[1] << endl;
    cout << "计算复数：" << complexArray[0] << ",减" << complexArray[1] << "为" << complexArray[0] - complexArray[1] << endl;
    cout << "计算复数：" << complexArray[0] << ",乘" << complexArray[1] << "为" << complexArray[0] * complexArray[1] << endl;
    cout << "计算复数：" << complexArray[0] << ",除" << complexArray[1] << "为" << complexArray[0] / complexArray[1] << endl;
    cout << "计算复数：" << complexArray[0] << ",+=运算" << complexArray[1] << "为" <<( complexArray[0] += complexArray[1]) << endl;
    cout << "计算复数：" << complexArray[0] << ",-=运算" << complexArray[1] << "为" << (complexArray[0] -= complexArray[1]) << endl;
    cout << "计算复数：" << complexArray[0] << ",*=运算" << complexArray[1] << "为" << (complexArray[0] *= complexArray[1])<< endl;
    cout << "计算复数：" << complexArray[0] << ",/=运算" << complexArray[1] << "为" << (complexArray[0] /= complexArray[1])<< endl;

    cout << "判断相等" << complexArray[0] << "和" << complexArray[1] << ((complexArray[0] == complexArray[1]) ? "相等" : "不相等") << endl;
    cout << "判断不相等" << complexArray[1] << "和" << complexArray[2] << ((complexArray[1] != complexArray[2]) ? "不相等" : "相等") << endl;

    int arraySize = sizeof(complexArray) / sizeof(complexArray[0]);

    // 计算模最小的复数
    Complex minComplex = complexArray[0];
    for (int i = 1; i < arraySize; ++i) {
        if (complexArray[i].magnitude() < minComplex.magnitude()) {
            minComplex = complexArray[i];
        }
    }

    // 计算模最大的复数
    Complex maxComplex = complexArray[0];
    for (int i = 1; i < arraySize; ++i) {
        if (complexArray[i].magnitude() > maxComplex.magnitude()) {
            maxComplex = complexArray[i];
        }
    }

    // 输出模最小和模最大的复数
    cout << "Minimum  Complex: " << minComplex << "， ta的模是" << minComplex.magnitude() << endl;
    cout << "Maximum  Complex: " << maxComplex << "， ta的模是" << maxComplex.magnitude() << endl;

    // 输出模不小于3的复数
    std::cout << "Complex Numbers with Magnitude not less than 3:" << std::endl;
    for (int i = 0; i < arraySize; ++i) {
        if (complexArray[i].magnitude() >= 3) {
            cout << complexArray[i] << "， ta的模是" << complexArray[i].magnitude() << endl;
        }
    }

    return 0;
}
