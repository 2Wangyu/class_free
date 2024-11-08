#include<iostream>
using namespace std;

void calcuBMI(){

	double height, weight;
	cout << "请输入你的身高(m)" << endl;
	cin >> height;
	while (height <= 0 || height > 3) {
		cout << "请输入正确的身高" << endl;
		cin >> height;
	}
	cout << "请输入你的体重(kg)" << endl;
	cin >> weight;
	while (weight <= 0 ) {
		cout << "请输入正确的体重" << endl;
		cin >> weight;
	}
	cout << "你的BMI为"<<weight/pow(height,2) << endl;




}


int main() {


	calcuBMI();







}