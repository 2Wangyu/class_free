/*NAME:YU.
Date:22-11-7
Description:复制数组并对数组进行降序排序*/
#include<stdio.h>
void copy_arr(double* source, double* target, int length)
{
    int i;
    for (i = 0; i < length; i++) {//用循环对数组进行复制，将source中的对应数字赋值到target中；
        target[i] = source[i];
    }
}
void display_array(double* target, int length)
{
    int i;
    for (i = 0; i < length; i++) {//用循环对数组进行打印，以便于比较
        printf("%.1lf", target[i]);//保留一位小数
        printf(" ");
    }
    printf("\n");//打印完数组后进行换行
}
void sort(double* target, int length)
{
    int i, j;
    for (i = length-1; i >=0; i--)//外部循环
    {
        for (j = 0; j <=i; j++) {   //每次运算后最后一个数确定从而每次算都少算一次
            if (target[j] < target[j + 1])//如果获取的数字小，就交换数字之间的顺序
            {
                double tem;//创建中间变量tem，用于交换
                tem = target[j];
                target[j] = target[j + 1];
                target[j + 1] = tem;//每次完成运算后最后一个数字为最小数
            }
        }
    }
}
int main()
{
    double source[5] = { 1.1, 2.2, 3.3, 4.4, 5.5 };
    double target[5];
    copy_arr(source, target, 5);
    display_array(target, 5);
    sort(target, 5);
    display_array(source, 5);//for comparing
    display_array(target, 5);




    return 0;
}