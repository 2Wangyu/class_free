#include"dict.h"

#define _CRT_SECURE_NO_WARNINGS

int displaychoice(){
	int a = 2;
	while (1)
	{
		printf("��ѡ��\n");
		printf("1->��ѯ���ʡ�0->�˳�\n");
		scanf_s("%d", &a);
		if (a == 1) {
			printf("������;������ĵĵ���\n");
			char word[20] = { 0 };
			gets(word);
			return lookup(word);
		}
		else if (a == 0)
			break;
		else {
			printf("�����������������\n");
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
	while (!feof(p)) {//�����ļ���β������ѭ��
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
			return &dict[j];//������ҵ��õ��ʾͷ������ĵ�ַ
		}
		else if (j == 999)//������˽ṹ�������һ������Ҳ�Ҳ������Ǿʹ���ʵ���û�ⵥ��
			printf("�ʵ���û�иõ���\n");
	}

}
