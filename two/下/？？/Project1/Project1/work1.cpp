#include<iostream>
#include<vector>
using namespace std;
#include<algorithm>

int countordernum(int n,vector<int> stunum) {
	
	vector<int> heightest(n);
	vector<int> ordernum(n);
	
	if (n == 0)
		return 0;
	ordernum[0] = 1;
	heightest[0] = stunum[0];
	if (n == 1) {

		return 1;
	}


	for (int i = 1; i < n; i++) {
		//for (int j = 0; j < i; j++) {
			int heightbefore = heightest[i-1];
			int heightnow = stunum[i];
			if (heightnow > heightbefore) {
				heightest[i] = heightnow;
				ordernum[i]=ordernum[i-1]+1;
			}
			else {
				ordernum[i] = ordernum[i - 1];
			
			}
		//}
	}
	return ordernum[n-1];
}
int main() {
	int n = 0;
	cin >> n;
	vector<int> stunum(n);
	for (int i = 0; i < n;i++) {
		cin >> stunum[i];
	}
	int num1=countordernum(n, stunum);
	reverse(stunum.begin(), stunum.end());
	int num2 = countordernum(n, stunum);
	int result = n - (num1 + num2 - 1);
	cout << result << endl;



}
