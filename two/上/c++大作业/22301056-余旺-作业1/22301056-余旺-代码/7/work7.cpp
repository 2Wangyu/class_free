#include<iostream>
#include<string>
using namespace std;
struct CandyBar {
	string name;
	double weight;
	int heat;


};
void initBar(struct CandyBar* &bar, string name = "Millennium Munch",
	double weight = 2.85, int heat = 350) {
	bar->name = name;
	bar->weight = weight;
	bar->heat = heat;


};
void printBar( struct CandyBar*  &const bar)  {

	cout<<bar->name<<endl;
	cout<<bar->weight <<endl;
	cout<<bar->heat <<endl;
}
int main() {
	struct CandyBar* bar1=new CandyBar;
	initBar(bar1,"madeChina", 3.33, 400);
	printBar(bar1);
	delete bar1;



}