#include<iostream>
#include<vector>
#include<string>
#include "chess.h"
#include"player.h"
#include <fstream>

using namespace std;
void showmenu() {
	cout << "这是一个以大欺小的进阶井字棋游戏" << endl;
	cout << "下面会进行游戏介绍" << endl;
	//cout << "在之后的游戏中如果不清楚规则可以输入x，以获取游戏规则" << endl;
	cout << "规则和井字棋相同，率先将棋子练成三个的将获得最终的胜利" << endl;
	cout << "游戏一共有大中小三类棋子，每类棋子各有三颗，较大类型的棋子可以吃掉较小的棋子" << endl;
	cout << "要求玩家以数字空格数字的形式输入作为下棋的步骤" << endl;
	cout << "第一个数字代表玩家所要下棋的区域，如何输入落子如下所示，输入对应序号可以落子" << endl;
	cout << "第二个数字要求您选择落子哪种类型（大中小三种类型）,0代表小子，1代表中子，2代表大字" << endl;
	cout << "棋盘上的展示会以数字+逗号+数字形式，第一个数字代表玩家，1代表玩家1，2代表玩家2，第二数字代表棋子类型，0代表小子，1代表中子，2代表大字" << endl;
	cout << "1  |  2  |  3 " << endl;
	cout << "4  |  5  |  6 " << endl;
	cout << "7  |  8  |  9" << endl;
	cout << "游戏开始，祝君好运" << endl;
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
		//当两位选手的棋子全都用完仍然没有决出胜负就代表平局
		if (player1->chessplay[0] == 0 && player1->chessplay[1] == 0 && player1->chessplay[2] == 0) {
			break;
		}

	}
	delete player1;
	delete player2;
	return flag;
}
void WinMess(const int result) {
	ofstream file("data.txt", ios::app); // 以追加形式打开文件  
	string temp;
	if (result == 1) {
		temp = "选手1 win,选手2 lose";
		cout << temp << endl;
	}
	else if (result == 0) {
		temp ="平局" ;
		cout << temp << endl;
	}
	else {
		temp= "选手2 win,选手1 lose";
		cout << temp<< endl;
	}

	if (file.is_open()) {
		file << temp<<endl; // 写入数据  
		file.close(); // 关闭文件  
		cout << "数据已成功追加写入文件。" << endl;
	}
	else {
		cout << "无法打开文件进行写入。" << endl;
	}

	
}
int main(int argc, char* argv[]) {
	//展示规则
	showmenu();
	
	while (1) {
		chess* chess1 = new chess();
		char goon = 'N';
		int result = Battle(chess1);
		WinMess(result);
		cout << "你还想来一场酣畅淋漓的井字棋比赛吗？请输入Y/N" << endl;
		cin >> goon;
		if (goon != 'Y') {
			cout << "感谢您参与比赛，下次再来哦" << endl;
			delete chess1;
			break;

		}
		else {
			delete chess1;
			cout << "游戏已重置！" << endl;
		}

	}



}