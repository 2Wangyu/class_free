#ifndef MYQUEUE_H
#define MYQUEUE_H
#include"Car.h"

class myQueue
{
public:
    myQueue();
    ~myQueue() {};
    void EnQueue(Car* x); //新元素入队
    bool DeQueue() ;       //队头元素出队
    Car* get() ;      //获取队头元素
    bool IsEmpty();      //判断队列是否为空

private:
    struct LinkNode* front;//代表头节点
    struct LinkNode* rear;//代表尾结点


};
//用struct定义节点
struct LinkNode {
    Car *data; //数据域
    LinkNode* next; //指针域，指向下一个节点
    LinkNode() //仅初始化指针的构造函数
    {
        LinkNode* ptr = nullptr;
        next = ptr;
    }
    LinkNode( Car *item, LinkNode* ptr = nullptr) //初始化数据和指针成员的构造函数
    {
        data = item;
        next = ptr;
    }
};

#endif // MYQUEUE_H
