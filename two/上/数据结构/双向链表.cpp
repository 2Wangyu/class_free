//���е�����
//1,�������˫�� 2.��ͷ����ͷ�� 3��ѭ�����߷�ѭ����
//��õ���ͷ�����ѭ���ģ���ͷ˫��ѭ������
typedef int LTDateType;
struct ListNode
{
	LTDateType data;
	struct ListNode* next;
	struct ListNode* prev;
}
int main() {
	//�ڱ�λͷ�ڵ㣬��Ϊ��ֹ�Ľڵ�
	phead = malloc(sizeof(LTNode));
	phead->next = phead;
	phead->prev =phead ;

	//shaungxiang���ӵı��ʾ��ǲ������Ҳ�����µ����ݣ�
	assert(phead);
	LTNode* tail = phead->prev;
	LTNode* newnode = (LTNode*)malloc(sizeof(LTNode));
	newnode->data = x;
	//phead������NULLҲ��������
	tail->next = newnode;
	newnode->prev = tail;
	newnode->next = phead;
	phead->prev = newnode;


}