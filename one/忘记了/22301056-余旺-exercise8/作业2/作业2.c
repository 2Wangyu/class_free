/*NAME:YU.
* DATE:11-23
* DESCRIPTION:���ļ�������������Ӧ����
*
*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define ROW 4
#define COL 5
void readarray(int arr[ROW][COL]);
int Maxvalue(int arr[ROW][COL]);//��������
int Ave_v(int arr[ROW][COL]);
int Ave_v2(int arr[ROW][COL]);


		int main() {
			int arr[4][5] = { 0 };
			readarray(arr);
			Ave_v(arr);//�޷���ֵ
			int b = 0; int c = 0; int d = 0;
			b=Ave_v2(arr);//�з���ֵ
			d=Maxvalue(arr);
			printf("��������ƽ��ֵΪ%d\n", b);
			printf("�������е����ֵΪ%d\n", d);

			return 0;
		}

		void readarray(int arr[ROW][COL]) {
			FILE* pa = fopen("date.txt", "r");
			if (pa == NULL) {

				printf("%s", "error\n");//ȷ���ǿ�
			}

				int i, j;
				for (i = 0; i <= ROW - 1; i++) {
					for (j = 0; j <= COL - 1; j++) {
						//��ѭ����ȡ�ļ��е�����
						fscanf(pa, "%d", &arr[i][j]);
					}
				}
				fclose(pa);
				pa = NULL;
			}
		

			int Ave_v(int arr[ROW][COL])
			{
				int i; int j; 
				for (i = 0; i <= ROW - 1; i++) {
					int a = 0;//ÿһ�г�ʼ��aΪ0
					for (j = 0; j <= COL - 1; j++) {
						a = a + arr[i][j];
					}
					printf("��%d�е������ƽ��ֵΪ%lf\n", i, a/5.0);
				}
			}

			int Ave_v2(int arr[ROW][COL]) {
				int i, j; int tem=0;
				for (i = 0; i <= ROW - 1; i++) {
					for (j = 0; j <= COL - 1; j++) {
						/*if (arr[0][0] < arr[i][j]);*/
						tem = tem + arr[i][j];//��arr��������������
					}
				}
				tem = tem / (ROW * COL);
				return tem;
				}

			int Maxvalue(int arr[ROW][COL]) {
				int i, j;
				int c = arr[0][0];//��c ��ʼ��Ϊ�����е�һ����

				for (i = 0; i <= ROW - 1; i++) {
					for (j = 0; j <= COL - 1; j++) {
						if (c < arr[i][j])
							c = arr[i][j];//�Ǹ��󣬾ʹ浽c ��
					}
				}
				return c;


			}