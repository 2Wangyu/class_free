#ifndef CALCULATOR_H
#define CALCULATOR_H
#include<QtWidgets/QWidget>
#include <QMainWindow>
#include<QAbstractButton>
#include"Stack.cpp"
#include<QTextEdit>
using namespace std;
QT_BEGIN_NAMESPACE
namespace Ui { class calculator; }
QT_END_NAMESPACE

class calculator : public QMainWindow
{
    Q_OBJECT

public:
    calculator(QWidget *parent = nullptr);
    ~calculator();
    //用于存储两个文本框的内容
    QString string1;
    QString string2;

    //判断是否为数字
    bool isNumber(char number);
    //判断输入内容是否合法
    bool isValid();
    //判断括号是否匹配
    bool validEnco(QString tem);
    //比较运算符号的优先级
    bool compare(char a,char b);

private slots:
    //简单的事件，点击后直接显示出来
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_point_clicked();
    void on_pushButton_0_clicked();
    void on_pushButton_right_clicked();
    void on_pushButton_left_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_plus_clicked();
    void on_pushButton_minus_clicked();
    void on_pushButton_mult_clicked();
    void on_pushButton_rid_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();

    //清除和回退功能
    void on_pushButton_clear_clicked();
    void on_pushButton_back_clicked();
    //倒数，平方，开方
    void on_pushButton_reverse_clicked();
    void on_pushButton_twice_clicked();
    void on_pushButton_half_clicked();
    //等号
    void on_pushButton_equal_clicked();

    //显示历史记录
    void on_pushButton_record_clicked();



private:
    Stack<char>* stack1;
    Stack<double> *stack2;
    QWidget *a=new QWidget;
    QTextEdit *record=new QTextEdit();
    Ui::calculator *ui;
};
#endif // CALCULATOR_H
