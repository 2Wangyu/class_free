/*NAME:YU.
Date:22-11-7
Description:�������鲢��������н�������*/
#include<stdio.h>
void copy_arr(double* source, double* target, int length)
{
    int i;
    for (i = 0; i < length; i++) {//��ѭ����������и��ƣ���source�еĶ�Ӧ���ָ�ֵ��target�У�
        target[i] = source[i];
    }
}
void display_array(double* target, int length)
{
    int i;
    for (i = 0; i < length; i++) {//��ѭ����������д�ӡ���Ա��ڱȽ�
        printf("%.1lf", target[i]);//����һλС��
        printf(" ");
    }
    printf("\n");//��ӡ���������л���
}
void sort(double* target, int length)
{
    int i, j;
    for (i = length-1; i >=0; i--)//�ⲿѭ��
    {
        for (j = 0; j <=i; j++) {   //ÿ����������һ����ȷ���Ӷ�ÿ���㶼����һ��
            if (target[j] < target[j + 1])//�����ȡ������С���ͽ�������֮���˳��
            {
                double tem;//�����м����tem�����ڽ���
                tem = target[j];
                target[j] = target[j + 1];
                target[j + 1] = tem;//ÿ�������������һ������Ϊ��С��
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