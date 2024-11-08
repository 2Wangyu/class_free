/*NAME:YU.
* DATE:11-23
* DESCRIPTION:进行三子棋的游戏
*/

#include<Windows.h>
#include<stdio.h>
#include<string.h>
void playgameX(char* array, int n);
void playgameO(char* array, int n);
char panduan(char* array);
void goto_xy(int x, int y);


void goto_xy(int x, int y)//定位光标位置到指定坐标
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { x,y };
	SetConsoleCursorPosition(hOut, pos);
}
char display(char* array) {
	int i; int n = 0;
	int sz = strlen(array);//求数组中元素个数
	for (i = 0; i <= sz - 1; i++) {
		if (n > 0 && (n % 3 == 0)) {
			printf("\n");//每打印三个数字换行
		}
		n++;
		printf("%8c", *array);
		array++;//每打印一次向后地址移动一次，征求下一个
	}
	printf("\n");
}

void playGame(char *array) {
	while (1) {
		char b;
		static int n = 9;//使n能随游戏进行能够不断改变
		playgameX(array, n);
		b = panduan(array);
		n--;
		if (n == 0)
		{
			printf("平局");//平局的情况只会在X玩家出现
			break;
		}
		if (b == 'X')
		{
			printf("玩家X赢了");
			break;
		}
		system("cls");
		goto_xy(0, 0);
		playgameO(array, n);//将初始化的棋盘打印出来
		b = panduan(array);
		n--;
		if (b == 'O')
		{
			printf("玩家O赢了");
			break;
		}
		system("cls");
		goto_xy(0, 0);
	}
}
void playgameX(char *array, int n) {
	display(array);
	printf("玩家X,请输入1-9代表你想下棋子的位置.\n");
	printf("棋盘上还%d个空格\n", n);
	while (1) {
		int a = 0;
		scanf_s("%d", &a);
		if (*(array+a-1)!= (char)('1' + a-1)) {
			printf("您下棋的位置已被占用请重新下棋\n");
		}
		else {
			*(array + a - 1) = 'X';
			break;
		}
	}

}
void playgameO(char* array, int n) {
	int a = 0;
	display(array);
	printf("玩家O,请输入1-9代表你想下棋子的位置.\n");
	printf("棋盘上还%d个空格\n", n);
	while (1) {
		scanf_s("%d", &a);
		if (array[a-1] = !(char)('1'+a-1) ){
			printf("您下棋的位置已被占用请重新下棋\n");//如果被占用就重复获取下棋位置
		}
		else {
			*(array + a - 1) = 'O';//否则下棋
			break;
		}
	}
}
char panduan(char *array) {//两条对角线的判断
	if ((*array == *(array + 4)) && (*(array + 4) == *(array + 8)))
		return *array;
	if ((*(array + 2) == *(array + 4)) && (*(array + 4) == *(array + 6)))
		return *(array + 2);

	//判断每一行的赢法
	if ((*array == *(array + 1)) && (*(array + 1) == *(array + 2)))
		return *array;
	if ((*(array + 3) == *(array + 4)) && (*(array + 4) == *(array + 5)))
		return *(array + 3);
	if ((*(array + 6) == *(array + 7)) && (*(array + 7) == *(array + 8)))
		return *(array + 6);


	//判断每一列的赢法
	if ((*array == *(array + 3)) && (*(array + 3) == *(array + 6)))
		return *array;
	if ((*(array + 1) == *(array + 4)) && (*(array + 4) == *(array + 7)))
		return *(array + 1);
	if ((*(array + 2) == *(array + 5)) && (*(array + 5) == *(array + 8)))
		return *(array + 2);

	//反之返回一个非X,O的字符
	else return 'a';
}


int main()
{
	char array[10];
	//initialize array prior to playing
	for (int i = 0; i < 10; i++)
	{
		array[i] = (char)('1' + i);
		/*array[i] = 'i+1';*/
	}
	array[9] = '\0';
	playGame(array);






	return 0;
}