/*NAME:YU.
Date:22-11-7
Description:�������ӵĸ���*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void qiuhe(int* arr[11], int times) {//��ȡ2-12��Ӧ�Ĵ���������������

	int i, sum; int a = 0; int b = 0;
	srand((unsigned int)time(NULL));
	for (i = 0; i < times; i++) {//ѭ��360000�������ȡ��
		
		a = rand()%6+1 ;
		b = rand()%6+1 ;
		sum = a + b;
		arr[sum - 2] = arr[sum - 2] + 1;//���Ͷ�Ӧ������һ�δ�������
	}

}
void display(int arr[11]) {//��ӡ����Ӧ�����Ͱٷֱ�

	int i;
	for (i = 0; i < 11; i++) {
		printf("��Ϊ%dʱ��Ͷ������Ϊ%d\n", i + 2, arr[i]);
	}
	for (i = 0; i < 11; i++) {
		double a = arr[i] / 360000.0;
		printf("��Ϊ%dʱ��Ͷ�������İٷֱ�Ϊ��%lf\n", i + 2, a);

	}
}
int main() {

	int arr[11] = {0};

	qiuhe(arr, 360000);
	display(arr);
	return 0;
}