#include "pickking.h"
#include<QList>
#include<QString>
#include<QDebug>

//构建约瑟夫循环节点的结构体
PickKing::~PickKing(){
    headnode=nullptr;
}
PickKing::PickKing(){
    headnode=nullptr;
}

void PickKing::CreatingRing(int num){
    //初始化约瑟夫化：即构建单向循环链表
        node* head=new node;
        node* temphead;
        node* temp;
        //暂时的头节点用来完成初始化约瑟夫环
        temphead=head;
       //通过循环来实现约瑟夫环
        for(int i=1;i<=num;i++){
            temp=new node;
            temp->val=i;
            temphead->next=temp;
            temphead=temp;
        }
        //让尾结点指向头节点的下一个有值节点
        temphead->next=head->next;
        headnode=head;
};

QList<QString> PickKing::StartJR(int listingnum){
   QList<QString> list;
    //作为头节点的临时指针，遍历
    node *a=headnode->next;
    node *b;
    while(a->next!=a){
        //找到要出列的猴子
        for(int j=1;j<listingnum;j++){
            //b存入前一个节点
            b=a;
            //a存入被删除节点
            a=a->next;
        }
        //从下一个节点开始
        a=a->next;
        //将要删除的猴子编号记录到数组当中
        QString string=QString::number(b->next->val);
        list.append(string);
        delete b->next;
        b->next=a;
        //删除出列编号的猴子

    }
    //将最后选出来的大王存入数组当中
        list.append(QString::number(a->val));
        return list;
};


