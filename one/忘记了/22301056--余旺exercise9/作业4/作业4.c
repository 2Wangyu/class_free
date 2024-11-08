/*NAME:YU.
* DATE:22-12-16
* DESCRIPTION:
*/
#include<stdio.h>
#define _CRT_SECURE_NO_WARNINGS
typedef struct node {//构建一个结构类型
    int value;
    struct node* next;
} ListNode;

ListNode* reverseGroup(ListNode* head, int k)//对链接列表进行重新排列
{
    ListNode* a = head;//创建中间变量储存head，以不修改head 的值
    for (; a != NULL; a = a->next)
    {
        if (a->value == k)
            break;//如果可以找到k对应的位置
    }
    if (a == NULL || a == head) 
        return head;//如果找不到对应的位置或k值就是开头的数，就不改变
    //创建中间变量
    ListNode* begin, * middle, * end;
    begin = head, middle = head->next, end = middle->next;
    for (;;)
    {
        middle->next = begin;//依次将后面的数放到前面去
        if (middle == a) 
            break;//找到输入k值对应位置，就跳出循环
        begin = middle;
        middle = end;
        end = end->next;
    }
    head->next = end;//找到head的前一个
    return a;
}

int main()
{
    ListNode list[10];
    printf("请输入您想建立的链接列表的数字，一共五个\n");//向用户请求输入
    list[0].next = NULL;
    for (int i = 4; i >= 0; i--)
    {
        scanf_s("%d", &list[i].value);
        if (i > 0) 
            list[i].next = list + i - 1;
    }
    int k;
    printf("您建立的链接列表: %d->%d->%d->%d->%d\n", list[4].value, list[3].value, list[2].value, list[1].value, list[0].value);//展示链接列表
    puts("请输入一个K值\n");//请求K值输入
    scanf("%d", &k);
    puts("");
    ListNode* head = reverseGroup(&list[4], k);
    printf("修改后的链接列表:%d", head->value);//展示排列后的链接列表
    for (head = head->next; head != NULL; head = head->next)
    {
        printf("->%d", head->value);
    }
    return 0;
}