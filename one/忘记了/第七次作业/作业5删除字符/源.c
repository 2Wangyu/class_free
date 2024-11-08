///* NAME:YU.
//Date:22-11-9
//Description:从字符串中删除对应的字符*/
//#include<stdio.h>
//#include<string.h>
//
//
//void removeChar(char* string, char ch) {
//	int i; int sz = strlen(string);//获取字符数
//	int j = 0;
//	printf("%d", sz);
//	for (i = 0; i < sz ; i++) {//循环获取每个字符用来判断
//		char tem = string[i];
//		if (tem!= ch) {//只要不是删除字母就存入string内
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
//	printf("请输入一串字符\n");
//	gets(message);//向用户获取
//	printf("请输入要消去的字母\n");
//	zimu = getchar();
//	removeChar(message, zimu);
//	puts(message);
//
//
//	return 0;
//}