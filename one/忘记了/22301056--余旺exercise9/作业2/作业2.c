/*Name:YU.
* DATE:22-12-15
* Description:计算车队的每加仑平均英里数
*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define NUM 5

typedef struct carmessage {
	char c[20];//分别用来存放Car Number，Mils Driven，Gallons Used
	int a;
	int b;
}car;
double averagecost(car d1)
{
	double g =(double) d1.a/(double)d1.b;//求平均值
	printf("%lf", g);
	return g;
}

int main() {
	double h=0;
	FILE* p = fopen("record.txt","r");
	if (p == NULL) {
		printf("error\n");
	}
	int i=0;
	car arr[5]; int k = 0;
	while (k<NUM) {
		//从文件中读取的次数取决于车辆数即为NUM
		fscanf(p, "%s%d%d", &arr[i].c, &arr[i].a, &arr[i].b);
		i++; //将文件中的数据遍历存进结构数组中
		k++;
	}
	printf("%-24s","车辆编号");
	printf("每加仑英里数\n");
	for (int d = 0; d < NUM; d++) {
		printf("%-24s", arr[d].c);
		h+=averagecost(arr[d]);//把每辆车的平均数累加
		printf("\n");
	}
	printf("整个车队每加仑的平均英里数为%lf", h / 5);
	fclose(p);
	p = NULL;
	return 0;
}