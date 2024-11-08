#include "createdatabase.h"
#include "userinterface.h"
#include<QDir>
#include <QFile>
#include<fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include<QMessageBox>
#include <QTextStream>
#include<QInputDialog>
#include<QLineEdit>
#include<QDebug>
createdatabase::createdatabase()
{

}
void createdatabase::createonedata(QString dbname){
    QDir *dir = new QDir(QDir::currentPath());
    dir->cdUp();
    //判断数据库的长度
    if(dbname.length()>128){
        QMessageBox::information(nullptr, "Warning", "数据库名称太长！");
        return ;
    }

    //对RUanko文件的操作
    QString dirPath = dir->path() + "/DBMS/data/Ruanko.txt";
    QFile file(dirPath);
    // 检查文件是否存在
    if (!file.exists()) {
        // 文件不存在，创建文件并写入内容
        if (file.open( QIODevice::WriteOnly|QIODevice::Text )) {
            // 创建QTextStream对象用于写入文本
            QTextStream out(&file);
            out.setCodec("UTF-8");
            // 显示一个输入对话框，请求用户输入
            QString userInput = QInputDialog::getText(nullptr, "Input Dialog",
                                                          "请输入创建数据库的日期（eg.2022-02-25）：",
                                                          QLineEdit::Normal,
                                                          "", nullptr, Qt::WindowFlags());
            userInput=dbname+" "+userInput+"\n";
            //写入内容,必须先QString,不然会乱码写入
            out << userInput; // 写入文件的初始内容
            file.close();


            //创建数据库文件夹
            // 创建QDir对象
            QDir newdir;
            // 定义你想要创建的文件夹的路径
            QString directoryPath = dir->path() + "/DBMS/data/"+dbname;
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


        }
        else{
            qDebug() << "文件无法创建" << endl;
        }

    }

    //文件存在
    else {
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "文件成功打开";
        } else {
            qDebug() << "文件打开失败：" << file.errorString();
        }
         //读取文件中的数据库名称
        QTextStream in(&file);

        while (!in.atEnd()) {
            QString line = in.readLine(); // 读取一行
            QStringList parts = line.split(' ');
            if (!parts.isEmpty()) {
                QString firstPart = parts.first();
                //进行判断
                if(firstPart==dbname){
                    QMessageBox::information(nullptr, "Warning", "该数据库已经存在！");
                    return ;
                }

            }
        }
        file.close();

        //写入数据库的基本信息
        // 文件存在，打开文件以追加内容
        if (file.open(QIODevice::Append | QIODevice::Text)) {
            // 创建QTextStream对象用于写入文本
            QTextStream out(&file);
            out.setCodec("UTF-8");

            // 显示一个输入对话框，请求用户输入
            QString userInput = QInputDialog::getText(nullptr, "Input Dialog",
                                                          "请输入创建数据库的日期（eg.2022-02-25）：",
                                                          QLineEdit::Normal,
                                                          "", nullptr, Qt::WindowFlags());
            userInput=dbname+" "+userInput+"\n";
            //写入内容,必须先QString,不然会乱码写入
            //QString content = QString::fromUtf8("初始内容\n");
            out << userInput; // 写入文件的初始内容
            file.close();

            //创建数据库文件夹
            // 创建QDir对象
            QDir newdir;
            // 定义你想要创建的文件夹的路径
            QString directoryPath = dir->path() + "/DBMS/data/"+dbname;
            // 使用mkdir方法创建文件夹

            bool result = newdir.mkdir(directoryPath); // true 表示如果上级目录不存在也创建

            if (result) {
                qDebug() << "文件夹创建成功：" << directoryPath;
            } else {
                qDebug() << "文件夹创建失败：" << directoryPath;
            }

        } else {
            qDebug() << "无法打开文件以追加内容:" << dirPath;
        }

         QMessageBox::information(nullptr, "INFORM", "创建成功");
}








}
