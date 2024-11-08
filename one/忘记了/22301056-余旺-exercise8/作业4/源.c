/*NAME:YU.
* DATE:12-04
* DESCRIPTION:对文本文件中的内容修改并且删改
*
*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define MAX 100
#include<string.h>
#include<stdlib.h>


void getHolidays(char* fIlename, char holidayList[MAX][100]);//声明函数
void choices(char holidayList[MAX][100], char* Filename);
void baocun(char* filename, int listlengh, char* holidayList);
void sortlist();
int getList(holidayList);
void changelist1(char holidayList[MAX][100], int listlengh, int a);
void putslist1(char* holidayList, int listlength);
int main()
{
	FILE* pa;
	pa = fopen("Holidays.txt", "r");
	if (pa == NULL) {
		printf("error\n");
		return 0;//如果为空指针则读取失败,程序不再进行
	}

	const char* Filename = "Holdays.txt";
	char holidayList[MAX][100] = { 0 };
	getHolidays(Filename, holidayList);//将文件的数据存到holidayList中
	int listlength = getList(holidayList);
	putslist1(holidayList, listlength);
	choices(holidayList, Filename);//添加或删除节目列表
	
	close(pa);
	pa == NULL;
	return 0;
}

void getHolidays(char* filename, char holidayList[MAX][100]) {
	FILE* pa;
	pa = fopen("Holidays.txt", "r");
	int i = 0; /*int j = 0;*/
	for (i = 0; i < MAX; i++) {

		fgets(holidayList[i], 100, pa);//获取文件中每一行数据存到数组的每一行中
	}
}
void choices(char holidayList[MAX][100], char* filename) {
	while (1) {
		printf("请选择\n");
		printf("1->add,2->delete,3->exit\n");
		int a = 0;
		scanf_s("%d", &a);
		static int n = 0;
		int listlength = getList(holidayList);
		if (a == 1 || a == 2) {
			changelist1(holidayList, &listlength, a);
			n++;
		}
		if (a == 3) {
			if (n > 0) {//如果n大于0代表进行删除或修改过 
				printf("是否保存(1.Y 2.N)\n");
				int c;
				scanf_s("%d", &c);
				if (c == 1) {
					baocun(filename, listlength, holidayList[MAX][100]);
				}
			}
			break;
		}
	}
}
sortList(char(*holidayList)[100], int listLength) {
	int i = 0; int j = 0; int a = 0; int n = 0;
	for (i = 0; i < listLength - 1; i++)
	{
		a = i;//创建中间变量a作为下标中间量
		for (j = i + 1; j < listLength; j++)
		{//这次循环用于获取i之后的每一个下标
			if (strcmp(holidayList[a], holidayList[j])>0)
			{
				a = j;//如果能找到一个比a对应的行更小就确定排在前面
			}
			if (a != i)
			{
				char temp[100];
				strcpy(temp, holidayList[a]);
				strcpy(holidayList[a], holidayList[i]);
				strcpy(holidayList[i], temp);//循环结束找到最小的一行，进行换行
				//每次循环后最前面的一行确定
			}
		}
	}
}
int getList(char(*holidayList)[100])
{
	int a = 0;
	
	FILE* pa;
	pa = fopen("Holidays.txt", "r");
	int i = 0; int j;
	for (i = 0; i < MAX; i++) {
		for(j=0;j<100;j++)
			if(holidayList[i][j]=='\n')//如果读到换行符就代表有一行的数据
			a++;
	}
	return a+1;//最后一行不会带有换行符，需要加上
	
}
void changelist1(char holidayList[MAX][100], int *listlengh, int a) {
	if (a == 1) {
		printf("请输入您想要添加的节日序列，不要重复，注意格式\n");
		char newholiday[100];
		gets_s(newholiday,20);//  VS2019,get和get_s我都不能运行下去
		strcat(newholiday, "\n");//追加换行符
		strcpy(holidayList[(*listlengh)++], newholiday);
		*listlengh=*listlengh + 1;
		int h = *listlengh;//行数增加
		sortList(holidayList, h);
		putslist1(holidayList, h);
	}
	if (a == 2) {
		int d;
		char deleteholiday[MAX] ;
		printf("请输入要删除的假日，注意与所给一致\n");
		gets_s(deleteholiday,20);
		strcat(deleteholiday, "\n");//加上换行符
		for (int i = 0; i < *listlengh; i++)//找到需删除的行
		{
			int b=0;
			if (strcmp(holidayList[i], deleteholiday))
			{
				(*listlengh)--;
				 b= 1;//找到对应行就开始一行一行网上copy
			}
				if(b==1){
					strcpy(holidayList[i], holidayList[i + 1]);
				}
			}
		}
	*listlengh = *listlengh -1;
	int g = *listlengh;//行数减少
	sortList(holidayList, g);
	putslist1(holidayList, g);
	}

void putslist1(char holidayList[MAX][100], int listlength) {
	int i = 0;
	while (i < listlength) {
		puts(holidayList[i]);
		i++;
	}//将数据显示在屏幕上
}
void baocun(char* filename,int listlengh,char *holidayList) {
	FILE* pfile;
	pfile = fopen(filename, "w");
	for (int i = 0; i < listlengh; i++)
		fputs(holidayList[i], pfile);
	fputs("", pfile);
	fclose(pfile);
	pfile == NULL;//将整理修改后的LIST写入文件中

}