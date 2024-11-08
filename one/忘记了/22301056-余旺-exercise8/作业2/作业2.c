/*NAME:YU.
* DATE:11-23
* DESCRIPTION:从文件读数并进行相应处理
*
*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define ROW 4
#define COL 5
void readarray(int arr[ROW][COL]);
int Maxvalue(int arr[ROW][COL]);//函数声明
int Ave_v(int arr[ROW][COL]);
int Ave_v2(int arr[ROW][COL]);


		int main() {
			int arr[4][5] = { 0 };
			readarray(arr);
			Ave_v(arr);//无返回值
			int b = 0; int c = 0; int d = 0;
			b=Ave_v2(arr);//有返回值
			d=Maxvalue(arr);
			printf("所有数的平均值为%d\n", b);
			printf("所有数中的最大值为%d\n", d);

			return 0;
		}

		void readarray(int arr[ROW][COL]) {
			FILE* pa = fopen("date.txt", "r");
			if (pa == NULL) {

				printf("%s", "error\n");//确保非空
			}

				int i, j;
				for (i = 0; i <= ROW - 1; i++) {
					for (j = 0; j <= COL - 1; j++) {
						//用循环获取文件中的数字
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
					int a = 0;//每一行初始化a为0
					for (j = 0; j <= COL - 1; j++) {
						a = a + arr[i][j];
					}
					printf("第%d行的数组的平均值为%lf\n", i, a/5.0);
				}
			}

			int Ave_v2(int arr[ROW][COL]) {
				int i, j; int tem=0;
				for (i = 0; i <= ROW - 1; i++) {
					for (j = 0; j <= COL - 1; j++) {
						/*if (arr[0][0] < arr[i][j]);*/
						tem = tem + arr[i][j];//将arr中所有数加起来
					}
				}
				tem = tem / (ROW * COL);
				return tem;
				}

			int Maxvalue(int arr[ROW][COL]) {
				int i, j;
				int c = arr[0][0];//将c 初始化为数字中第一个数

				for (i = 0; i <= ROW - 1; i++) {
					for (j = 0; j <= COL - 1; j++) {
						if (c < arr[i][j])
							c = arr[i][j];//那个大，就存到c 中
					}
				}
				return c;


			}