/* NAME:YU.
Date:22-11-7
Description:���������ж�*/
#include<stdio.h>
#include<string.h>
void trans(char str[20]) {//��Сд��ת��,����д��ĸȫ��ת��ΪСд��ĸ
	int i;
	for (i = 0; str[i] != '\0'; i++) {
		if (str[i] >= 'A' && str[i] <= 'Z') {
			str[i] = str[i] + 32;//���ּ�32����д��ΪСд
		}
		str[i] = '\0';
	}
}

void space(char str[20]) {//ɾ���ո�
	int i = 0; int j = 0;
	char temp = str[i];//�����м����
	while (temp != '\0') {   //һֱ��ȡchar��ÿһ���ַ�ֱ������
		if (temp >= 'a' && temp <= 'z') {//��Сд��ת�����迼�Ǵ�д��ĸ��������ǿո�ʹ���char��
			str[j] = temp;
			j++;
		}
		i++;
		temp = str[i];//��tem��ȡchar��һ���ַ�
	}
	str[j] = '\0';
}
void copy_str(char str[20], char str1[20]) {//�����鸴��
	int i;
	for (i = 0; str[i] != '\0'; i++)//��ȡֱ������
	{
		str1[i] = str[i];
	}
	str[i] = '\0';
}

void reverse(char str[20], int a) {
	int i = 0; int b = a - 1;
	for (i = 0; i <= b; i++, b--) {//�����ҷֱ��ȡ��ĸ���н����������߶�Ӧ�±���ڵ����ұߣ�˵���������
		char tem = str[i];
		str[i] = str[a];
		str[a] = tem;
	}


}
void compare(char str[20], char str1[20]) {//��� ת��ǰ��һ����֤���ǻ�������

	if (str = str1)
		printf("��������ǻ�������");
	else
		printf("������Ĳ��ǻ�������");

}
int main() {
	char str[20] = { 0 }; char str1[20];
	printf("������һ���ַ���\n");
	gets(str);//���û���ѯ�ַ���
	trans(str);
	space(str);
	copy_str(str, str1);
	int sz = strlen(str);//��ȡstr���ַ���
	reverse(str, sz);
	compare(str, str1);
	return 0;
}