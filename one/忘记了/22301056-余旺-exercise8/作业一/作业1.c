/*NAME:YU.
* DATE:11-23
* DESCRIPTION:�������������Ϸ
*/

#include<Windows.h>
#include<stdio.h>
#include<string.h>
void playgameX(char* array, int n);
void playgameO(char* array, int n);
char panduan(char* array);
void goto_xy(int x, int y);


void goto_xy(int x, int y)//��λ���λ�õ�ָ������
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { x,y };
	SetConsoleCursorPosition(hOut, pos);
}
char display(char* array) {
	int i; int n = 0;
	int sz = strlen(array);//��������Ԫ�ظ���
	for (i = 0; i <= sz - 1; i++) {
		if (n > 0 && (n % 3 == 0)) {
			printf("\n");//ÿ��ӡ�������ֻ���
		}
		n++;
		printf("%8c", *array);
		array++;//ÿ��ӡһ������ַ�ƶ�һ�Σ�������һ��
	}
	printf("\n");
}

void playGame(char *array) {
	while (1) {
		char b;
		static int n = 9;//ʹn������Ϸ�����ܹ����ϸı�
		playgameX(array, n);
		b = panduan(array);
		n--;
		if (n == 0)
		{
			printf("ƽ��");//ƽ�ֵ����ֻ����X��ҳ���
			break;
		}
		if (b == 'X')
		{
			printf("���XӮ��");
			break;
		}
		system("cls");
		goto_xy(0, 0);
		playgameO(array, n);//����ʼ�������̴�ӡ����
		b = panduan(array);
		n--;
		if (b == 'O')
		{
			printf("���OӮ��");
			break;
		}
		system("cls");
		goto_xy(0, 0);
	}
}
void playgameX(char *array, int n) {
	display(array);
	printf("���X,������1-9�������������ӵ�λ��.\n");
	printf("�����ϻ�%d���ո�\n", n);
	while (1) {
		int a = 0;
		scanf_s("%d", &a);
		if (*(array+a-1)!= (char)('1' + a-1)) {
			printf("�������λ���ѱ�ռ������������\n");
		}
		else {
			*(array + a - 1) = 'X';
			break;
		}
	}

}
void playgameO(char* array, int n) {
	int a = 0;
	display(array);
	printf("���O,������1-9�������������ӵ�λ��.\n");
	printf("�����ϻ�%d���ո�\n", n);
	while (1) {
		scanf_s("%d", &a);
		if (array[a-1] = !(char)('1'+a-1) ){
			printf("�������λ���ѱ�ռ������������\n");//�����ռ�þ��ظ���ȡ����λ��
		}
		else {
			*(array + a - 1) = 'O';//��������
			break;
		}
	}
}
char panduan(char *array) {//�����Խ��ߵ��ж�
	if ((*array == *(array + 4)) && (*(array + 4) == *(array + 8)))
		return *array;
	if ((*(array + 2) == *(array + 4)) && (*(array + 4) == *(array + 6)))
		return *(array + 2);

	//�ж�ÿһ�е�Ӯ��
	if ((*array == *(array + 1)) && (*(array + 1) == *(array + 2)))
		return *array;
	if ((*(array + 3) == *(array + 4)) && (*(array + 4) == *(array + 5)))
		return *(array + 3);
	if ((*(array + 6) == *(array + 7)) && (*(array + 7) == *(array + 8)))
		return *(array + 6);


	//�ж�ÿһ�е�Ӯ��
	if ((*array == *(array + 3)) && (*(array + 3) == *(array + 6)))
		return *array;
	if ((*(array + 1) == *(array + 4)) && (*(array + 4) == *(array + 7)))
		return *(array + 1);
	if ((*(array + 2) == *(array + 5)) && (*(array + 5) == *(array + 8)))
		return *(array + 2);

	//��֮����һ����X,O���ַ�
	else return 'a';
}


int main()
{
	char array[10];
	//initialize array prior to playing
	for (int i = 0; i < 10; i++)
	{
		array[i] = (char)('1' + i);
		/*array[i] = 'i+1';*/
	}
	array[9] = '\0';
	playGame(array);






	return 0;
}