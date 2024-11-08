#include"Stack.h"
template<class T>
Stack<T>::Stack(){
    front=new node<T>();

}
template<class T>
bool Stack<T>::IsEmpty(){
    return(front->next==nullptr);

}//判断队列是否为空

template<class T>
bool Stack<T>::push(T elem){
    struct node<T>* next = new node<T>(elem);
    struct node<T>* tem=front->next;
    next->next=tem;
    front->next =next;

}//入栈

template<class T>
bool Stack<T>::pop(){
    if (front->next == nullptr)
        return false;
    else {
        struct node<T>* temp = front->next;
        if (temp->next == nullptr) {
            front->next = nullptr;
        }
        else {
            front->next = temp->next;
            temp == nullptr;
        }
    }
    return true;

}//出栈


template<class T>
T Stack<T>::getFront(){
    return front->next->val;

};//获取头节点


