#include<iostream>
#include<fstream>
using namespace std;



void ReadFromFile(string name, int* num) {//���ļ���ȡ����
	int i, datalen = 0;
	ifstream file(name);
	while (!file.eof())file >> num[datalen++];//����ȡ�����ݴ浽������
	file.close();
}
int main() {












}