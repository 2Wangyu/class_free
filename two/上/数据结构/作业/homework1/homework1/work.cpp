#include<iostream>
#include<string>
using namespace std;

class BadDemo {
public:
	// δ������Ϊ��i_��j_֮ǰ����ʼ��
	BadDemo(int val) : j_(val), i_(j_) {}

public:
	int i_;
	int j_;
};


int main() {
	
	BadDemo p1(1);
	cout << p1.i_ <<endl ;
	cout << p1.j_ << endl;


}