#include<string>
#include<iostream>
using namespace std;

class print {

public:
	void printString(string stringTem, int times);
	void printString(string stringTem);
	print() {
		print::n = 0;

	}
	static int n;
};

void print::printString(string stringTem, int times) {

	for (int i = 0; i < print::n + times; i++) {

		cout << stringTem << endl;

	}
	

}
void print::printString(string stringTem) {

	cout << stringTem << endl;
}