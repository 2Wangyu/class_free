/*NAME:YU.
* DATE:11-23
* DESCRIPTION:���������в���������Ӧ����
*
*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<ctype.h>

void reverse(char* string);//��������

int main(int argc, int* argv[]) {
	/*printf("%d", argc);*/
	char c=0;
	FILE* fp; char string = { 0 };
	fp = fopen("message.txt", "r");
	if ((fp = fopen("message.txt", "r")) == NULL) {

		printf("error\n");//��ָ��ʹ�ʧ��
		return 0;
	}
	/*fseek(fp, 0, SEEK_END);
	int g = ftell(fp);
	fgets(string, g, fp);
	fseek(fp, 0, SEEK_SET);*/
	if (argc==1) {
		while (1) {
			char c;
			c = fgetc(fp);//�ظ�һ��һ���ַ����
			if (feof(fp))//��������ļ���β������ѭ��
				break;
			putchar(c);
		}
	}

	if (argv[1]== 'u')
	{
	 while (1)
		{
			c = fgetc(fp);
			if (feof(fp))
			{
				break;
			}
			putchar(toupper(c));//����ת��Ϊ��д��ĸ����
		
	}
		
	if (argv[1]== 'l')
	{

		while (1)
		{
			c = fgetc(fp);
			if (feof(fp))
			{
				break;
			}
			putchar(tolower(c));//����ת��ΪСд��ĸ�ĺ���

	}
	if (argv[1] == 'r')
	{
		reverse(string);
		//���û���ĺ���
	}

	return 0;
}
void reverse(char* string) {
	const char s[3] = " ";
	char* token;
	char arr[100][100] = { 0 };
	token = strtok(string, s);
	int i = 0;
	while (token != NULL) {
		token = arr[i][100];
		i++;
	}
	for (; i >= 0; i--) {

		puts(arr[i]);
		if (i != 0) {
			printf(" ");
		}
	}

}




