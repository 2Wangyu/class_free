#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include <iomanip>
#include "chess.h"
#include"chess"
using namespace std;

static vector<string> chess(9, "   ");
static int chessplay1[3] = { 3 ,3,3};
static int chessplay2[3] = { 3 ,3,3};

void showmenu() {
	cout << "����һ���Դ���С�Ľ��׾�������Ϸ" << endl;
	cout << "����������Ϸ����" << endl;
	//cout << "��֮�����Ϸ���������������������x���Ի�ȡ��Ϸ����" << endl;
	cout << "����;�������ͬ�����Ƚ��������������Ľ�������յ�ʤ��" << endl;
	cout << "��Ϸһ���д���С�������ӣ�ÿ�����Ӹ������ţ��ϴ����͵����ӿ��ԳԵ���С������" << endl;
	cout << "�����������������ʾ�������Ӧ��ſ�������" << endl;
	cout << "���Ż�Ҫ����ѡ�������������ͣ�����С�������ͣ�,0����С�ӣ�1�������ӣ�2�������" <<endl ;
	cout << "�����ϵ�չʾ��������+����+������ʽ����һ�����ִ�����ң�1�������1��2�������2���ڶ����ִ����������ͣ�0����С�ӣ�1�������ӣ�2�������" << endl;
	cout << "1  |  2  |  3 " << endl;
	cout << "4  |  5  |  6 " << endl;
	cout << "7  |  8  |  9" << endl;
	cout << "��Ϸ��ʼ��ף������" << endl;
}
//չʾ��ǰ���� 
void Display(vector<string>& chess) {
	cout << "����Ŀǰս����" << endl;

	/*cout << chess[0].substr(0, 4) << endl;
	cout.write(chess[0].c_str(),4) << endl;*/
	cout << chess[0] << std::setw(4) << " |" << chess[1] << std::setw(4) << " |" << chess[2] << endl;
	cout << "����������������������������������������" <<"  ѡ��1��ʣ��������������С��:"<<chessplay1[0]<<"����" << chessplay1[1] << "���ӣ�" << chessplay1[2] << endl;
	cout << chess[3] << std::setw(4)<< "  |" << chess[4] << std::setw(4) << " |" << chess[5] <<endl;
	cout << "����������������������������������������" <<"  ѡ��2��ʣ��������������С��:" << chessplay2[0] << "����" << chessplay2[1] << "���ӣ�" << chessplay2[2] << endl;
	cout << chess[6] << std::setw(4) << " |" << chess[7] << std::setw(4) << " |" << chess[8] << endl;
}

