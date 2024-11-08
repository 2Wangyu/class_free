#include<iostream>
#include<string>

using namespace std;

struct Car {

	string make;
	int year;
	Car() = default;
	Car(string making,int years):make(making),year(years) {
	};
};


int main() {
	int num = 0;
	cout<<"How many cars do you wish to catalog ?" << endl;
	cin >> num;
	cin.ignore();

	Car* array=new Car[10];
	//vector<Car> array;
	for (int i = 0; i < num; i++) {
		char make[100]; 
		int year;
		cout << "Car #" << i+1 << endl;
		cout << "Please enter the make " << endl;
		cin.getline(make,100);
		string making (make);
		cout << "Please enter the year made :" << endl;
		cin >> year;
		cin.ignore();
		struct Car *onecar = new Car(making, year);
		//array.push_back(*onecar);
		array[i] = *onecar;

	}

	cout << "Here is your collection" << endl;
	for (int i = 0; i <num; i++) {
		cout << array[i].year <<"  " << array[i].make << endl;
	}
	delete[]array;
	
	
}