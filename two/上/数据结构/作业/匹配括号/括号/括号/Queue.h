#include<iostream>

class Queue
{
public:
	Queue() ;
	~Queue() {};
    void EnQueue(const char x); //��Ԫ�����
	bool DeQueue() ;       //��ͷԪ�س���
    char getRear() ;      //��ȡ��ͷԪ��
	bool IsEmpty();      //�ж϶����Ƿ�Ϊ��
	
private:
	struct LinkNode* front;//����ͷ�ڵ�
	struct LinkNode* rear;//����β���
};

//��struct����ڵ�
struct LinkNode {
	char data; //������
	LinkNode* next; //ָ����ָ����һ���ڵ�
	LinkNode() //����ʼ��ָ��Ĺ��캯��
	{
		LinkNode* ptr = nullptr;
		next = ptr;
	}
	LinkNode(const char item, LinkNode* ptr = nullptr) //��ʼ�����ݺ�ָ���Ա�Ĺ��캯��
	{
		data = item;
		next = ptr;
	}
};