void palyerone() {
	int num,chara;
	Display(chess);
	cout << "ѡ��1����������������������ͣ�ʾ��Ϊ 1 1�����ֿո����֣�" << endl;
	cin >> num >> chara;
	while (1) {
		
		if (chessplay1[chara] == 0) {
			cout << "��û�и����͵������ˣ�����������" << endl;
			cin >> num >> chara;
			continue;
		}
		else {
			if (chess[num-1] == "   ") {
				string temp = "1," + to_string(chara);
				chess[num-1] = temp;
				chessplay1[chara]--;
				break;
			}
			else {
				//��ȡ���ӵ���Ϣ
				string temp = chess[num-1];
				stringstream ss(temp);
				string item;
				vector<int> ints;
				while (getline(ss, item, ',')) {
					ints.push_back(stoi(item));
				}
				//int playernum = ints[0];
				int chesschara = ints[1];
				if (chara > chesschara) {
					string temp = "1," + to_string(chara);
					chess[num-1] = temp;
					chessplay1[chara]--;
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
void playertwo() {
	int num, chara;
	Display(chess);
	cout << "ѡ��2����������������������ͣ�ʾ��Ϊ 1 1�����ֿո����֣�" << endl;
	cin >> num >> chara;
	while (1) {

		if (chessplay2[chara] == 0) {
			cout << "��û�и����͵������ˣ�����������" << endl;
			cin >> num >> chara;
			continue;
		}
		else {
			if (chess[num-1] == "   ") {
				string temp = "2," + to_string(chara);
				chess[num-1] = temp;
				chessplay2[chara]--;
				break;
			}
			else {
				//��ȡ���ӵ���Ϣ
				string temp = chess[num-1];
				stringstream ss(temp);
				string item;
				vector<int> ints;
				while (getline(ss, item, ',')) {
					ints.push_back(stoi(item));
				}
				//int playernum = ints[0];
				int chesschara = ints[1];
				if (chara > chesschara) {
					string temp = "2," + to_string(chara);
					chess[num-1] = temp;
					chessplay2[chara]--;
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
int whetherwin() 
{
	if (chess[0]!= "   " &&chess[0][0] == chess[1][0] && chess[1][0] == chess[2][0]) {
		//cout<<(chess[0])[0]<<endl;
		return static_cast<int>((chess[0])[0]);
	}
	else if(chess[3] != "   " && chess[3][0] == chess[4][0] && chess[4][0] == chess[5][0]) {
		return static_cast<int>((chess[3])[0]);
	
	}
	else if (chess[6] !="   " && chess[6][0] == chess[7][0] && chess[7][0] == chess[8][0]) {
		return static_cast<int>((chess[6])[0]);
	}
	else if (chess[0] != "   " && chess[0][0] == chess[3][0] && chess[3][0] == chess[6][0]) {
		return static_cast<int>((chess[0])[0]);
	}
	else if (chess[1] != "   " && chess[1][0] == chess[4][0] && chess[4][0] == chess[7][0]) {
		return static_cast<int>((chess[1])[0]);
	}
	else if (chess[2] !="   " && chess[2][0] == chess[5][0] && chess[5][0] == chess[8][0]) {
		return static_cast<int>((chess[2])[0]);
	}
	else if (chess[0] != "   " && chess[0][0] == chess[4][0] && chess[4][0] == chess[8][0]) {
		return static_cast<int>((chess[0])[0]);
	}
	else if (chess[2] != "   " && chess[2][0] == chess[4][0] && chess[6][0] == chess[4][0]) {
		return static_cast<int>((chess[2])[0]);
	}
	else{
		return 0;
	}
}
int Battle() {
	int flag = 0;
	while (flag==0) {
		palyerone();
		flag=whetherwin();
		if (flag != 0) {
			break;
		}
		playertwo();
		flag=whetherwin();
		if (flag != 0) {
			break;
		}
		//����λѡ�ֵ�����ȫ��������Ȼû�о���ʤ���ʹ���ƽ��
		if (chessplay1[0] == 0 && chessplay1[1] == 0 && chessplay1[2] == 0) {
			break;
		}
	
	}
	return flag;
}
void WinMess(const int result) {
	if (result == 1) {
		cout << "ѡ��1 win,ѡ��2 lose" << endl;
	}
	else if (result == 0) {
		cout << "ƽ��" << endl;
	}
	else {
		cout << "ѡ��2 win,ѡ��1 lose" << endl;
	}

}
int main(int argc, char* argv[]) {
	//չʾ����
	showmenu();
	chess *playchess = new chess();
	while (1) {
		char goon='N';
		int result=Battle();
		WinMess(result);
		cout << "�㻹����һ����������ľ����������������Y/N" <<endl ;
		cin >> goon;
		if(goon!='Y') {
			cout << "��л������������´�����Ŷ" << endl;
			break;
		}
		else {
			//��������
			for (int i = 0; i < 9; i++) {
				chess[i] = "   ";
			}
			//������������
			for (int i = 0; i < 3; i++) {
				chessplay1[i] = 3;
				chessplay2[i] = 3;
			}
			cout << "��Ϸ�����ã�" << endl;
		}
		
	}



}