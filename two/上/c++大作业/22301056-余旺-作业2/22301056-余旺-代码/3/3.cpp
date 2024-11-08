#include <iostream>
#include <cstring>
#include<cstring>
#define _CRT_SECURE_NO_WARNINGS

using namespace std;


class SimpleString {
private:
    //ָ��ͳ���
    char* ptr_ = nullptr;
    size_t len_ = 0;

public:
    // ���캯��
    SimpleString(const char* str) {
        if (str != nullptr) {
            len_ = strlen(str);
            ptr_ = new char[len_ ]; // 
            memcpy(ptr_, str, len_); // ʹ�� memcpy �����ַ�������
        }
    }

    // �������캯��
    SimpleString(const SimpleString& other) {
        if (other.ptr_ != nullptr) {
        len_ = other.len_;
        ptr_ = new char[len_ ];
        memcpy(ptr_, other.ptr_,len_);
    }
}

    // ��������
    ~SimpleString() {
        delete[] ptr_;
    }

    // ������������
    friend ostream& operator<<(ostream& os, const SimpleString& str) {
        //os << str.ptr_;
        os.write(str.ptr_, str.len_);
        return os;
    }

    // ���ط�������� []
    char operator[](size_t index) const {
        if (index < len_) {
            return ptr_[index];
        }
        else {
          
            cout << "visit wrong!" << endl;
            return '\0';
        }
    }

    // �����޸������ []
    char& operator[](size_t index) {
        if (index < len_) {
            return ptr_[index];
        }
        else {
            static char nullChar = '\0';
            cout << "visit wrong!" << endl;
            return nullChar;
        }
    }
};

int main() {
    // ���� SimpleString �������
    SimpleString myString("Ilovecoding!");
    // ʹ�� [] ���ʺ��޸��ַ�
    cout << "�ַ����ĵڰ˸��ַ���: " << myString[7] << endl;
    cout << "�޸�ǰ���ַ��� " << myString << endl;
    myString[7] = 'X';
    cout << "�޸ĺ���ַ��� " << myString << endl;

    return 0;
}



