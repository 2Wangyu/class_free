//区别于顺序表：
//1.空间不够了需要增容，增容是要付出代价的
//2.避免频繁扩容，我们满了基本都是扩容2倍，可能导致一定的空间浪费
//3.要求数据从开始位置连续存储，我们从头部或中间位置插入删除数据，就需要挪动数据，效率低
// 所以我们带来链表
// 缺点：1，不能随机访问                                 优点：1按照需要申请空间，你不用就释放
//            2.每一个数据都要存一个指针                        2.就可以在任意位置插入，且不需要挪动数据
//                                                              3.不存在空间的浪费
struct DATE {
    int date;
    struct DATE* next;

};
int main() {
    struct DATE* head = next;
    while (head != NULL) {
        printf("", head->);
        head = head->next;
        //遍历结构体的内容，打印结构体
    }
    //在尾部添加节点
    Pushback(struct DATE* head)
        //注意，传值和传址的区别
        //正确的 (&struct DATE*head)
        Pushfront(&struct DATE* head);
}
void Pushback(srtuct DATE** head) {
    if (*head == NULL) {
        *head = newcode;
    }
    while (head->next != NULL) {
        head = head->next;
    }//找到尾结点
    //创建新的节点
    struct DATE* newnode = (struct DATE*)malloc(sizeof(struct DATE));
    newnode->data = 6;
    newnode->next = NULL;

}
void Pushfront(struct DATE** head) {
    struct DATE* newnode;
    newnode->data = 5;
    newnode->next = *head;
    *head = newnode;
    //创建了newnode->next指向开头的地址
    //然后改变开头的地址为newnode,下次访问head即是访问newnode开始往后访问
    //区别于尾部插入，这个计时head为null也没有问题
}
void Popback(struct DATE** head) {
    //解决方案
    if（* head == NULL){
    return;
}
//assert(*head!=NULL);

//只有一个
if (*head->next == NULL) {
    free(*head);
    *head = NULL;
}

    //两个以上的
    struct DATE* tail = *head;
    struct DATE* prevail;
else {
    while (tail->next) {
        prevail = tail;
        tail = tail->next;//找到结尾之前的节点，即是要删除的节点

    }
    //错误的
    free(tail);
    tail = NULL;//tail内存内容被释放了，但是->next仍然指向该地址，而被释放后只会是随机值
    //正确的
    free(tail);
    tail = NULL;
    prevail->next = NULL;

    //方法二
    while (tail->next->next) {
        tail = tail->next;
    }
    free(tail);
    tail->next = NULL;
    tail = NULL;//不需要双指针
}
    //面临一个问题，就是如果只有一个，会崩溃
}
//
//在pos之前去插入

void SListInsert(SLTNode** pphead, SLTNode* pos)
{
    SLTNode* posPrev = *pphead;//找到第一个
    while (posPrev->next != pos) {
        posPrev = posPrev->next;//找到pos
    }
    posPrev->next = newnode;//newnode为需要插入的内容
    newnode->next = pos;
}
// 
//pos后面去插入
//
{
    //一个细节，先找到下一个，再找前一个链接上
    //因为反之，Pos->next就找不到，链接不到下一个了
   //或者用一个指针去存起来
    newnode->next = pos->next;
    pos->next = newnode;
}

//删除pos
{//pphead为开头
    if (*pphead == pos) {
        *pphead == pos->next;
        free(pos);
    }
    else {
        SLTNode* prev = *pphead;
        while (prev->next != pos) {
            prev = prev->next;
        }
        prev->next = pos->next;//跳过pos指向Pos的下一个
        free(pos);
        pos = NULL;//将他置空是没有什么意义的，因为pos本身是形参，出函数后也会被置空
    }
}//删除
{
    assert(pphead);
    SLTNode* cur = *pphead;
    while (cur) {
        /*SLTNode* next = cur->next;*/
        free(cur);
        /*cur = cur->next;*/
    }//如果没有注释的两行，无法删除全部因为，cur->next没有释放
    *pphead == NULL;
}

//反转链表，双指针
//命名。prev，next,cur:之前，下面,现在的
{
    if (*pphead == NULL)
        return *pphead;
    SLTNode* prev = NULL;
    SLTNode* cur = *pphead;
    SLTNode* next = cur->next;
    while (cur != NULL) {
        cur->next = prev;//反转
        prev = cur;//迭代走
        cur = next;
        if(next)//加上这一句才对
        next = next->next;//但会为空
        
    }
    return prev;//最后一次移动会让cur为null，而prev就是头了
}
//方法二
{
    SLTNode* cur = *pphead;
    SLTNode* newhead = NULL;
    cur->next = NULL;
    while (cur) {
        SLTNode* next = cur->next;
        //头插
        cur->next = newhead;
        newhead = cur;
        //迭代往后走
        cur = next;
        if(next)
        next = next->next;
    }
}

