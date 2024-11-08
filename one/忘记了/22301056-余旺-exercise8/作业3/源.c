/*NAME:YU.
* DATE:11-23
* DESCRIPTION:利用命令行参数进行相应处理
*
*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<ctype.h>

void reverse(char* string);//声明函数

int main(int argc, int* argv[]) {
	/*printf("%d", argc);*/
	char c=0;
	FILE* fp; char string = { 0 };
	fp = fopen("message.txt", "r");
	if ((fp = fopen("message.txt", "r")) == NULL) {

		printf("error\n");//空指针就打开失败
		return 0;
	}
	/*fseek(fp, 0, SEEK_END);
	int g = ftell(fp);
	fgets(string, g, fp);
	fseek(fp, 0, SEEK_SET);*/
	if (argc==1) {
		while (1) {
			char c;
			c = fgetc(fp);//重复一个一个字符输出
			if (feof(fp))//如果读到文件结尾就跳出循环
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
			putchar(toupper(c));//调用转化为大写字母函数
		
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
			putchar(tolower(c));//调用转化为小写字母的函数

	}
	if (argv[1] == 'r')
	{
		reverse(string);
		//调用换序的函数
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




