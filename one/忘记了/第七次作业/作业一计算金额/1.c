/*NAME:YU.
Date:22-11-7
Description:������*/
#include<stdio.h>
#define members 5
//����͵ĺ��������Ӧtotal
double sum(double arr[members], int a) {
	int i; double b=0;
	for (i = 0; i < a; i++) {
		b += arr[i];
	}
	return b;
}
//���û���������
void getUnits(double* units, int a)
{
	printf("������5����������С��\n");
	int i;
	for (i = 0; i < a; i++) {
		scanf_s("%lf", &units[i]);
	}
}
//�����ܽ��
void calcAmount(double prices[members], double units[members], double* amts, int a) {
	int i;
	for (i = 0; i < a; i++) {
		amts[i] = prices[i] * units[i];
	}
}
//��ӡ��table
void display(double units[members], double prices[members], double amt[members], int a) {
	int i;double b, c;
	printf("%8s %8s %8s", "Price", "Units", "Amount");
	printf("\n");
	printf("-------- -------- --------\n");
	for (i = 0; i < a; i++) {
		printf("%8.2lf %8.2lf %8.2lf", prices[i], units[i], amt[i]);
		printf("\n");
	}
	b = sum(units, members);
	c = sum(amt, members);
	printf("%8s %8.2lf %8.2lf", "Total:", b, c);
	printf("\n");
	printf("-------- -------- --------");
}

int main()
{
	double units[members]; double prices[members] = { 9.92,6.32,12.63,5.95,10.29 };
	double amts[members];
	getUnits(units, members);
	calcAmount(prices, units, amts, members);
	display(units, prices, amts, members);


	return 0;
}