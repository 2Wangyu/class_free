//������˳���
//1.�ռ䲻������Ҫ���ݣ�������Ҫ�������۵�
//2.����Ƶ�����ݣ��������˻�����������2�������ܵ���һ���Ŀռ��˷�
//3.Ҫ�����ݴӿ�ʼλ�������洢�����Ǵ�ͷ�����м�λ�ò���ɾ�����ݣ�����ҪŲ�����ݣ�Ч�ʵ�
// �������Ǵ�������
// ȱ�㣺1�������������                                 �ŵ㣺1������Ҫ����ռ䣬�㲻�þ��ͷ�
//            2.ÿһ�����ݶ�Ҫ��һ��ָ��                        2.�Ϳ���������λ�ò��룬�Ҳ���ҪŲ������
//                                                              3.�����ڿռ���˷�
struct DATE {
    int date;
    struct DATE* next;

};
int main() {
    struct DATE* head = next;
    while (head != NULL) {
        printf("", head->);
        head = head->next;
        //�����ṹ������ݣ���ӡ�ṹ��
    }
    //��β����ӽڵ�
    Pushback(struct DATE* head)
        //ע�⣬��ֵ�ʹ�ַ������
        //��ȷ�� (&struct DATE*head)
        Pushfront(&struct DATE* head);
}
void Pushback(srtuct DATE** head) {
    if (*head == NULL) {
        *head = newcode;
    }
    while (head->next != NULL) {
        head = head->next;
    }//�ҵ�β���
    //�����µĽڵ�
    struct DATE* newnode = (struct DATE*)malloc(sizeof(struct DATE));
    newnode->data = 6;
    newnode->next = NULL;

}
void Pushfront(struct DATE** head) {
    struct DATE* newnode;
    newnode->data = 5;
    newnode->next = *head;
    *head = newnode;
    //������newnode->nextָ��ͷ�ĵ�ַ
    //Ȼ��ı俪ͷ�ĵ�ַΪnewnode,�´η���head���Ƿ���newnode��ʼ�������
    //������β�����룬�����ʱheadΪnullҲû������
}
void Popback(struct DATE** head) {
    //�������
    if��* head == NULL){
    return;
}
//assert(*head!=NULL);

//ֻ��һ��
if (*head->next == NULL) {
    free(*head);
    *head = NULL;
}

    //�������ϵ�
    struct DATE* tail = *head;
    struct DATE* prevail;
else {
    while (tail->next) {
        prevail = tail;
        tail = tail->next;//�ҵ���β֮ǰ�Ľڵ㣬����Ҫɾ���Ľڵ�

    }
    //�����
    free(tail);
    tail = NULL;//tail�ڴ����ݱ��ͷ��ˣ�����->next��Ȼָ��õ�ַ�������ͷź�ֻ�������ֵ
    //��ȷ��
    free(tail);
    tail = NULL;
    prevail->next = NULL;

    //������
    while (tail->next->next) {
        tail = tail->next;
    }
    free(tail);
    tail->next = NULL;
    tail = NULL;//����Ҫ˫ָ��
}
    //����һ�����⣬�������ֻ��һ���������
}
//
//��pos֮ǰȥ����

void SListInsert(SLTNode** pphead, SLTNode* pos)
{
    SLTNode* posPrev = *pphead;//�ҵ���һ��
    while (posPrev->next != pos) {
        posPrev = posPrev->next;//�ҵ�pos
    }
    posPrev->next = newnode;//newnodeΪ��Ҫ���������
    newnode->next = pos;
}
// 
//pos����ȥ����
//
{
    //һ��ϸ�ڣ����ҵ���һ��������ǰһ��������
    //��Ϊ��֮��Pos->next���Ҳ��������Ӳ�����һ����
   //������һ��ָ��ȥ������
    newnode->next = pos->next;
    pos->next = newnode;
}

//ɾ��pos
{//ppheadΪ��ͷ
    if (*pphead == pos) {
        *pphead == pos->next;
        free(pos);
    }
    else {
        SLTNode* prev = *pphead;
        while (prev->next != pos) {
            prev = prev->next;
        }
        prev->next = pos->next;//����posָ��Pos����һ��
        free(pos);
        pos = NULL;//�����ÿ���û��ʲô����ģ���Ϊpos�������βΣ���������Ҳ�ᱻ�ÿ�
    }
}//ɾ��
{
    assert(pphead);
    SLTNode* cur = *pphead;
    while (cur) {
        /*SLTNode* next = cur->next;*/
        free(cur);
        /*cur = cur->next;*/
    }//���û��ע�͵����У��޷�ɾ��ȫ����Ϊ��cur->nextû���ͷ�
    *pphead == NULL;
}

