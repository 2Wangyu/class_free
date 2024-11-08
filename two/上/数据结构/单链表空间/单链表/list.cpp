#include<iostream>

struct slink {
	int data;
	struct slink *next;
};
slink* newNode(int a) {
     slink *node= (slink*)malloc(sizeof(struct slink));
	 node->data = a;
	 node->next = NULL;
	 return node;
}

slink* initList( int num[],int i) { 

	struct slink* initList = (slink*)malloc(sizeof(struct slink));
	struct slink* temp = (slink*)malloc(sizeof(struct slink));
	temp = initList;

	for (int j = 0; j < i; j++) {
		struct slink* node = newNode(num[j]);
		temp->next = node;
		temp = node;
	}
	return initList;
}

//升序排序
slink* Sort(slink *head) {
	struct slink* sort = (slink*)malloc(sizeof(struct slink));
    struct slink* slow = (slink*)malloc(sizeof(struct slink));
    struct slink* fast = (slink*)malloc(sizeof(struct slink));
    if (head == NULL || head->next == NULL) 
        return head;
    slow = head;
    fast = head->next;
    //快慢指针来分割链表
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    struct slink* midR = (slink*)malloc(sizeof(struct slink));
    midR = slow->next;
    slow->next = NULL;//将中间结点置空是下次递归 return 的必要条件
    struct slink* left = (slink*)malloc(sizeof(struct slink));
    struct slink* right = (slink*)malloc(sizeof(struct slink));
    left = Sort(head);
    right = Sort(midR);
    //合并
    
    struct slink* prev = (slink*)malloc(sizeof(struct slink));
    struct slink* newHead = (slink*)malloc(sizeof(struct slink));
    
    prev = newHead;;
    while (left != NULL && right != NULL) {
        if (left->data <= right->data) {
            prev->next = left;
            left = left->next;
        }
        else {
            prev->next = right;
            right = right->next;
        }
        prev = prev->next;

    }
    //走到这里，两个有序序列，一个为空，一个不为空，把不为空的接在prev的后面
    prev->next = (left != NULL ? left : right);
    return newHead->next;


}
slink *Union(slink* la1, slink* lb1, slink* lc) {
    struct slink* la = (slink*)malloc(sizeof(struct slink));
    struct slink* lb = (slink*)malloc(sizeof(struct slink));
    la = la1;
    lb =lb1;

    la = la->next;
    lb = lb->next;
    //临时节点用来进行Lc的并集
    struct slink* temp = (slink*)malloc(sizeof(struct slink));
    temp = lc;
  

    while (la && lb) {
        if (la->data == lb->data) {
            struct slink* node = newNode(la->data);
            temp->next = node;
            temp = node;
            la = la->next;
            lb = lb->next;
        }
        else if (la->data < lb->data) {
            struct slink* node = newNode(la->data);
            temp->next = node;
            temp = node;
            la = la->next;
        }
        else {
            struct slink* node = newNode(lb->data);
            temp->next = node;
            temp = node;
            lb = lb->next;
        }
    }
        if (la)
            temp->next = la;
        if(lb)
            temp->next = lb;
    
    return lc;
}

slink* Mix(slink* la1, slink* lb1, slink* lc) {
    struct slink* la = (slink*)malloc(sizeof(struct slink));
    struct slink* lb = (slink*)malloc(sizeof(struct slink));
    la = la1;
    lb = lb1;

    la = la->next;
    lb = lb->next;
    //临时节点用来进行Lc的交集
    struct slink* temp = (slink*)malloc(sizeof(struct slink));
    temp = lc;
    while (la && lb) {
        if (la->data == lb->data) {
            struct slink* node = newNode(la->data);
            temp->next = node;
            temp = node;
            la = la->next;
            lb = lb->next;
        }
        //如果不相等，则小的那个抛出，不用节点
        else if (la->data < lb->data) {
           /* struct slink* node = newNode(la->data);
            temp->next = node;
            temp = node;*/

            la = la->next;
        }
        else {
            /*struct slink* node = newNode(lb->data);
            temp->next = node;
            temp = node;*/
            lb = lb->next;
        }
    }
    
    return lc;
}
//作差运算，作A-B运算，若B中有和A相同的则减去
slink* Elim(slink* la1, slink* lb1, slink* lc) {
    struct slink* la = (slink*)malloc(sizeof(struct slink));
    struct slink* lb = (slink*)malloc(sizeof(struct slink));
    la = la1;
    lb = lb1;

    la = la->next;
    lb = lb->next;
    //临时节点用来进行Lc的交集
    struct slink* temp = (slink*)malloc(sizeof(struct slink));
    temp = lc;
    while (la && lb) {
        if (la->data == lb->data) {
            //相等不放入链表中
            la = la->next;
            lb = lb->next;
        }
        //如果la节点较小，则lb中一定没有和la相等的链表
        else if (la->data < lb->data) {
             struct slink* node = newNode(la->data);
             temp->next = node;
             temp = node;
            la = la->next;
        }
        else {
            //lb小则找到下一个节点，下一个节点可能有la的元素
            lb = lb->next;
        }
    }
    //若la中还有元素则放入
    if (la)
        temp->next = la;

    return lc;
}


int main() {

	struct slink* A = (slink*)malloc(sizeof(struct slink));
	struct slink* B = (slink*)malloc(sizeof(struct slink));
	int numA[5] = { 7,3,6,4 ,5};
	int a = sizeof(numA) / sizeof(int);
   
	int numB[5] = { 1,3,5,7,2 };
	int b= sizeof(numB) / sizeof(int);

	slink*  initA= initList(numA,a);
	slink* initB = initList(numB,b);

	slink* sortA = Sort(initA);

	slink* sortB = Sort(initB);


    struct slink* unionList = (slink*)malloc(sizeof(struct slink));
    unionList=Union(sortA, sortB, unionList);

    struct slink*   mixList= (slink*)malloc(sizeof(struct slink));
    mixList = Mix(sortA,sortB,mixList);

   /* struct slink* elimList = (slink*)malloc(sizeof(struct slink));
    elimList = Elim(sortA, sortB, mixList);*/

    
    int c = 0;
}