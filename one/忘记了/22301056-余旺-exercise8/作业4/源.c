/*NAME:YU.
* DATE:12-04
* DESCRIPTION:���ı��ļ��е������޸Ĳ���ɾ��
*
*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define MAX 100
#include<string.h>
#include<stdlib.h>


void getHolidays(char* fIlename, char holidayList[MAX][100]);//��������
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
		return 0;//���Ϊ��ָ�����ȡʧ��,�����ٽ���
	}

	const char* Filename = "Holdays.txt";
	char holidayList[MAX][100] = { 0 };
	getHolidays(Filename, holidayList);//���ļ������ݴ浽holidayList��
	int listlength = getList(holidayList);
	putslist1(holidayList, listlength);
	choices(holidayList, Filename);//��ӻ�ɾ����Ŀ�б�
	
	close(pa);
	pa == NULL;
	return 0;
}

void getHolidays(char* filename, char holidayList[MAX][100]) {
	FILE* pa;
	pa = fopen("Holidays.txt", "r");
	int i = 0; /*int j = 0;*/
	for (i = 0; i < MAX; i++) {

		fgets(holidayList[i], 100, pa);//��ȡ�ļ���ÿһ�����ݴ浽�����ÿһ����
	}
}
void choices(char holidayList[MAX][100], char* filename) {
	while (1) {
		printf("��ѡ��\n");
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
			if (n > 0) {//���n����0�������ɾ�����޸Ĺ� 
				printf("�Ƿ񱣴�(1.Y 2.N)\n");
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
		a = i;//�����м����a��Ϊ�±��м���
		for (j = i + 1; j < listLength; j++)
		{//���ѭ�����ڻ�ȡi֮���ÿһ���±�
			if (strcmp(holidayList[a], holidayList[j])>0)
			{
				a = j;//������ҵ�һ����a��Ӧ���и�С��ȷ������ǰ��
			}
			if (a != i)
			{
				char temp[100];
				strcpy(temp, holidayList[a]);
				strcpy(holidayList[a], holidayList[i]);
				strcpy(holidayList[i], temp);//ѭ�������ҵ���С��һ�У����л���
				//ÿ��ѭ������ǰ���һ��ȷ��
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
			if(holidayList[i][j]=='\n')//����������з��ʹ�����һ�е�����
			a++;
	}
	return a+1;//���һ�в�����л��з�����Ҫ����
	
}
void changelist1(char holidayList[MAX][100], int *listlengh, int a) {
	if (a == 1) {
		printf("����������Ҫ��ӵĽ������У���Ҫ�ظ���ע���ʽ\n");
		char newholiday[100];
		gets_s(newholiday,20);//  VS2019,get��get_s�Ҷ�����������ȥ
		strcat(newholiday, "\n");//׷�ӻ��з�
		strcpy(holidayList[(*listlengh)++], newholiday);
		*listlengh=*listlengh + 1;
		int h = *listlengh;//��������
		sortList(holidayList, h);
		putslist1(holidayList, h);
	}
	if (a == 2) {
		int d;
		char deleteholiday[MAX] ;
		printf("������Ҫɾ���ļ��գ�ע��������һ��\n");
		gets_s(deleteholiday,20);
		strcat(deleteholiday, "\n");//���ϻ��з�
		for (int i = 0; i < *listlengh; i++)//�ҵ���ɾ������
		{
			int b=0;
			if (strcmp(holidayList[i], deleteholiday))
			{
				(*listlengh)--;
				 b= 1;//�ҵ���Ӧ�оͿ�ʼһ��һ������copy
			}
				if(b==1){
					strcpy(holidayList[i], holidayList[i + 1]);
				}
			}
		}
	*listlengh = *listlengh -1;
	int g = *listlengh;//��������
	sortList(holidayList, g);
	putslist1(holidayList, g);
	}

void putslist1(char holidayList[MAX][100], int listlength) {
	int i = 0;
	while (i < listlength) {
		puts(holidayList[i]);
		i++;
	}//��������ʾ����Ļ��
}
void baocun(char* filename,int listlengh,char *holidayList) {
	FILE* pfile;
	pfile = fopen(filename, "w");
	for (int i = 0; i < listlengh; i++)
		fputs(holidayList[i], pfile);
	fputs("", pfile);
	fclose(pfile);
	pfile == NULL;//�������޸ĺ��LISTд���ļ���

}