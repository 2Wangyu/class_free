#include "chess.h"

chess::chess()
{
	for (int i = 0; i < 9; i++) {
		onechess.push_back("   ");
	
	}
	//vector<string> onechess(9, "   ");
}
int chess::whetherwin()
{
	const string temp = "   ";
	if (onechess[0] != temp && (onechess[0])[0] == onechess[1][0] && onechess[1][0] == onechess[2][0]) {
		//cout<<(chess[0])[0]<<endl;
		return onechess[0][0] - '0';
	}
	else if (onechess[3] != temp && onechess[3][0] == onechess[4][0] && onechess[4][0] == onechess[5][0]) {
		return onechess[3][0] - '0';

	}
	else if (onechess[6] != temp && onechess[6][0] == onechess[7][0] && onechess[7][0] == onechess[8][0]) {
		return onechess[6][0] - '0';
	}
	else if (onechess[0] != temp && onechess[0][0] == onechess[3][0] && onechess[3][0] == onechess[6][0]) {
		return onechess[0][0] - '0';
	}
	else if (onechess[1] != temp && onechess[1][0] == onechess[4][0] && onechess[4][0] == onechess[7][0]) {
		return onechess[1][0] - '0';
	}
	else if (onechess[2] != temp && onechess[2][0] == onechess[5][0] && onechess[5][0] == onechess[8][0]) {
		return onechess[2][0] - '0';
	}
	else if (onechess[0] != temp && onechess[0][0] == onechess[4][0] && onechess[4][0] == onechess[8][0]) {
		return onechess[0][0] - '0';
	}
	else if (onechess[2] != temp && onechess[2][0] == onechess[4][0] && onechess[6][0] == onechess[4][0]) {
		return onechess[2][0] - '0';
	}
	else {
		return 0;
	}
}