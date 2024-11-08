/*NAME:YU.
* DATE:22-12-16
* DESCRIPTION:A dictionary for search
*/
#include<stdio.h>
#include"dict.h"
#define _CRT_SECURE_NO_WARNINGS

int main() {
	
	/* data structure for the dictionary
assume less than 1000 words in the dictionary
*/
	struct dictionary myDict[1000];
	/* File name*/
	char* fileName = "dictionary.txt";
		/* initialize the global variable*/
		dict = myDict;
	/* read from file, get the dictionary*/
	int wordsNumber = loadDictionary(fileName);
	printf("一共有%d个单词\n",wordsNumber);
	displaychoice();//给用户提供选项，并试图查找单词 


	return 0;
}