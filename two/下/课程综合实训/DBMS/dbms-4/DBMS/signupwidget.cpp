#include "signupwidget.h"
#include "ui_signupwidget.h"

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
#include"smtp.h"
#include<QTime>
#include <QByteArray>

signupwidget::signupwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::signupwidget)
{
    ui->setupUi(this);
    this->resize(1180, 566); // 设置初始大小
    this->setFixedSize(600, 800); // 设置固定大小
    QPixmap Images(":/image/back.jpg");
    QPalette Palette = this->palette();
    Palette.setBrush(QPalette::Background,Images);
    this->setPalette(Palette);
    setMask(Images.mask());
    //去窗口边框
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());

}

signupwidget::~signupwidget()
{
    delete ui;
}

//退出按钮
void signupwidget::on_pushButton_2_clicked()
{
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    ui->lineEdit_4->setText("");
    this->close();
}



//注册按钮
void signupwidget::on_pushButton_clicked()
{
    QString username=ui->lineEdit->text();
    QString password=ui->lineEdit_2->text();
    QString againpass=ui->lineEdit_4->text();
    if(password!=againpass){
        QMessageBox::information(nullptr, "Warning", "两次密码不一致");
    }
    else if(password==nullptr||againpass==nullptr){
        QMessageBox::information(nullptr, "Warning", "密码不为空");
    }
    else{
        QDir *dir = new QDir(QDir::currentPath());
        dir->cdUp();
        //创建数据库文件夹
        // 创建QDir对象
        QDir newdir;
        // 定义你想要创建的文件夹的路径
        QString directoryPath = dir->path() + "/DBMS/User/"+username;
        //判断是否创建过该用户
        QDir dir2(dir->path() + "/DBMS/User");
           if (dir2.exists(username)) {
              QMessageBox::information(nullptr, "Warning", "该用户已经创建过了");

           } else {
               //输入验证码的框
               QString temp = ui->lineEdit_6->text();
               if (temp == code) {
                   QMessageBox::information(NULL, "成功", "验证成功，欢迎您使用MYSQL！");
                   //后续的进入游戏功能
                   // 使用mkdir方法创建文件夹
                   // 如果需要创建多级目录，可以传递true作为第二个参数
                   bool result = newdir.mkdir(directoryPath); // true 表示如果上级目录不存在也创建

                   if (result) {
                       qDebug() << "文件夹创建成功：" << directoryPath;
                   }
                   else {
                       qDebug() << "文件夹创建失败：" << directoryPath;
                   }
                   QMessageBox::information(nullptr, "INFORM", "创建成功");

                   //对密码文件的操作
                   QString dirPath = dir->path() + "/DBMS/User/"+username+"/password.txt";
                   QFile file(dirPath);
                   // 检查文件是否存在
                   if (!file.exists()) {
                       // 文件不存在，创建文件并写入内容
                       if (file.open( QIODevice::WriteOnly|QIODevice::Text )) {
                           // 创建QTextStream对象用于写入文本
                           QTextStream out(&file);
                           out.setCodec("UTF-8");

                           //写入内容,必须先QString,不然会乱码写入
                           out << password; // 写入文件的初始内容
                           file.close();
                                                                         }
                                        }

                   this->close();
               }
               else {
                   QMessageBox::information(NULL, "失败", "验证码错误，请重新输入！");
                   return ;

               }





          }
    }
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    ui->lineEdit_4->setText("");


}



void signupwidget::on_pushButton_3_clicked()
{
    QString subject = "MYSQL登录验证码";
    QMessageBox::information(NULL, "提示", "验证码将在30s内发送至您的邮箱，请耐心等待。");
    QTime time = QTime::currentTime();
    srand(time.msec() + time.second() * 1000);
    code = QString::number(1000 + rand() % (9999 - 1000));    //产生1000~9999以内的随机数
    QString content = "欢迎登录MYSQL，本次操作的验证码为：" + code;

    Smtp s("13584149536@163.com", "YIMMQLOUDXOXKNTL");
    //输入的账户的edit,账户要求要邮箱账户
    QString mail = ui->lineEdit_5->text();
    if(mail.isEmpty()){
        QMessageBox::information(NULL, "提示", "发送验证码邮箱不能为空");
    }
    else{
        s.send(mail.toUtf8(), subject, content);
    }

}
