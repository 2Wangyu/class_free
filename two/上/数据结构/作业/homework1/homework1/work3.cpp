//#include<iostream>
//#include<string>
//
//using namespace std;
//
//
//
//int main() {
//	string sysinSecond;
//	cout<<"�����Ҫ����������Ҫת��Ϊ����(����Ϊ����)�����ǻὫ��ת��Ϊ���룬���ӣ�Сʱ�ȵ�λ" << endl;
//	cin >> sysinSecond;
//	int numroot = sysinSecond.find(".");
//	int num = stoi(sysinSecond);
//	while (num < 0||numroot<sysinSecond.length()) {
//	
//		cout << "������Ǹ�������" << endl;
//		cin >> sysinSecond;
//		numroot = sysinSecond.find(".");
//		num = stoi(sysinSecond);
//	}
//	int day = 0;
//	int	hour = 0;
//	int minute = 0;
//	int second = 0;
//	string mess="ת�����ʱ��Ϊ:";
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