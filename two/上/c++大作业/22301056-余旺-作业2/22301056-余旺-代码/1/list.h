#ifndef LIST_H
#define LIST_H
#include<iostream>

template <typename T>
class List {
private:
    T* elements;
    int size;//��С
    int capacity;//����

public:
    List(int capacity);
    ~List();

    void addElement(T element);
    void resize();
    bool isEmpty() const;
    bool isFull() const;
    void forEach() const;

};

// ��ģ��ʵ�ַ���ͷ�ļ��ĵײ�
#include "list.cpp"

#endif // LIST_H
