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
	cout << "这是一个以大欺小的进阶井字棋游戏" << endl;
	cout << "下面会进行游戏介绍" << endl;
	//cout << "在之后的游戏中如果不清楚规则可以输入x，以获取游戏规则" << endl;
	cout << "规则和井字棋相同，率先将棋子练成三个的将获得最终的胜利" << endl;
	cout << "游戏一共有大中小三类棋子，每类棋子各有三颗，较大类型的棋子可以吃掉较小的棋子" << endl;
	cout << "如何输入落子如下所示，输入对应序号可以落子" << endl;
	cout << "接着会要求您选择落子哪种类型（大中小三种类型）,0代表小子，1代表中子，2代表大字" <<endl ;
	cout << "棋盘上的展示会以数字+逗号+数字形式，第一个数字代表玩家，1代表玩家1，2代表玩家2，第二数字代表棋子类型，0代表小子，1代表中子，2代表大字" << endl;
	cout << "1  |  2  |  3 " << endl;
	cout << "4  |  5  |  6 " << endl;
	cout << "7  |  8  |  9" << endl;
	cout << "游戏开始，祝君好运" << endl;
}
//展示当前棋盘 
void Display(vector<string>& chess) {
	cout << "棋盘目前战况：" << endl;

	/*cout << chess[0].substr(0, 4) << endl;
	cout.write(chess[0].c_str(),4) << endl;*/
	cout << chess[0] << std::setw(4) << " |" << chess[1] << std::setw(4) << " |" << chess[2] << endl;
	cout << "————————————————————" <<"  选手1（剩余棋子数量）：小子:"<<chessplay1[0]<<"中子" << chessplay1[1] << "大子：" << chessplay1[2] << endl;
	cout << chess[3] << std::setw(4)<< "  |" << chess[4] << std::setw(4) << " |" << chess[5] <<endl;
	cout << "————————————————————" <<"  选手2（剩余棋子数量）：小子:" << chessplay2[0] << "中子" << chessplay2[1] << "大子：" << chessplay2[2] << endl;
	cout << chess[6] << std::setw(4) << " |" << chess[7] << std::setw(4) << " |" << chess[8] << endl;
}

void palyerone() {
	int num,chara;
	Display(chess);
	cout << "选手1请输入落子区域和落子类型，示例为 1 1（数字空格数字）" << endl;
	cin >> num >> chara;
	while (1) {
		
		if (chessplay1[chara] == 0) {
			cout << "您没有该类型的棋子了，请重新输入" << endl;
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
				//获取该子的信息
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
					cout << "您吃不掉当前位置的棋子，请重新输入" << endl;
					cin >> num >> chara;
				}
			}
		
		
		}
	}

}
void playertwo() {
	int num, chara;
	Display(chess);
	cout << "选手2请输入落子区域和落子类型，示例为 1 1（数字空格数字）" << endl;
	cin >> num >> chara;
	while (1) {

		if (chessplay2[chara] == 0) {
			cout << "您没有该类型的棋子了，请重新输入" << endl;
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
				//获取该子的信息
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
					cout << "您吃不掉当前位置的棋子，请重新输入" << endl;
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
		//当两位选手的棋子全都用完仍然没有决出胜负就代表平局
		if (chessplay1[0] == 0 && chessplay1[1] == 0 && chessplay1[2] == 0) {
			break;
		}
	
	}
	return flag;
}
void WinMess(const int result) {
	if (result == 1) {
		cout << "选手1 win,选手2 lose" << endl;
	}
	else if (result == 0) {
		cout << "平局" << endl;
	}
	else {
		cout << "选手2 win,选手1 lose" << endl;
	}

}
int main(int argc, char* argv[]) {
	//展示规则
	showmenu();
	chess *playchess = new chess();
	while (1) {
		char goon='N';
		int result=Battle();
		WinMess(result);
		cout << "你还想来一场酣畅淋漓的井字棋比赛吗？请输入Y/N" <<endl ;
		cin >> goon;
		if(goon!='Y') {
			cout << "感谢您参与比赛，下次再来哦" << endl;
			break;
		}
		else {
			//重置棋盘
			for (int i = 0; i < 9; i++) {
				chess[i] = "   ";
			}
			//重置棋子数量
			for (int i = 0; i < 3; i++) {
				chessplay1[i] = 3;
				chessplay2[i] = 3;
			}
			cout << "游戏已重置！" << endl;
		}
		
	}



}