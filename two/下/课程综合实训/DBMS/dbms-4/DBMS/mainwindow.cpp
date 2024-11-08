#include "mainwindow.h"
#include "ui_mainwindow.h"

#include"QMessageBox"
#include<QBitmap>
#include<string.h>
#include<QDebug>
#include<iostream>
#include<string>
#include<regex>
#include<QDir>
#include <QFile>
#include<fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <QTextStream>
#include<QInputDialog>
#include<QLineEdit>
#include"userinterface.h"
#include"signupwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->resize(1180, 566); // 设置初始大小
    this->setFixedSize(1280, 853); // 设置固定大小
    QPixmap Images(":/image/back.jpg");
    QPalette Palette = this->palette();
    Palette.setBrush(QPalette::Background,Images);
    this->setPalette(Palette);
    setMask(Images.mask());
    //去窗口边框
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    // 设置按钮的样式表
    ui->pushButton_3->setStyleSheet("QPushButton { background-color: transparent; border: none; }");

}

MainWindow::~MainWindow()
{
    delete ui;
}

//登录
void MainWindow::on_pushButton_clicked()
{

    QString username=ui->lineEdit->text();
    QString password=ui->lineEdit_2->text();
    QDir *dir = new QDir(QDir::currentPath());
    dir->cdUp();
    //创建数据库文件夹
    // 创建QDir对象
    QDir newdir;
    // 定义你想要创建的文件夹的路径
    QString directoryPath = dir->path() + "/DBMS/User/"+username+"/password.txt";
    //判断是否创建过该用户
    QDir dir2(dir->path() + "/DBMS/User");
    if(username.isEmpty()||password.isEmpty()){
        QMessageBox::information(nullptr, "Warning", "请输入");

    }
    else if (dir2.exists(username)) {

        QFile file(directoryPath);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Error opening file:" << directoryPath;                                                     }
          //读取密码
        QTextStream in(&file);
        QString content = in.readAll();
        if(content!=password){
            QMessageBox::information(nullptr, "Warning", "密码错误");

         }
        else{

            connect(this, &MainWindow::sendData, user, &UserInterface::receiveData);
            // 当按钮点击时，发射 sendData 信号，并传递 LineEdit 中的文本内容
            emit sendData(ui->lineEdit->text());

            QMessageBox::information(nullptr, "Warning", "登录成功");
            ui->lineEdit->setText("");
            ui->lineEdit_2->setText("");
            this->close();



            user->show();
        }
        file.close();
   } else {
          QMessageBox::information(nullptr, "Warning", "无该用户，请注册！");
        }
}

//退出
void MainWindow::on_pushButton_2_clicked()
{
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    this->close();
}


//点击注册账户的功能
void MainWindow::on_pushButton_3_clicked()
{

    user->close();
    newuser->show();

}
