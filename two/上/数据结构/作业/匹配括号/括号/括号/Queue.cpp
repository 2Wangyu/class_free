#include "Queue.h"
#pragma once

Queue::Queue(){
	
	rear=front = new LinkNode();
	
}
void Queue::EnQueue(const char x) {
	//��β�����Ԫ��
	LinkNode* next = new LinkNode(x);
	rear->next =next ;
	rear = next;

} //��Ԫ�����

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
};       //��ͷԪ�س���

char Queue::getRear() {
	return rear->data;
};      //��ȡ��ͷԪ��
bool Queue::IsEmpty() {

	return(front==rear);

};      //�ж϶����Ƿ�Ϊ��
