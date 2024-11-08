#include "Queue.h"
#pragma once

Queue::Queue(){
	
	rear=front = new LinkNode();
	
}
void Queue::EnQueue(const char x) {
	//从尾部添加元素
	LinkNode* next = new LinkNode(x);
	rear->next =next ;
	rear = next;

} //新元素入队

bool Queue::DeQueue() {
	if (front->next == NULL)
		return false;
	else {
		LinkNode* temp = front->next;
		if (temp->next == NULL) {
			front->next = NULL;
			rear = front;
		}
		else {
			front->next = temp->next;
			temp == nullptr;
		}
	}
};       //队头元素出队

char Queue::getRear() {
	return rear->data;
};      //获取队头元素
bool Queue::IsEmpty() {

	return(front==rear);

};      //判断队列是否为空
