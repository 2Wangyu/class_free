#include<iostream>
using namespace std;

void calcuBMI(){

	double height, weight;
	cout << "������������(m)" << endl;
	cin >> height;
	while (height <= 0 || height > 3) {
		cout << "��������ȷ�����" << endl;
		cin >> height;
	}
	cout << "�������������(kg)" << endl;
	cin >> weight;
	while (weight <= 0 ) {
		cout << "��������ȷ������" << endl;
		cin >> weight;
	}
	cout << "���BMIΪ"<<weight/pow(height,2) << endl;




}


int main() {


	calcuBMI();







}