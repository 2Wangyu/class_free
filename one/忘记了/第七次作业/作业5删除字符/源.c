///* NAME:YU.
//Date:22-11-9
//Description:���ַ�����ɾ����Ӧ���ַ�*/
//#include<stdio.h>
//#include<string.h>
//
//
//void removeChar(char* string, char ch) {
//	int i; int sz = strlen(string);//��ȡ�ַ���
//	int j = 0;
//	printf("%d", sz);
//	for (i = 0; i < sz ; i++) {//ѭ����ȡÿ���ַ������ж�
//		char tem = string[i];
//		if (tem!= ch) {//ֻҪ����ɾ����ĸ�ʹ���string��
//			string[j] = tem;
//			j++;
//		}
//	}
//	string[j] = '\0';
//
//}
//
//int main() {
//	char message[50] ; char zimu;
//	printf("������һ���ַ�\n");
//	gets(message);//���û���ȡ
//	printf("������Ҫ��ȥ����ĸ\n");
//	zimu = getchar();
//	removeChar(message, zimu);
//	puts(message);
//
//
//	return 0;
//}