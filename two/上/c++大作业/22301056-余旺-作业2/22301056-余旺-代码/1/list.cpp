#include "list.h"
using namespace std;

template <typename T>
List<T>::List(int capacity) {
    this->elements = new T[capacity];
    this->size = 0;
    this->capacity = capacity;
}
//template class List<int>;  
//template List<int>::~List();  
template <typename T>
List<T>::~List() {
    delete[] elements;
}

template <typename T>
void List<T>::addElement(T element) {
    if (size == capacity) {
        resize(); // Resize the list if it's full
    }

    elements[size++] = element;
}
template <typename T>
void List<T>::resize() {
    //int newCapacity = capacity + 4;
    int newCapacity = capacity * 2; // Double the capacity if it is full
    T* newElements = new T[newCapacity];

    for (int i = 0; i < size; ++i) {
        newElements[i] = elements[i];
    }

    delete[] elements;
    elements = newElements;
    capacity = newCapacity;
}

//List is empty??
template <typename T>
bool List<T>::isEmpty() const {
    return size == 0;
}
// List is full??
template <typename T>
bool List<T>::isFull() const {
    return size == capacity;
}

template <typename T>
void List<T>::forEach() const {
    for (int i = 0; i < size; ++i) {
        cout << "hhhh,the element you wanna visit is " << elements[i] << endl;
    }

}
