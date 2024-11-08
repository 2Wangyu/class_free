//所有的链表
//1,单向或者双向 2.带头不带头的 3。循环或者非循环的
//最常用的无头单向非循环的，带头双向循环链表
typedef int LTDateType;
struct ListNode
{
	LTDateType data;
	struct ListNode* next;
	struct ListNode* prev;
}
int main() {
	//哨兵位头节点，作为终止的节点
	phead = malloc(sizeof(LTNode));
	phead->next = phead;
	phead->prev =phead ;

	//shaungxiang连接的本质就是不断在右侧插入新的数据，
	assert(phead);
	LTNode* tail = phead->prev;
	LTNode* newnode = (LTNode*)malloc(sizeof(LTNode));
	newnode->data = x;
	//phead，包括NULL也可以适用
	tail->next = newnode;
	newnode->prev = tail;
	newnode->next = phead;
	phead->prev = newnode;


}