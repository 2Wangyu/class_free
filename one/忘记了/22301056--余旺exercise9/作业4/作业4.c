/*NAME:YU.
* DATE:22-12-16
* DESCRIPTION:
*/
#include<stdio.h>
#define _CRT_SECURE_NO_WARNINGS
typedef struct node {//����һ���ṹ����
    int value;
    struct node* next;
} ListNode;

ListNode* reverseGroup(ListNode* head, int k)//�������б������������
{
    ListNode* a = head;//�����м��������head���Բ��޸�head ��ֵ
    for (; a != NULL; a = a->next)
    {
        if (a->value == k)
            break;//��������ҵ�k��Ӧ��λ��
    }
    if (a == NULL || a == head) 
        return head;//����Ҳ�����Ӧ��λ�û�kֵ���ǿ�ͷ�������Ͳ��ı�
    //�����м����
    ListNode* begin, * middle, * end;
    begin = head, middle = head->next, end = middle->next;
    for (;;)
    {
        middle->next = begin;//���ν���������ŵ�ǰ��ȥ
        if (middle == a) 
            break;//�ҵ�����kֵ��Ӧλ�ã�������ѭ��
        begin = middle;
        middle = end;
        end = end->next;
    }
    head->next = end;//�ҵ�head��ǰһ��
    return a;
}

int main()
{
    ListNode list[10];
    printf("���������뽨���������б�����֣�һ�����\n");//���û���������
    list[0].next = NULL;
    for (int i = 4; i >= 0; i--)
    {
        scanf_s("%d", &list[i].value);
        if (i > 0) 
            list[i].next = list + i - 1;
    }
    int k;
    printf("�������������б�: %d->%d->%d->%d->%d\n", list[4].value, list[3].value, list[2].value, list[1].value, list[0].value);//չʾ�����б�
    puts("������һ��Kֵ\n");//����Kֵ����
    scanf("%d", &k);
    puts("");
    ListNode* head = reverseGroup(&list[4], k);
    printf("�޸ĺ�������б�:%d", head->value);//չʾ���к�������б�
    for (head = head->next; head != NULL; head = head->next)
    {
        printf("->%d", head->value);
    }
    return 0;
}