#include"dict.h"

#define _CRT_SECURE_NO_WARNINGS

int displaychoice(){
	int a = 2;
	while (1)
	{
		printf("请选择！\n");
		printf("1->查询单词。0->退出\n");
		scanf_s("%d", &a);
		if (a == 1) {
			printf("请输入;您想查阅的单词\n");
			char word[20] = { 0 };
			gets(word);
			return lookup(word);
		}
		else if (a == 0)
			break;
		else {
			printf("输入错误请重新输入\n");
		}
	}

}
/*Global variable */
struct dictionary* dict;

//int wordsNumber; //number of words

/*definitions of the functions*/
/* Read a file which contains words and their definitions into the array of structures, return the number of words.
If the file does not exist, return 0.
*/
int loadDictionary(char* fileName) {
	FILE* p;
	/*errno_t err = (&p,fileName, "w");*/
	p = fopen(fileName, "r");
	if (p == NULL)
		printf("error\n");
	int i = 0;
	while (!feof(p)) {//读到文件结尾就跳出循环
		fscanf_s(p, "%s%s", &dict[i].word, &dict[i].definition);
		i++;
	}
	return i;;
}
/* look up the word in the dictionary, return the address of the structure if the word is found, return NULL if not found.
*/
struct dictionary* lookup(char* word) {
	int j;
	for (j = 0; j < 1000; j++) {
		if (strcmp(word, dict[j].word) == 0) {
			return &dict[j];//如果能找到该单词就返回它的地址
		}
		else if (j == 999)//如果到了结构体中最后一个单词也找不到，那就代表词典里没这单词
			printf("词典中没有该单词\n");
	}

}
