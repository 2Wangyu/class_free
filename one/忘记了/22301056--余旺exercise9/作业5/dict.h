#include<stdio.h>
#include <stdlib.h>
#include<string.h>

int displaychoice();

/* data structure for the dictionary */
struct dictionary {

	char word[50];//分别代表单词和定义
	char definition[200];

};

/*Global variable declaration*/
extern struct dictionary* dict;

extern int wordsNumber;

/* Function prototype declarations */

int loadDictionary(char* fileName);

struct dictionary* lookup(char* word);
