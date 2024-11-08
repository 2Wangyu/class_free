/*Date:22-12-11
* Name:YU.
* Description:计算两个日期之间的天数
ID：22301056
*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
typedef struct {//创建结构体
	int month;
	int day;
	int year;
} MyDate;
int difDays( MyDate d1, MyDate d2);//声明函数
void showdate(mydate);
void swap(MyDate *d1,MyDate *d2);



int main()
{
	MyDate d1 = {0};
	MyDate d2 = {0};
	printf("请输入第一个日期,按照年月日\n");//请求用户的日期
	scanf("%d%d%d",&d1.year,&d1.month,&d1.day);
	printf("请输入第二个日期\n");
	scanf("%d%d%d", &d2.year, &d2.month, &d2.day);
	//判断年的先后顺序,如果前面的大就交换
	if (d1.year > d2.year)
		swap(&d1, &d2);
	//计算日期之间天数并教给c
	int c = difDays(d1, d2);
	showdate(d1);//调用函数显示日期的格式
	printf("和");
	showdate(d2);
	printf("这两个日期之间相差%d天", c);

	return 0;
}
int difDays(const MyDate d1, const MyDate d2) {
	int count = 0;
	int midday = 0;//代表两难之间整年的天数
	int stday = 0;//代表前一年的天数
	int endday = 0;//代表后一年的天数
	int a = d1.year;
	int b = d2.year;
	for (int c = a + 1; c < b; c++) {
		if ((c % 4 == 0 && c % 100 != 0) || (c % 400 == 0))
			midday += 366;
		else
		{
			midday += 365;
		}
	}//计算中间的天数
	int arr1[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	int arr2[12] = { 31,29,31,30,31,30,31,31,30,31,30,31 };
	if ((d2.year % 4 == 0 && d2.year % 100 != 0) || (d2.year % 400 == 0)) {//如果是闰年就用闰年的数组计算
		for (int d = d2.month - 2; d >= 0; d--) {//遍历天数开始累加
			endday += arr2[d];//最后一个月不可以全加-1；下标再-1
		}
		endday += d2.day;
	}
	else {
		for (int d = d2.month - 2; d >= 0; d--) {//遍历天数开始累加
			endday += arr1[d];//最后一个月不可以全加-1；下标再-1
		}
		endday += d2.day;
	}

	if ((d1.year % 4 == 0 && d1.year % 100 != 0) || (d1.year % 400 == 0))
	{
		for (int d = d1.month; d <= 11; d++)//从下一个月开始算到月末
		{
			stday += arr2[d];
		}
		stday = stday + arr2[d1.month - 2] - d1.day;//当月的天数为月末减去day
	}
	else {
		for (int d = d1.month; d <= 11; d++)
		{
			stday += arr1[d];
		}
		stday = stday + arr1[d1.month - 2] - d1.day;
	}

	count = midday + stday + endday;//三个的和为相差的天数
	return count;
	}
void showdate(MyDate day) 
{
	printf("%d-%d-%d", day.year, day.month, day.day);
}
void swap(MyDate* d1, MyDate* d2) {
	MyDate tem;
	tem = *d1;
	*d1 = *d2;
	*d2 = tem;
}



//year % 4 == 0 && year % 100 != 0 ) || (year % 400 == 0