#include "dropdatabase.h"
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
dropdatabase::dropdatabase()
{

}
void dropdatabase::droponedata(QString dbname){
    QDir *dir = new QDir(QDir::currentPath());
    dir->cdUp();
    //对RUanko文件的操作
    QString dirPath = dir->path() + "/DBMS/data/Ruanko.txt";
    QFile file(dirPath);

    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
            qDebug() << "无法打开文件：" << file.errorString();
            return;
        }

        // 创建一个新文件，用于临时保存修改后的内容
        QFile tempFile(dir->path() + "/DBMS/data/"+"temp.txt");
        if (!tempFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug() << "无法创建临时文件：" << tempFile.errorString();
            file.close();
            return;
        }

        // 读取文件内容并删除指定数据库名称的行
        QTextStream in(&file);
        QTextStream out(&tempFile);
        bool found = false; // 标志是否找到了指定的数据库名称
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(' ');
            if (!parts.isEmpty() && parts.first() == dbname) {
                // 找到了要删除的数据库名称，设置标志为true
                found = true;
                continue; // 跳过该行，不写入到临时文件中
            }
            out << line << "\n";
        }

        // 如果没有找到指定的数据库名称，则输出提示信息
        if (!found) {
            qDebug() << "未找到数据库：" << dbname;
            file.close();
            tempFile.close();
            return;
        }

        // 关闭文件
        file.close();
        tempFile.close();

        // 删除原文件
        file.remove();

        // 重命名临时文件为原文件名
        tempFile.rename(dir->path() + "/DBMS/data/Ruanko.txt");

        //删除文件夹

        // 创建 QDir 对象
        QString folderPath=dir->path() + "/DBMS/data/"+dbname;;
        QDir folderDir(folderPath);

           // 检查文件夹是否存在并删除
           if (folderDir.exists()) {
               if (folderDir.removeRecursively()) {
                   qDebug() << "文件夹删除成功：" << folderPath;
                   QMessageBox::information(nullptr, "INFORM", "数据库删除成功");
               } else {
                   qDebug() << "文件夹删除失败：" << endl;
               }
           } else {
               qDebug() << "文件夹不存在：" << folderPath;
           }













}
