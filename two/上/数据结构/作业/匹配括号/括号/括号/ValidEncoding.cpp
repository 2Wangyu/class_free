
#include"Queue.h"
#include <iostream>
using namespace std;


bool isValidEncoding(const char *s) {
	Queue *queue = new Queue();
	for (int i = 0; i < strlen(s); i++) {
		char temp = s[i];
		if (temp == '(' || temp == '[' || temp == '{') {
			queue->EnQueue(temp);
		}
		else {
			if (queue->IsEmpty() == true)
				return false;
			char a = queue->getRear();
			if (temp == ')') {
				if (a == '(')
					queue->DeQueue();
				else
					return false;
			}
			else if (temp == ']') {
				if (a == '[')
					queue->DeQueue();
				else
					return false;
			}
			else {
				if (a == '{')
					queue->DeQueue();
				else
					return false;
			}
		}
	}
	if (queue->IsEmpty() == true)
		return true;
	else
		return false;
}


int main() {


	bool a = isValidEncoding("()");
	bool b = isValidEncoding("()[]{}");
	bool c = isValidEncoding("(]");
	bool d = isValidEncoding("([)]");
	cout << "a£º" << a << endl;
	cout << "b£º" << b << endl;
	cout << "c£º" << c << endl;
	cout << "d£º" << d << endl;

}