//找到中间的节点
{
    SLTNode* slow = *pphead;
    SLTNode* fast = *pphead;//找到开头
    while (fast == NULL || fast->next == NULL) {
        slow = slow->next;
        fast = fast->next->next;//slow一次走一个,fast一次走两个
    }
    return slow;
}

//链表中倒数第K个节点
{
    //先走k步，fast为NULL后，slow就是倒数第k个

    SLTNode* slow = *head;
    SLTNode* fast = *head;
    while (k--) {
        if (fast == NULL)
        {
            return NULL;
        }
     //如果是--k，那么下面就是fast->next!=NULL
        fast = fast->next;
    }
    while (fast) {
        fast = fast->next;
        slow = slow->next;
    }
    return slow;
}
//将两个列表合并成一个有序的列表
{
    struct LISTNode* head = NULL,*tail=NULL;//新的链表的头和尾
    while(l1&&l2）//循环进行下去的条件是l1和l2不为空
        {
            if (l1->val > l2->val) {
                if (head == NULL) {
                    head = tail = l2;//命名头是为了return时找到头节点
                }
                else {
                    tail->next = l2;
                    tail = l2;
                }
                                    }


            else {
                       if (head == NULL) {
                     head = tail = l1;//命名头是为了return时找到头节点
               }
                       else {
                       tail->next = l1;
                       tail = l1;
               }

                 }

        }
}
//带头不带头，多一个哨兵位的头结点，这个节点不存储有效数据
head = tail = malloc(sizeof(LISTNode));
//然后接下来的不变，但注意释放的问题
LISTNode* tem = head;
free(head);
head = NULL;

//分隔链表，且保持相对的顺序,以一个数字x作为分隔的节点,小的前面，大的后面
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
        lesstail->next = greaterhead->next;//尾部和头部相互链接
    }
     //关键代码
    greatertail->next = NULL;
    //比如:7 13 4 15 6(10)  排序后：7-4-6-13-15-6-13-15-6接下来会死循环
    struct SLTNode* newhead = lesshead->next;
    free(lesshead);
    free(greaterhead);
    return newhead;

 }

//给定一个链表，判断是否会回文链表
{
    //方案一，找一个数组放入链表中的每一个的值，然后再数组中去比较

    //方案二：逆置序列再比较

    //方案三：找到中间节点，后面逆置，比较前半段和后半段
    //但注意细节，链表有奇数还是偶数个
    //当奇数个会出问题：两种思路，一个是遇到结尾NULL就不再进行比较
    //                            还有一个把结尾置空即多出来的NULL

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
    //有个细节是不用管结尾再次循环链接就如上面所示，因为到前面一个为空就终止了
    return true;
}

//找到两个链表相交的节点，不相交，返回空
{
    //一，去A中的每个节点跟B的所有节点比较，如果有地址相同的节点，就是相交，为第一个相同的节点
    //o(N*N)
    //二，1，尾结点相同就是相交，否则就是不相交
    //    2，求交点：长的链表先走，再同时走，第一个就是姐节点
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
    //不相交
    if (tailA != tailB) {
        return NULL;
    }
    int gap = abs(lenA - lenB);
    //长的先走差距步数，在同时走找交点
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

//环形链表
{
    //判断是否有环
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
//延伸问题：1，一定会在环中相遇，怎么弄证明
 //         2，一次走大于2步，就不一定一次走n步
{//口头上：就是从追击问题，走两步一次追一个单位的距离
   // ：3,3倍好追，非的话要和环的长度比较，如果环-1或-2是3的倍数
//找到环的起始位置，一个从头走，一个从相遇的地方开始走
    //分析：追上的过程中，慢指针是L+x,快指针是L+X+n*C
    //2（L+X）=L+N*C+X,L=(n-1)*c+c-x,L是距离环开头的长度
    //那么一个从开头一个从meet开始走一定会在环头相遇x+L=n*c
    //L是环和头的距离，c为环的长度，而相遇一定是在环上的x

    //方法二，解开meet的点，然后从此处开始走，head走找到相交的点

}
//复制带随机指针的链表
//本题除了节点指向向一个链表，还存在另外一个变量random可能指向后面或前面的链表的头部位
{
    //复制节点，插入到原节点和下一个之间
    //指向复制的random
    //把复制的节点解下来成 新链表，并回复原链表
    struct Node* cur = head;
    while (cur)
    {
        sturct Node* copy = (struct Node*)malloc(sizeof(struct Node));
        copy->val = cur->val;
//插入复制的链表
        copy->next = cur->next;
        cur->next = copy;
        cur = copy->next;
        //拷贝的节点插入原节点后面，先拷贝的后指向，在前面链接，在改变cur的
    }
    //2，根据原节点，处理copy节点的random
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
    //进行第三步骤
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
    //返回头节点
    return copyHead;
}











