#ifndef STACK_H
#define STACK_H
template<class valType>
struct node{
    valType val;
    struct node<valType> *next;
    node() //仅初始化指针的构造函数
    {
        node* ptr = nullptr;
        next = ptr;
    }
    node(const valType item, node* ptr = nullptr) //初始化数据和指针成员的构造函数
    {
        val = item;
        next = ptr;
    }
};

template<class T>
class Stack
{
public:
    Stack();
    bool IsEmpty();      //判断队列是否为空
    bool push(T elem);//入栈
    bool pop();//出栈
    T getFront();//获取头节点
private:
    struct node<T>* front;//代表头节点

};



#endif // STACK_H
