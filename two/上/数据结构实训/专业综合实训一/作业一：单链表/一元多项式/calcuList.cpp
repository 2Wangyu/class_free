#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;

//创建list
typedef struct node{
	int coef;//代表一元多项式的系数
	int exp;    //代表一元多项式的指数
	struct node* next;//节点指向下一个项

}list;

//初始化代表项的每个节点
node* newNode(int a,int b) {
	node* newNode = (node*)malloc(sizeof(struct node));
	newNode->coef = a;
	newNode->exp = b;
	newNode->next = NULL;
	return newNode;

}

list* initList(int num[]) {

	list* headnode = NULL;
	//头节点为其开辟空间，
	headnode = (list*)malloc(sizeof(struct node));

	node* temp=NULL ;
	node* temp_headnode=headnode;
	//作为临时的头节点，进行一元多项式的连接
	//为最后不影响头节点位置,对临时头结点进行操作
	int i = 0;
    for (; num[i] != -858993460; i++) {
		
		}
	//数组有效的长度
	int length = i ;

	for (int j = 1; j <length; j=j+2) {
		//使用尾插法进行操作
		temp = newNode(num[j], num[j+1]);
		temp_headnode->next = temp;
		temp_headnode = temp;

	}
	return headnode;
}


//将两个链表相加
list* addList(list* A, list* B) {

	//首先应该检查A和B的长度，如果只有一个头节点，直接返回另一个就好了
	if (A == nullptr||A->next == NULL)
		return B;
	if (B == nullptr||B->next == NULL)
		return A;
	//当然考虑两个都为空链表，则返回空链表就好了，所以其实不用再次书写
	
	//指向头节点的第一项
	node* headA = A->next;
	node* headB = B->next;

	//和List初始化
	list* sumList = (list*)malloc(sizeof(struct node));
	sumList->next = NULL;

	//同上面一样的道理，利用临时头结点进行链表的加法连接、

	node* tem_headnode = sumList;
	node* temp = NULL;
	//这里依据从大到小的指数排序
	while (headA && headB) {
	
		if (headA->exp < headB->exp) {
			//处理指数不相等的情况，先插入指数大的
			temp = newNode(headB->coef,headB->exp);
			//尾插法
			tem_headnode->next = temp;
			tem_headnode = temp;
	
			//指向下一个
			headB = headB->next;
		}
		else if (headA->exp > headB->exp) {
			//处理指数不相等的情况，先插入指数大的
			temp = newNode(headA->coef, headA->exp);
			//尾插法
			tem_headnode->next = temp;
			tem_headnode = temp;

			//指向下一个
			headA = headA->next;
		
		}
		else {
			//相等的情况系数相加,
			//注意考虑系数之和为0的情况
			if (headA->coef + headB->coef != 0) {
				temp = newNode(headA->coef + headB->coef, headA->exp);
				//尾插法
				tem_headnode->next = temp;
				tem_headnode = temp;
			}
			//指向下一个
			headB = headB->next;
			headA = headA->next;
		}
	}

	//对另一个非空链表进行处理
	if (headA == NULL && headB != NULL)
		tem_headnode->next = headB;
	if (headB == NULL && headA != NULL)
		tem_headnode->next = headA;

	return sumList;
}

//将两个链表相乘
list* multList(list *A,list*B) {
	//首先应该检查A和B的长度，如果只有一个头节点，直接返回该链表代表最后为空链表
	if (A->next == NULL)
		return A;
	if (B->next == NULL)
		return B;
	//当然考虑两个都为空链表，则返回空链表就好了，所以其实不用再次书写


		//指向头节点的第一项
	node* headA = A->next;
	node* headB = B->next;

	//和List初始化
	list* multList = (list*)malloc(sizeof(struct node));
	multList->next = NULL;

	//同上面一样的道理，利用临时头结点进行链表的加法连接、

	node* tem_headnode = multList;
	list* temp[100]{NULL};
	int i = 0;

	while (headA != NULL) {
		//作为B的临时头节点
		node* tem_headB = headB;
		temp[i]= (list*)malloc(sizeof(struct node));
		temp[i]->next = NULL;
		//临时节点，链表数组的
		list* tempnode1 = temp[i];
		while (tem_headB) {
			//两项相乘后的结果
			node * tempnode=newNode(headA->coef * tem_headB->coef, headA->exp + tem_headB->exp);
			
			//给临时链表加节点
			tempnode1->next = tempnode;
			tempnode1=tempnode;

			//代表B的临时节点指向下一个
			tem_headB = tem_headB->next;

		}
		i++;
		headA = headA->next;
	
	}
	//将三个链表全部加起来得出最终的乘机链表
	for (int j = 0; j < i-1; j++) {

		temp[j + 1] = addList(temp[j],temp[j+1]);
	
	}
	multList = temp[i-1];

	return multList;

}

//
void ReadFromFile(string name, int* num) {//从文件读取数据
	int i = 0;
	ifstream file(name);
	while (!file.eof()) {
		file >> num[i++];
		//将读取的数据存到数组中
	}
	file.close();
}
//输出数据到文件当中
void WriteToFile(string name,list * A) {
	int length=0;//记录链表的数据个数
	int num1 = 0;//记录项数
	int num[100];//记录链表的数据内容
	//让A指向首元素地址
	A = A->next;
	while (A) {
		num[length] = A->coef;
		length++;
		num[length] = A->exp;
		length++;
		A = A->next;
		num1++;
	}
	fstream file(name, ios::out);
	//输出数据到文件
	file << num1;
	file << " ";
	for (int i = 0; i < length; i++) {
		file << num[i];
		file << " ";
	}
	file.close();
	return;
}

int main() {

	int list2[100] ;
	int list1[100] ;

	ReadFromFile("list1.txt", list1);
	ReadFromFile("list2.txt", list2);
	
	/*for (int i = 0; i < sizeof(list2) / sizeof(list2[0]); i++) {
		cout << list2[i] << ",";
	}*/

	list *B1 = initList(list2);
	list *A1 = initList(list1);

	//测试
	//list *temA = A1;
	//list* temB = B1;
	/*while (temA) {
		cout << temA->coef << ","<<temA->exp<<",";
		temA= temA->next;
	}*/
	/*while (temB) {
		cout << "/n";
		cout << temB->coef << "," << temB->exp << ",";
		temB = temB->next;
	}*/

	list* List1 = addList(A1,B1);
	WriteToFile("AddList.txt",List1);

	list* List2 = multList(A1, B1);
	WriteToFile("MultipleList.txt", List2);








}