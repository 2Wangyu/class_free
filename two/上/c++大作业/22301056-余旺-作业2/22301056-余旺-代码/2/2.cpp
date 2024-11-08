#include <iostream>
#include <cmath>
using namespace std;

class Complex {
private:
    //ʵ������
    double real;
    //��������
    double imag;

public:
    Complex(double real, double imag) : real(real), imag(imag) {}

    // ��������
    //
    // +
    Complex operator+(const Complex& other) const {
        //Complex now= Complex(real + other.real, imag + other.imag);

        //�ӷ�
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
        //����ʵ����
        double temp = other.real * other.real + other.imag * other.imag;
        
        return Complex((real * other.real + imag * other.imag) / temp,
            ( - real * other.imag+ imag * other.real) / temp);

    }

    // +=, -=, *=, /= �汾
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

    // �ж���ȺͲ���
    bool operator==(const Complex& other) const {
        return (real == other.real) && (imag == other.imag);
    }

    bool operator!=(const Complex& other) const {
        return !(*this == other);
    }

    // ���㸴����ģ
    double magnitude() const {
        return sqrt(real * real + imag * imag);
    }

    // �������
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
    cout << "���㸴����" << complexArray[0] << ",��" << complexArray[1] << "Ϊ" << complexArray[0] + complexArray[1] << endl;
    cout << "���㸴����" << complexArray[0] << ",��" << complexArray[1] << "Ϊ" << complexArray[0] - complexArray[1] << endl;
    cout << "���㸴����" << complexArray[0] << ",��" << complexArray[1] << "Ϊ" << complexArray[0] * complexArray[1] << endl;
    cout << "���㸴����" << complexArray[0] << ",��" << complexArray[1] << "Ϊ" << complexArray[0] / complexArray[1] << endl;
    cout << "���㸴����" << complexArray[0] << ",+=����" << complexArray[1] << "Ϊ" <<( complexArray[0] += complexArray[1]) << endl;
    cout << "���㸴����" << complexArray[0] << ",-=����" << complexArray[1] << "Ϊ" << (complexArray[0] -= complexArray[1]) << endl;
    cout << "���㸴����" << complexArray[0] << ",*=����" << complexArray[1] << "Ϊ" << (complexArray[0] *= complexArray[1])<< endl;
    cout << "���㸴����" << complexArray[0] << ",/=����" << complexArray[1] << "Ϊ" << (complexArray[0] /= complexArray[1])<< endl;

    cout << "�ж����" << complexArray[0] << "��" << complexArray[1] << ((complexArray[0] == complexArray[1]) ? "���" : "�����") << endl;
    cout << "�жϲ����" << complexArray[1] << "��" << complexArray[2] << ((complexArray[1] != complexArray[2]) ? "�����" : "���") << endl;

    int arraySize = sizeof(complexArray) / sizeof(complexArray[0]);

    // ����ģ��С�ĸ���
    Complex minComplex = complexArray[0];
    for (int i = 1; i < arraySize; ++i) {
        if (complexArray[i].magnitude() < minComplex.magnitude()) {
            minComplex = complexArray[i];
        }
    }

    // ����ģ���ĸ���
    Complex maxComplex = complexArray[0];
    for (int i = 1; i < arraySize; ++i) {
        if (complexArray[i].magnitude() > maxComplex.magnitude()) {
            maxComplex = complexArray[i];
        }
    }

    // ���ģ��С��ģ���ĸ���
    cout << "Minimum  Complex: " << minComplex << "�� ta��ģ��" << minComplex.magnitude() << endl;
    cout << "Maximum  Complex: " << maxComplex << "�� ta��ģ��" << maxComplex.magnitude() << endl;

    // ���ģ��С��3�ĸ���
    std::cout << "Complex Numbers with Magnitude not less than 3:" << std::endl;
    for (int i = 0; i < arraySize; ++i) {
        if (complexArray[i].magnitude() >= 3) {
            cout << complexArray[i] << "�� ta��ģ��" << complexArray[i].magnitude() << endl;
        }
    }

    return 0;
}
