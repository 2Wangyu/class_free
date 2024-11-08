//#include<iostream>
//#include<string>
//
//using namespace std;
//
//
//
//int main() {
//	string sysinSecond;
//	cout<<"下面会要求您输入想要转换为秒数(必须为整数)，我们会将秒转换为以秒，分钟，小时等单位" << endl;
//	cin >> sysinSecond;
//	int numroot = sysinSecond.find(".");
//	int num = stoi(sysinSecond);
//	while (num < 0||numroot<sysinSecond.length()) {
//	
//		cout << "请输入非负正整数" << endl;
//		cin >> sysinSecond;
//		numroot = sysinSecond.find(".");
//		num = stoi(sysinSecond);
//	}
//	int day = 0;
//	int	hour = 0;
//	int minute = 0;
//	int second = 0;
//	string mess="转化后的时间为:";
//
//	if (num > 3600 * 24) {
//		day = num / (3600 * 24);
//		num = num % (3600 * 24);
//		
//		mess =mess+to_string(day)+"day ";
//	}
//	if (num > 3600) {
//		hour = num / 3600 ;
//		num = num % 3600 ;
//		mess = mess+to_string(hour) + "hour ";
//	}
//	if (num > 60) {
//		minute = num / 60;
//		num = num % 60;
//		mess = mess+to_string(minute) + "minute ";
//	}
//	if (num > 0) {
//		mess = mess+to_string(num) + "second ";
//	
//	}
//
//	cout << mess << endl;
//
//
//
//}