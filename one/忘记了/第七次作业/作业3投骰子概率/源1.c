/*NAME:YU.
Date:22-11-7
Description:计算骰子的概率*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void qiuhe(int* arr[11], int times) {//获取2-12对应的次数并存入数组中

	int i, sum; int a = 0; int b = 0;
	srand((unsigned int)time(NULL));
	for (i = 0; i < times; i++) {//循环360000次随机获取和
		
		a = rand()%6+1 ;
		b = rand()%6+1 ;
		sum = a + b;
		arr[sum - 2] = arr[sum - 2] + 1;//将和对应数算入一次存入数组
	}

}
void display(int arr[11]) {//打印出对应次数和百分比

	int i;
	for (i = 0; i < 11; i++) {
		printf("和为%d时的投掷次数为%d\n", i + 2, arr[i]);
	}
	for (i = 0; i < 11; i++) {
		double a = arr[i] / 360000.0;
		printf("和为%d时的投掷次数的百分比为：%lf\n", i + 2, a);

	}
}
int main() {

	int arr[11] = {0};

	qiuhe(arr, 360000);
	display(arr);
	return 0;
}