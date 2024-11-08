#ifndef WIDGETSHOW_H
#define WIDGETSHOW_H
#include<QVBoxLayout>
#include<QPushButton>
#include<QTextEdit>
#include<QLineEdit>
#include<QList>
#include <QWidget>

class WidgetShow : public QWidget
{
    Q_OBJECT

public:
    WidgetShow(QWidget *parent = nullptr);
    ~WidgetShow();

public:
      //start button
    QPushButton *button;
    //展示大王按钮：
    QPushButton *King;
    //按钮下的两个展示窗口
    QGridLayout *edit1;
    QTextEdit *edit2;
    //输入猴子信息的文本框
    QLineEdit* text1;
    QLineEdit* text2;
    QList<QString> list;
    //记录猴子的编号
   QString number;

    //开始按钮的点击事件
    void on_button_clicked();
    void on_King_clicked();




};
#endif // WIDGETSHOW_H
