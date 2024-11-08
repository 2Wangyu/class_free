#include <iostream>
#include <cstring>
#include<cstring>
#define _CRT_SECURE_NO_WARNINGS

using namespace std;


class SimpleString {
private:
    //指针和长度
    char* ptr_ = nullptr;
    size_t len_ = 0;

public:
    // 构造函数
    SimpleString(const char* str) {
        if (str != nullptr) {
            len_ = strlen(str);
            ptr_ = new char[len_ ]; // 
            memcpy(ptr_, str, len_); // 使用 memcpy 复制字符串内容
        }
    }

    // 拷贝构造函数
    SimpleString(const SimpleString& other) {
        if (other.ptr_ != nullptr) {
        len_ = other.len_;
        ptr_ = new char[len_ ];
        memcpy(ptr_, other.ptr_,len_);
    }
}

    // 析构函数
    ~SimpleString() {
        delete[] ptr_;
    }

    // 重载输出运算符
    friend ostream& operator<<(ostream& os, const SimpleString& str) {
        //os << str.ptr_;
        os.write(str.ptr_, str.len_);
        return os;
    }

    // 重载访问运算符 []
    char operator[](size_t index) const {
        if (index < len_) {
            return ptr_[index];
        }
        else {
          
            cout << "visit wrong!" << endl;
            return '\0';
        }
    }

    // 重载修改运算符 []
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
    // 创建 SimpleString 对象并输出
    SimpleString myString("Ilovecoding!");
    // 使用 [] 访问和修改字符
    cout << "字符串的第八个字符是: " << myString[7] << endl;
    cout << "修改前的字符串 " << myString << endl;
    myString[7] = 'X';
    cout << "修改后的字符串 " << myString << endl;

    return 0;
}



