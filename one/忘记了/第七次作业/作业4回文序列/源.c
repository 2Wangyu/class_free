/* NAME:YU.
Date:22-11-7
Description:回文序列判断*/
#include<stdio.h>
#include<string.h>
void trans(char str[20]) {//大小写的转换,将大写字母全部转换为小写字母
	int i;
	for (i = 0; str[i] != '\0'; i++) {
		if (str[i] >= 'A' && str[i] <= 'Z') {
			str[i] = str[i] + 32;//数字加32，大写变为小写
		}
		str[i] = '\0';
	}
}

void space(char str[20]) {//删除空格
	int i = 0; int j = 0;
	char temp = str[i];//创建中间变量
	while (temp != '\0') {   //一直获取char的每一个字符直到结束
		if (temp >= 'a' && temp <= 'z') {//大小写的转化后不需考虑大写字母，如果不是空格就存入char内
			str[j] = temp;
			j++;
		}
		i++;
		temp = str[i];//用tem获取char下一个字符
	}
	str[j] = '\0';
}
void copy_str(char str[20], char str1[20]) {//将数组复制
	int i;
	for (i = 0; str[i] != '\0'; i++)//获取直到结束
	{
		str1[i] = str[i];
	}
	str[i] = '\0';
}

void reverse(char str[20], int a) {
	int i = 0; int b = a - 1;
	for (i = 0; i <= b; i++, b--) {//从左右分别获取字母进行交换，如果左边对应下标大于等于右边，说明交换完成
		char tem = str[i];
		str[i] = str[a];
		str[a] = tem;
	}


}
void compare(char str[20], char str1[20]) {//如果 转换前后一致则证明是回文序列

	if (str = str1)
		printf("您输入的是回文序列");
	else
		printf("您输入的不是回文序列");

}
int main() {
	char str[20] = { 0 }; char str1[20];
	printf("请输入一串字符串\n");
	gets(str);//向用户征询字符串
	trans(str);
	space(str);
	copy_str(str, str1);
	int sz = strlen(str);//获取str内字符数
	reverse(str, sz);
	compare(str, str1);
	return 0;
}