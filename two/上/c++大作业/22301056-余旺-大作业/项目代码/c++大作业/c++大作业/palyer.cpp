#include"player.h"
#include<iostream>
#include <iomanip>
#include <string>
using namespace std;


player::player(){
	
}
void player::Display( vector<string>* chess, const int* arr1, const int* arr2) {
	cout << "棋盘目前战况：" << endl;

	/*cout << chess[0].substr(0, 4) << endl;
	cout.write(chess[0].c_str(),4) << endl;*/
	cout << (*chess)[0] << " |" << (*chess)[1] << " |" << (*chess)[2] << endl;
	cout << "———————————————" << "  选手1（剩余棋子数量）：小子: " << arr1[0] << " 中子: " << arr1[1] << " 大子：" << arr1[2] << endl;
	cout << (*chess)[3] << " |" << (*chess)[4] << " |" << (*chess)[5] << endl;
	cout << "———————————————" << "  选手2（剩余棋子数量）：小子: " << arr2[0] << " 中子: " << arr2[1] << " 大子：" << arr2[2] << endl;
	cout << (*chess)[6] << " |" << (*chess)[7] << " |" << (*chess)[8] << endl;
}
void player::playchess(int playnum,vector<string>* chess,int *arr) {
	int num, chara;
	cout << "选手"<<to_string(playnum)<<":请输入落子区域和落子类型，示例为 1 1（数字空格数字）" << endl;
	cin >> num >> chara;
	while (1) {

		if (arr[chara] == 0||chara>2) {
			cout << "您没有该类型的棋子了，请重新输入" << endl;
			cin >> num >> chara;
			continue;
		}
		if (num<= 0 || num > 9) {
			cout << "超出指定区域，请重新输入" << endl;
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
					cout << "您吃不掉当前位置的棋子，请重新输入" << endl;
					cin >> num >> chara;
				}
			}


		}
	}





}