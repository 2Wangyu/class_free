#include "list.h"
#include <iostream>
using namespace std;


int main() {
    // Create an empty list 
    List<int> myList(5);

    // Check if the list is empty
    cout << "Is list empty? ah ,guess?"<<endl;
    cout<< (myList.isEmpty() ? "Yes" : "No") <<endl;

    // Add elements to the list
    myList.addElement(1);
    myList.addElement(2);
    myList.addElement(3);
    myList.addElement(4);
    myList.addElement(5);
    myList.addElement(6);


    // Check if the list is full
    //给出提示，因为是2倍扩容所以该实例并不会满
    cout << "Is list full? ah,guess? "<<endl;
    cout << (myList.isFull() ? "Yes" : "No") << endl;

    // Process each element in the list
    cout<< "Now visit the elements you added: "<<endl;
    myList.forEach();
    

    return 0;
}
