#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

class myPrint
{
public:
	void operator()(int val)
	{
		// 反转指定范围的元素
		// beg 开始迭代器
		cout << val << " ";
	}
};
void test01()
{
	vector<int> v1;
	vector<int> v2;
	for (int i = 0; i < 10; i++)
	{
		v1.push_back(i);
		v2.push_back(i + 2);
	}
	vector<int> vtarget;
	//目标容器需要提前开辟空间
	vtarget.resize(v1.size() + v2.size());
	//合并 需要两个有序序列
	merge(v1.begin(), v1.end(), v2.begin(), v2.end(), vtarget.begin());
	for_each(vtarget.begin(), vtarget.end(), myPrint());
	cout << endl;
}
int main() {
	test01();
	system("pause");
	return 0;
}