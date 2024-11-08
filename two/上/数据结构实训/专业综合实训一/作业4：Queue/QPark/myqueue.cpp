#include "myqueue.h"

myQueue::myQueue()
{

    rear=front = new LinkNode();
}
void myQueue::EnQueue(Car* x) {
    //从尾部添加元素
    LinkNode* next = new LinkNode(x);
    rear->next =next ;
    rear = next;

} //新元素入队

bool myQueue::DeQueue() {
    if (front->next == nullptr)
        return false;
    else {
        LinkNode* temp = front->next;
        if (temp->next == nullptr) {
            front->next =nullptr;
            rear = front;
        }
        else {
            front->next = temp->next;
            temp == nullptr;
        }
    }
};       //队头元素出队

Car* myQueue::get() {
    return front->next->data;
};      //获取队头元素
bool myQueue::IsEmpty() {

    return(front==rear);

};      //判断队列是否为空
