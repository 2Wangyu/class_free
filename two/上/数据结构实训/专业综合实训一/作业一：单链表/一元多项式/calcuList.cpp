#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;

//����list
typedef struct node{
	int coef;//����һԪ����ʽ��ϵ��
	int exp;    //����һԪ����ʽ��ָ��
	struct node* next;//�ڵ�ָ����һ����

}list;

//��ʼ���������ÿ���ڵ�
node* newNode(int a,int b) {
	node* newNode = (node*)malloc(sizeof(struct node));
	newNode->coef = a;
	newNode->exp = b;
	newNode->next = NULL;
	return newNode;

}

list* initList(int num[]) {

	list* headnode = NULL;
	//ͷ�ڵ�Ϊ�俪�ٿռ䣬
	headnode = (list*)malloc(sizeof(struct node));

	node* temp=NULL ;
	node* temp_headnode=headnode;
	//��Ϊ��ʱ��ͷ�ڵ㣬����һԪ����ʽ������
	//Ϊ���Ӱ��ͷ�ڵ�λ��,����ʱͷ�����в���
	int i = 0;
    for (; num[i] != -858993460; i++) {
		
		}
	//������Ч�ĳ���
	int length = i ;

	for (int j = 1; j <length; j=j+2) {
		//ʹ��β�巨���в���
		temp = newNode(num[j], num[j+1]);
		temp_headnode->next = temp;
		temp_headnode = temp;

	}
	return headnode;
}


//�������������
list* addList(list* A, list* B) {

	//����Ӧ�ü��A��B�ĳ��ȣ����ֻ��һ��ͷ�ڵ㣬ֱ�ӷ�����һ���ͺ���
	if (A == nullptr||A->next == NULL)
		return B;
	if (B == nullptr||B->next == NULL)
		return A;
	//��Ȼ����������Ϊ�������򷵻ؿ�����ͺ��ˣ�������ʵ�����ٴ���д
	
	//ָ��ͷ�ڵ�ĵ�һ��
	node* headA = A->next;
	node* headB = B->next;

	//��List��ʼ��
	list* sumList = (list*)malloc(sizeof(struct node));
	sumList->next = NULL;

	//ͬ����һ���ĵ���������ʱͷ����������ļӷ����ӡ�

	node* tem_headnode = sumList;
	node* temp = NULL;
	//�������ݴӴ�С��ָ������
	while (headA && headB) {
	
		if (headA->exp < headB->exp) {
			//����ָ������ȵ�������Ȳ���ָ�����
			temp = newNode(headB->coef,headB->exp);
			//β�巨
			tem_headnode->next = temp;
			tem_headnode = temp;
	
			//ָ����һ��
			headB = headB->next;
		}
		else if (headA->exp > headB->exp) {
			//����ָ������ȵ�������Ȳ���ָ�����
			temp = newNode(headA->coef, headA->exp);
			//β�巨
			tem_headnode->next = temp;
			tem_headnode = temp;

			//ָ����һ��
			headA = headA->next;
		
		}
		else {
			//��ȵ����ϵ�����,
			//ע�⿼��ϵ��֮��Ϊ0�����
			if (headA->coef + headB->coef != 0) {
				temp = newNode(headA->coef + headB->coef, headA->exp);
				//β�巨
				tem_headnode->next = temp;
				tem_headnode = temp;
			}
			//ָ����һ��
			headB = headB->next;
			headA = headA->next;
		}
	}

	//����һ���ǿ�������д���
	if (headA == NULL && headB != NULL)
		tem_headnode->next = headB;
	if (headB == NULL && headA != NULL)
		tem_headnode->next = headA;

	return sumList;
}

//�������������
list* multList(list *A,list*B) {
	//����Ӧ�ü��A��B�ĳ��ȣ����ֻ��һ��ͷ�ڵ㣬ֱ�ӷ��ظ�����������Ϊ������
	if (A->next == NULL)
		return A;
	if (B->next == NULL)
		return B;
	//��Ȼ����������Ϊ�������򷵻ؿ�����ͺ��ˣ�������ʵ�����ٴ���д


		//ָ��ͷ�ڵ�ĵ�һ��
	node* headA = A->next;
	node* headB = B->next;

	//��List��ʼ��
	list* multList = (list*)malloc(sizeof(struct node));
	multList->next = NULL;

	//ͬ����һ���ĵ���������ʱͷ����������ļӷ����ӡ�

	node* tem_headnode = multList;
	list* temp[100]{NULL};
	int i = 0;

	while (headA != NULL) {
		//��ΪB����ʱͷ�ڵ�
		node* tem_headB = headB;
		temp[i]= (list*)malloc(sizeof(struct node));
		temp[i]->next = NULL;
		//��ʱ�ڵ㣬���������
		list* tempnode1 = temp[i];
		while (tem_headB) {
			//������˺�Ľ��
			node * tempnode=newNode(headA->coef * tem_headB->coef, headA->exp + tem_headB->exp);
			
			//����ʱ����ӽڵ�
			tempnode1->next = tempnode;
			tempnode1=tempnode;

			//����B����ʱ�ڵ�ָ����һ��
			tem_headB = tem_headB->next;

		}
		i++;
		headA = headA->next;
	
	}
	//����������ȫ���������ó����յĳ˻�����
	for (int j = 0; j < i-1; j++) {

		temp[j + 1] = addList(temp[j],temp[j+1]);
	
	}
	multList = temp[i-1];

	return multList;

}

//
void ReadFromFile(string name, int* num) {//���ļ���ȡ����
	int i = 0;
	ifstream file(name);
	while (!file.eof()) {
		file >> num[i++];
		//����ȡ�����ݴ浽������
	}
	file.close();
}
//������ݵ��ļ�����
void WriteToFile(string name,list * A) {
	int length=0;//��¼��������ݸ���
	int num1 = 0;//��¼����
	int num[100];//��¼�������������
	//��Aָ����Ԫ�ص�ַ
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
	//������ݵ��ļ�
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

	//����
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