/*Date:22-12-11
* Name:YU.
* Description:������������֮�������
ID��22301056
*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
typedef struct {//�����ṹ��
	int month;
	int day;
	int year;
} MyDate;
int difDays( MyDate d1, MyDate d2);//��������
void showdate(mydate);
void swap(MyDate *d1,MyDate *d2);



int main()
{
	MyDate d1 = {0};
	MyDate d2 = {0};
	printf("�������һ������,����������\n");//�����û�������
	scanf("%d%d%d",&d1.year,&d1.month,&d1.day);
	printf("������ڶ�������\n");
	scanf("%d%d%d", &d2.year, &d2.month, &d2.day);
	//�ж�����Ⱥ�˳��,���ǰ��Ĵ�ͽ���
	if (d1.year > d2.year)
		swap(&d1, &d2);
	//��������֮���������̸�c
	int c = difDays(d1, d2);
	showdate(d1);//���ú�����ʾ���ڵĸ�ʽ
	printf("��");
	showdate(d2);
	printf("����������֮�����%d��", c);

	return 0;
}
int difDays(const MyDate d1, const MyDate d2) {
	int count = 0;
	int midday = 0;//��������֮�����������
	int stday = 0;//����ǰһ�������
	int endday = 0;//�����һ�������
	int a = d1.year;
	int b = d2.year;
	for (int c = a + 1; c < b; c++) {
		if ((c % 4 == 0 && c % 100 != 0) || (c % 400 == 0))
			midday += 366;
		else
		{
			midday += 365;
		}
	}//�����м������
	int arr1[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	int arr2[12] = { 31,29,31,30,31,30,31,31,30,31,30,31 };
	if ((d2.year % 4 == 0 && d2.year % 100 != 0) || (d2.year % 400 == 0)) {//������������������������
		for (int d = d2.month - 2; d >= 0; d--) {//����������ʼ�ۼ�
			endday += arr2[d];//���һ���²�����ȫ��-1���±���-1
		}
		endday += d2.day;
	}
	else {
		for (int d = d2.month - 2; d >= 0; d--) {//����������ʼ�ۼ�
			endday += arr1[d];//���һ���²�����ȫ��-1���±���-1
		}
		endday += d2.day;
	}

	if ((d1.year % 4 == 0 && d1.year % 100 != 0) || (d1.year % 400 == 0))
	{
		for (int d = d1.month; d <= 11; d++)//����һ���¿�ʼ�㵽��ĩ
		{
			stday += arr2[d];
		}
		stday = stday + arr2[d1.month - 2] - d1.day;//���µ�����Ϊ��ĩ��ȥday
	}
	else {
		for (int d = d1.month; d <= 11; d++)
		{
			stday += arr1[d];
		}
		stday = stday + arr1[d1.month - 2] - d1.day;
	}

	count = midday + stday + endday;//�����ĺ�Ϊ��������
	return count;
	}
void showdate(MyDate day) 
{
	printf("%d-%d-%d", day.year, day.month, day.day);
}
void swap(MyDate* d1, MyDate* d2) {
	MyDate tem;
	tem = *d1;
	*d1 = *d2;
	*d2 = tem;
}



//year % 4 == 0 && year % 100 != 0 ) || (year % 400 == 0