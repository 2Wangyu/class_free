#include<iostream>
#include<fstream>
using namespace std;



void ReadFromFile(string name, int* num) {//从文件读取数据
	int i, datalen = 0;
	ifstream file(name);
	while (!file.eof())file >> num[datalen++];//将读取的数据存到数组中
	file.close();
}
int main() {












}