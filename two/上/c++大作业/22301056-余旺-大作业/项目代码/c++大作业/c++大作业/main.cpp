#include<iostream>
#include<vector>
#include<string>
#include "chess.h"
#include"player.h"
#include <fstream>

using namespace std;
void showmenu() {
	cout << "����һ���Դ���С�Ľ��׾�������Ϸ" << endl;
	cout << "����������Ϸ����" << endl;
	//cout << "��֮�����Ϸ���������������������x���Ի�ȡ��Ϸ����" << endl;
	cout << "����;�������ͬ�����Ƚ��������������Ľ�������յ�ʤ��" << endl;
	cout << "��Ϸһ���д���С�������ӣ�ÿ�����Ӹ������ţ��ϴ����͵����ӿ��ԳԵ���С������" << endl;
	cout << "Ҫ����������ֿո����ֵ���ʽ������Ϊ����Ĳ���" << endl;
	cout << "��һ�����ִ��������Ҫ��������������������������ʾ�������Ӧ��ſ�������" << endl;
	cout << "�ڶ�������Ҫ����ѡ�������������ͣ�����С�������ͣ�,0����С�ӣ�1�������ӣ�2�������" << endl;
	cout << "�����ϵ�չʾ��������+����+������ʽ����һ�����ִ�����ң�1�������1��2�������2���ڶ����ִ����������ͣ�0����С�ӣ�1�������ӣ�2�������" << endl;
	cout << "1  |  2  |  3 " << endl;
	cout << "4  |  5  |  6 " << endl;
	cout << "7  |  8  |  9" << endl;
	cout << "��Ϸ��ʼ��ף������" << endl;
}

int Battle(chess *chess) {
	int flag = 0;
	player* player1 = new player;
	player* player2 = new player;
	while (flag == 0) {
		player1->Display(&chess->onechess, player1->chessplay, player2->chessplay);
		player1->playchess(1,&chess->onechess,(player1->chessplay));
		flag=chess->whetherwin();
		if (flag != 0) {
			break;
		}
		player2->Display(&chess->onechess, player1->chessplay, player2->chessplay);
		player2->playchess(2, &chess->onechess, (player2->chessplay));
		flag=chess->whetherwin();
		if (flag != 0) {
			break;
		}
		//����λѡ�ֵ�����ȫ��������Ȼû�о���ʤ���ʹ���ƽ��
		if (player1->chessplay[0] == 0 && player1->chessplay[1] == 0 && player1->chessplay[2] == 0) {
			break;
		}

	}
	delete player1;
	delete player2;
	return flag;
}
void WinMess(const int result) {
	ofstream file("data.txt", ios::app); // ��׷����ʽ���ļ�  
	string temp;
	if (result == 1) {
		temp = "ѡ��1 win,ѡ��2 lose";
		cout << temp << endl;
	}
	else if (result == 0) {
		temp ="ƽ��" ;
		cout << temp << endl;
	}
	else {
		temp= "ѡ��2 win,ѡ��1 lose";
		cout << temp<< endl;
	}

	if (file.is_open()) {
		file << temp<<endl; // д������  
		file.close(); // �ر��ļ�  
		cout << "�����ѳɹ�׷��д���ļ���" << endl;
	}
	else {
		cout << "�޷����ļ�����д�롣" << endl;
	}

	
}
int main(int argc, char* argv[]) {
	//չʾ����
	showmenu();
	
	while (1) {
		chess* chess1 = new chess();
		char goon = 'N';
		int result = Battle(chess1);
		WinMess(result);
		cout << "�㻹����һ����������ľ����������������Y/N" << endl;
		cin >> goon;
		if (goon != 'Y') {
			cout << "��л������������´�����Ŷ" << endl;
			delete chess1;
			break;

		}
		else {
			delete chess1;
			cout << "��Ϸ�����ã�" << endl;
		}

	}



}