/*NAME:YU.
* DATE:22-12-15
* DESCRIPTION:Seat reservation procedure
*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define NUM 300
#include<string.h>
//NUM����λ������
int diaplay();
typedef struct train {
	char arr[20];//ʶ���־
	char a[10];//��λԤ�����
	char xing[20];
	char ming[20];//�Ա�����
}EMU;
void reserve(EMU* message);
void deleteme(EMU* message);
void show(EMU* message);
void preserve(EMU* message);
int main() {
	FILE* p = fopen("message.txt", "r");
	if (p == NULL)
		printf("error\n");
	EMU message[300];
	//���ļ��ж�ȡ����
	int i;
	for (i = 0; i < 300; i++) {
		fscanf(p, "%s%s%s%s", &message[i].arr, &message[i].a, &message[i].xing, &message[i].ming);
	}
	//���û������������
	while (1) {
		display();
		int c; int d = 0;  int q;
		printf("��ѡ��");
		scanf("%d", &c);
		//�˳�
		if (c == 0) {
			preserve(message);
			break; }
		//��ʾ����λ��
		else if (c == 1) {
			for (i = 0; i < 300; i++)
			{
				if ((message[i].a[0]) == 'O')//ֻҪ��O����Ϊ����λ
					d++;
			}
			printf("ʣ��Ŀ���λ��Ϊ%d\n", d);
		}
		//��ʾ��λ��Ϣ
		else if (c == 2)
		{
			int j; int k = 1;
			for (i = 0; i < 300; i++) {
				{
					printf("%s:%c  ", message[i].arr, message[i].a[0]);
					if (i != 0 && (i + 1) % 6 == 0)
					{
						printf("\n");
					}//ÿ6������
				}
			}
		}
		//��ʾ��λ��Ϣ
		else if (c == 3) {
			printf("��������Ҫ�鿴����λ��Ϣ");

			show(message);

		}
		//Ԥ����λ��Ϣ
		else if (c == 4)
		{
			for (i = 0; i < 300; i++) {
				if (message[i].a[0] == 'O')
					q = i;//����Ԥ����λ�������Ա����ɾ����λ��Ϣ
			}
			reserve(&message[i]);
		}
		//ɾ��Ԥ����Ϣ
		else if (c == 5)
		{
			deleteme(&message[q]);
		}

		//����Ԥ����Ϣ
		else if (c == 6) {
			preserve(message);
		}
		//�����˴��������
		else {
			printf("�������˴������֣�����������\n");
		}
	}
	fclose(p);
	return 0;

}


//����
int display() {
	printf("1.��ʾ����λ����.\n");
	printf("2.��ʾ�������ε���Ϣ\n");
	printf("3.��ʾ��λ��Ϣ\n");
	printf("4.Ϊ��Ԥ��һ������λ\n");
	printf("5.ɾ��������λԤ��\n");
	printf("6.���浱ǰԤ��\n");
	printf("0.�˳�\n");
}
void reserve(EMU* message) {
	printf("������������Ϣ,��ʽWΪ����+�ո�+��\n");
	scanf("%s%s", message->xing, message->ming);
	message->a[0] = 'R';
}
//void baocun();
void deleteme(EMU* message) {
	message->a[0] = 'O';//�޸ĳ�ԭ���ĸ�ʽ
	char arr1[20] = { "��" };
	strcpy(message->xing, arr1);
	strcpy(message->ming, arr1);
}
void show(EMU message[300]) {
	printf("��������Ҫ��ѯ����λ����ʽ��������1+�ո�+9+�ո�+6\n");
	int a = 0; int b = 0; int c = 0; int d = 0;
	scanf("%d%d%d", &a, &b, &c);
	d = 60 * (a - 1) + 6 * (b - 1) + c - 1;
	if (message[d].a[0] == 'O')
		printf("����λΪ����λ\n");//����λ�Ͳ���ʾ
	else {
		printf("%s%s", message[d].xing, message[d].ming);
	}
}
void preserve(EMU message[300]) {
	FILE* pfile;
	pfile = fopen("message.txt", "w"); int i;//������д���ļ���
	for (int i = 0; i < 300; i++)
	{
		fprintf(pfile, "%s %s %s %s", message[i].a, message[i].arr, message[i].ming, message[i].xing);
	}
	fclose(pfile);
	pfile == NULL;//�������޸ĺ��LISTд���ļ���

}