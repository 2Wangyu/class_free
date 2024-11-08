#ifndef LIST_H
#define LIST_H
#include<iostream>

template <typename T>
class List {
private:
    T* elements;
    int size;//大小
    int capacity;//容量

public:
    List(int capacity);
    ~List();

    void addElement(T element);
    void resize();
    bool isEmpty() const;
    bool isFull() const;
    void forEach() const;

};

// 将模板实现放在头文件的底部
#include "list.cpp"

#endif // LIST_H
