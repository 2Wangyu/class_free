/*Name:YU.
* DATE:22-12-15
* Description:���㳵�ӵ�ÿ����ƽ��Ӣ����
*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define NUM 5

typedef struct carmessage {
	char c[20];//�ֱ��������Car Number��Mils Driven��Gallons Used
	int a;
	int b;
}car;
double averagecost(car d1)
{
	double g =(double) d1.a/(double)d1.b;//��ƽ��ֵ
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
		//���ļ��ж�ȡ�Ĵ���ȡ���ڳ�������ΪNUM
		fscanf(p, "%s%d%d", &arr[i].c, &arr[i].a, &arr[i].b);
		i++; //���ļ��е����ݱ�������ṹ������
		k++;
	}
	printf("%-24s","�������");
	printf("ÿ����Ӣ����\n");
	for (int d = 0; d < NUM; d++) {
		printf("%-24s", arr[d].c);
		h+=averagecost(arr[d]);//��ÿ������ƽ�����ۼ�
		printf("\n");
	}
	printf("��������ÿ���ص�ƽ��Ӣ����Ϊ%lf", h / 5);
	fclose(p);
	p = NULL;
	return 0;
}