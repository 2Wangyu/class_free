#include"player.h"
#include<iostream>
#include <iomanip>
#include <string>
using namespace std;


player::player(){
	
}
void player::Display( vector<string>* chess, const int* arr1, const int* arr2) {
	cout << "����Ŀǰս����" << endl;

	/*cout << chess[0].substr(0, 4) << endl;
	cout.write(chess[0].c_str(),4) << endl;*/
	cout << (*chess)[0] << " |" << (*chess)[1] << " |" << (*chess)[2] << endl;
	cout << "������������������������������" << "  ѡ��1��ʣ��������������С��: " << arr1[0] << " ����: " << arr1[1] << " ���ӣ�" << arr1[2] << endl;
	cout << (*chess)[3] << " |" << (*chess)[4] << " |" << (*chess)[5] << endl;
	cout << "������������������������������" << "  ѡ��2��ʣ��������������С��: " << arr2[0] << " ����: " << arr2[1] << " ���ӣ�" << arr2[2] << endl;
	cout << (*chess)[6] << " |" << (*chess)[7] << " |" << (*chess)[8] << endl;
}
void player::playchess(int playnum,vector<string>* chess,int *arr) {
	int num, chara;
	cout << "ѡ��"<<to_string(playnum)<<":����������������������ͣ�ʾ��Ϊ 1 1�����ֿո����֣�" << endl;
	cin >> num >> chara;
	while (1) {

		if (arr[chara] == 0||chara>2) {
			cout << "��û�и����͵������ˣ�����������" << endl;
			cin >> num >> chara;
			continue;
		}
		if (num<= 0 || num > 9) {
			cout << "����ָ����������������" << endl;
			cin >> num >> chara;
			continue;
		}
		else {
			if ((*chess)[num - 1] == "   ") {
				string temp = to_string(playnum)+"," + to_string(chara);
				(*chess)[num - 1] = temp;
				arr[chara]--;
				break;
			}
			else {
				int chesschara = (*chess)[num - 1][2]-'0';
				if (chara > chesschara) {
					string temp = to_string(playnum)+"," + to_string(chara);
					(*chess)[num - 1] = temp;
					arr[chara]--;
					break;
				}
				else {
					cout << "���Բ�����ǰλ�õ����ӣ�����������" << endl;
					cin >> num >> chara;
				}
			}


		}
	}





}