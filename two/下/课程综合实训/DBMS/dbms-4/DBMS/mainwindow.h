#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"userinterface.h"
#include"signupwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //登录和注册窗口
    UserInterface *user=new UserInterface;
    signupwidget *newuser=new signupwidget;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

public:
    Ui::MainWindow *ui;

signals:
    void sendData(const QString &data); // 定义一个发送数据的信号


};
#endif // MAINWINDOW_H