//��ת����˫ָ��
//������prev��next,cur:֮ǰ������,���ڵ�
{
    if (*pphead == NULL)
        return *pphead;
    SLTNode* prev = NULL;
    SLTNode* cur = *pphead;
    SLTNode* next = cur->next;
    while (cur != NULL) {
        cur->next = prev;//��ת
        prev = cur;//������
        cur = next;
        if(next)//������һ��Ŷ�
        next = next->next;//����Ϊ��
        
    }
    return prev;//���һ���ƶ�����curΪnull����prev����ͷ��
}
//������
{
    SLTNode* cur = *pphead;
    SLTNode* newhead = NULL;
    cur->next = NULL;
    while (cur) {
        SLTNode* next = cur->next;
        //ͷ��
        cur->next = newhead;
        newhead = cur;
        //����������
        cur = next;
        if(next)
        next = next->next;
    }
}

//�ҵ��м�Ľڵ�
{
    SLTNode* slow = *pphead;
    SLTNode* fast = *pphead;//�ҵ���ͷ
    while (fast == NULL || fast->next == NULL) {
        slow = slow->next;
        fast = fast->next->next;//slowһ����һ��,fastһ��������
    }
    return slow;
}

//�����е�����K���ڵ�
{
    //����k����fastΪNULL��slow���ǵ�����k��

    SLTNode* slow = *head;
    SLTNode* fast = *head;
    while (k--) {
        if (fast == NULL)
        {
            return NULL;
        }
     //�����--k����ô�������fast->next!=NULL
        fast = fast->next;
    }
    while (fast) {
        fast = fast->next;
        slow = slow->next;
    }
    return slow;
}
//�������б�ϲ���һ��������б�
{
    struct LISTNode* head = NULL,*tail=NULL;//�µ������ͷ��β
    while(l1&&l2��//ѭ��������ȥ��������l1��l2��Ϊ��
        {
            if (l1->val > l2->val) {
                if (head == NULL) {
                    head = tail = l2;//����ͷ��Ϊ��returnʱ�ҵ�ͷ�ڵ�
                }
                else {
                    tail->next = l2;
                    tail = l2;
                }
                                    }


            else {
                       if (head == NULL) {
                     head = tail = l1;//����ͷ��Ϊ��returnʱ�ҵ�ͷ�ڵ�
               }
                       else {
                       tail->next = l1;
                       tail = l1;
               }

                 }

        }
}
//��ͷ����ͷ����һ���ڱ�λ��ͷ��㣬����ڵ㲻�洢��Ч����
head = tail = malloc(sizeof(LISTNode));
//Ȼ��������Ĳ��䣬��ע���ͷŵ�����
LISTNode* tem = head;
free(head);
head = NULL;

//�ָ������ұ�����Ե�˳��,��һ������x��Ϊ�ָ��Ľڵ�,С��ǰ�棬��ĺ���
{
    SLTNode* lesshead, * lesstail, * greaterhead, * greatertail;
    lesstail->next = NULL;
    greatertail->next = NULL;
    lesstail = lesshead = greaterhead = greatertail = (struct SLTNode*)malloc(sizeof(struct SLTNode);
    while (*head) {
        if (*head->val > x) {
            greatertail->next = *head;
            greatertail = *head;
        }

        else {
            lesstail->next = *head;
            lesstail = *head;
        }
        *head = *head->next;
    }
    if (greaterhead && lesshead) {
        lesstail->next = greaterhead->next;//β����ͷ���໥����
    }
     //�ؼ�����
    greatertail->next = NULL;
    //����:7 13 4 15 6(10)  �����7-4-6-13-15-6-13-15-6����������ѭ��
    struct SLTNode* newhead = lesshead->next;
    free(lesshead);
    free(greaterhead);
    return newhead;

 }

//����һ�������ж��Ƿ���������
{
    //����һ����һ��������������е�ÿһ����ֵ��Ȼ����������ȥ�Ƚ�

    //�����������������ٱȽ�

    //���������ҵ��м�ڵ㣬�������ã��Ƚ�ǰ��κͺ���
    //��ע��ϸ�ڣ���������������ż����
    //��������������⣺����˼·��һ����������βNULL�Ͳ��ٽ��бȽ�
    //                            ����һ���ѽ�β�ÿռ��������NULL

    struct LISTNode* mid = middleNode(*head);
    *rhead = tailNode(*mid);
    while (mid && rhead) {
        if (mid->val != rhead->val)
        {
            return false;
        }
        else {
            mid = mid->next;
            rhead = rhead->next;
        }
    }
    //�и�ϸ���ǲ��ùܽ�β�ٴ�ѭ�����Ӿ���������ʾ����Ϊ��ǰ��һ��Ϊ�վ���ֹ��
    return true;
}

//�ҵ����������ཻ�Ľڵ㣬���ཻ�����ؿ�
{
    //һ��ȥA�е�ÿ���ڵ��B�����нڵ�Ƚϣ�����е�ַ��ͬ�Ľڵ㣬�����ཻ��Ϊ��һ����ͬ�Ľڵ�
    //o(N*N)
    //����1��β�����ͬ�����ཻ��������ǲ��ཻ
    //    2���󽻵㣺�����������ߣ���ͬʱ�ߣ���һ�����ǽ�ڵ�
    struct ListNode* tailA = headA;
    int lenA, lenB = 1;
    while (tailA->next)
    {
        tailA = tailA->next;
        lenA++;
    }
    while (tailB->next)
    {
        tailB = tailB->next;
        lenB++;
    }
    //���ཻ
    if (tailA != tailB) {
        return NULL;
    }
    int gap = abs(lenA - lenB);
    //�������߲�ಽ������ͬʱ���ҽ���
    struct ListNode* longlist =headA ;
    struct ListNode* shortlist = headB;
    if (lenA < lenB) {
        shortlist = headA;
        longlist = headB;
    }
    while (gap--) {
        longlist = longlist->next;
    }
    while (longlist != shortlist) {
        longlist = longlist->next;
        shortlist = shortlist->next;
    }
    return longlist;
}

//��������
{
    //�ж��Ƿ��л�
    struct ListNode* slow = head, * fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            struct ListNode* meet = slow;
            fast = head;
            while (fast != slow) {
                fast = fast->next;
                slow = slow->next;
            }
            return slow;
        }
    }
    return false;
}
//�������⣺1��һ�����ڻ�����������ôŪ֤��
 //         2��һ���ߴ���2�����Ͳ�һ��һ����n��
{//��ͷ�ϣ����Ǵ�׷�����⣬������һ��׷һ����λ�ľ���
   // ��3,3����׷���ǵĻ�Ҫ�ͻ��ĳ��ȱȽϣ������-1��-2��3�ı���
//�ҵ�������ʼλ�ã�һ����ͷ�ߣ�һ���������ĵط���ʼ��
    //������׷�ϵĹ����У���ָ����L+x,��ָ����L+X+n*C
    //2��L+X��=L+N*C+X,L=(n-1)*c+c-x,L�Ǿ��뻷��ͷ�ĳ���
    //��ôһ���ӿ�ͷһ����meet��ʼ��һ�����ڻ�ͷ����x+L=n*c
    //L�ǻ���ͷ�ľ��룬cΪ���ĳ��ȣ�������һ�����ڻ��ϵ�x

    //���������⿪meet�ĵ㣬Ȼ��Ӵ˴���ʼ�ߣ�head���ҵ��ཻ�ĵ�

}
//���ƴ����ָ�������
//������˽ڵ�ָ����һ����������������һ������random����ָ������ǰ��������ͷ��λ
{
    //���ƽڵ㣬���뵽ԭ�ڵ����һ��֮��
    //ָ���Ƶ�random
    //�Ѹ��ƵĽڵ�������� ���������ظ�ԭ����
    struct Node* cur = head;
    while (cur)
    {
        sturct Node* copy = (struct Node*)malloc(sizeof(struct Node));
        copy->val = cur->val;
//���븴�Ƶ�����
        copy->next = cur->next;
        cur->next = copy;
        cur = copy->next;
        //�����Ľڵ����ԭ�ڵ���棬�ȿ����ĺ�ָ����ǰ�����ӣ��ڸı�cur��
    }
    //2������ԭ�ڵ㣬����copy�ڵ��random
    cur = head;
    while (cur) {
        struct Node* copy = cur->next;
        if (cur->random == NULL)
        {
            copy->random = NULL;
        }
        else {
            copy->random =cur->random->next ;
        }
        cur = copy->next;
    }
    //���е�������
    sturct Node* copyhead, *copytail;
    cur = head;
    while (cur) {
        struct Node* copy = cur->next;
        sturct Node* next = copy->next;
        if (copyTail == NULL) {
            copyhead = copytail = copy;
        }
        else {
            copyTail->next = copy;
            copyTail = copy;
        }
        cur->next = next;
        cur = next;
    }
    //����ͷ�ڵ�
    return copyHead;
}











