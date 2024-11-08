/*NAME:YU.
Date:22-11-7
Description:计算金额*/
#include<stdio.h>
#define members 5
//用求和的函数求出对应total
double sum(double arr[members], int a) {
	int i; double b=0;
	for (i = 0; i < a; i++) {
		b += arr[i];
	}
	return b;
}
//向用户请求数据
void getUnits(double* units, int a)
{
	printf("请输入5个数，保留小数\n");
	int i;
	for (i = 0; i < a; i++) {
		scanf_s("%lf", &units[i]);
	}
}
//计算总金额
void calcAmount(double prices[members], double units[members], double* amts, int a) {
	int i;
	for (i = 0; i < a; i++) {
		amts[i] = prices[i] * units[i];
	}
}
//打印出table
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