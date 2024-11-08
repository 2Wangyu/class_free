/*NAME:YU.
* DATE:22-12-15
* DESCRIPTION:Seat reservation procedure
*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define NUM 300
#include<string.h>
//NUM由座位数决定
int diaplay();
typedef struct train {
	char arr[20];//识别标志
	char a[10];//座位预定情况
	char xing[20];
	char ming[20];//性别名字
}EMU;
void reserve(EMU* message);
void deleteme(EMU* message);
void show(EMU* message);
void preserve(EMU* message);
int main() {
	FILE* p = fopen("message.txt", "r");
	if (p == NULL)
		printf("error\n");
	EMU message[300];
	//从文件中读取数据
	int i;
	for (i = 0; i < 300; i++) {
		fscanf(p, "%s%s%s%s", &message[i].arr, &message[i].a, &message[i].xing, &message[i].ming);
	}
	//向用户请求所需服务
	while (1) {
		display();
		int c; int d = 0;  int q;
		printf("请选择！");
		scanf("%d", &c);
		//退出
		if (c == 0) {
			preserve(message);
			break; }
		//显示空座位数
		else if (c == 1) {
			for (i = 0; i < 300; i++)
			{
				if ((message[i].a[0]) == 'O')//只要是O代表为空座位
					d++;
			}
			printf("剩余的空座位数为%d\n", d);
		}
		//显示座位信息
		else if (c == 2)
		{
			int j; int k = 1;
			for (i = 0; i < 300; i++) {
				{
					printf("%s:%c  ", message[i].arr, message[i].a[0]);
					if (i != 0 && (i + 1) % 6 == 0)
					{
						printf("\n");
					}//每6个换行
				}
			}
		}
		//显示座位信息
		else if (c == 3) {
			printf("请输入想要查看的座位信息");

			show(message);

		}
		//预定座位信息
		else if (c == 4)
		{
			for (i = 0; i < 300; i++) {
				if (message[i].a[0] == 'O')
					q = i;//保存预定的位置数，以便后面删除座位信息
			}
			reserve(&message[i]);
		}
		//删除预定信息
		else if (c == 5)
		{
			deleteme(&message[q]);
		}

		//保存预定信息
		else if (c == 6) {
			preserve(message);
		}
		//输入了错误的数字
		else {
			printf("您输入了错误数字，请重新输入\n");
		}
	}
	fclose(p);
	return 0;

}


//函数
int display() {
	printf("1.显示空座位总数.\n");
	printf("2.显示所有座椅的信息\n");
	printf("3.显示座位信息\n");
	printf("4.为您预定一个空座位\n");
	printf("5.删除您的座位预定\n");
	printf("6.保存当前预定\n");
	printf("0.退出\n");
}
void reserve(EMU* message) {
	printf("请输入您的信息,格式W为：性+空格+名\n");
	scanf("%s%s", message->xing, message->ming);
	message->a[0] = 'R';
}
//void baocun();
void deleteme(EMU* message) {
	message->a[0] = 'O';//修改成原来的格式
	char arr1[20] = { "空" };
	strcpy(message->xing, arr1);
	strcpy(message->ming, arr1);
}
void show(EMU message[300]) {
	printf("请输入您要查询的座位，格式按照例如1+空格+9+空格+6\n");
	int a = 0; int b = 0; int c = 0; int d = 0;
	scanf("%d%d%d", &a, &b, &c);
	d = 60 * (a - 1) + 6 * (b - 1) + c - 1;
	if (message[d].a[0] == 'O')
		printf("该座位为空座位\n");//空座位就不显示
	else {
		printf("%s%s", message[d].xing, message[d].ming);
	}
}
void preserve(EMU message[300]) {
	FILE* pfile;
	pfile = fopen("message.txt", "w"); int i;//将数据写入文件中
	for (int i = 0; i < 300; i++)
	{
		fprintf(pfile, "%s %s %s %s", message[i].a, message[i].arr, message[i].ming, message[i].xing);
	}
	fclose(pfile);
	pfile == NULL;//将整理修改后的LIST写入文件中

}