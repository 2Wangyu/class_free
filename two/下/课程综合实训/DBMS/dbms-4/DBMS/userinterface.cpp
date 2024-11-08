#include "userinterface.h"
#include "ui_userinterface.h"
#include"createdatabase.h"
#include"dropdatabase.h"
#include "droprecord.h"
#include "insertrecord.h"
#include "modifyrecord.h"
#include "searchrecord.h"
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
#include<QMessageBox>
#include <QTextStream>
#include<QInputDialog>
#include<QLineEdit>
#include <QFileDialog>
#include <QDateTime>
using namespace std;


QString dname="";


UserInterface::UserInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserInterface)
{
    ui->setupUi(this);
    this->setWindowTitle("用户界面");
    this->resize(800, 600); // 设置初始大小
    this->setFixedSize(800, 600); // 设置固定大小
    QPixmap Images(":/image/background.png");
    QPalette Palette = this->palette();
    Palette.setBrush(QPalette::Background,Images);
    this->setPalette(Palette);
    setMask(Images.mask());
    ui->label->setStyleSheet("color: white;"); // 设置文字颜色为红色
    ui->label->show();

}

UserInterface::~UserInterface()
{
    delete ui;
}


//每次输入数据库操作后
void UserInterface::on_GO_clicked()
{
    string readmess = ui->readline->toPlainText().toStdString();
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString currentTime = currentDateTime.toString("yyyy-MM-dd hh:mm:ss");

    writelog(username,QString::fromStdString(readmess),currentTime);

    // 输出内容到控制台
    //qDebug() << "QTextEdit content:" << readmess;

    // 通过正则化表达式读取内容
    //正则化的所有语句
    //1,创建数据库
    std::regex createdatabase("CREATE\\s+DATABASE\\s+(\\w+)", std::regex_constants::icase);
    //2，删除数据库
    std::regex dropdatabase("DROP\\s+DATABASE\\s+(\\w+)", std::regex_constants::icase);

    //3，创建表
    std::regex createTable("CREATE\\s+TABLE\\s+(\\w+)\\s*\\(([^\\)]+)\\)", regex_constants::icase);
    //4 识别数据库
    //我们需要指定数据库对其进行接下来的操作
    std::regex useDatabaseRegex("USE\\s+DATABASE\\s+(\\w+)", regex_constants::icase);

        // 待匹配的字符串
        //string query = "CREATE DATABASE my_database";


    //5，删除表
    std::regex dropTableRegex("DROP\\s+TABLE\\s+(\\w+)", regex_constants::icase);
    //6,修改表
    std::regex alterTableRegex("ALTER\\s+TABLE\\s+(\\w+)\\s+(ADD|MODIFY|DROP)\\s+(\\w+)(?:\\s+(\\w+(?:\\(\\d+\\))?))?(?:\\s+(\\w+(?:\\(\\d+\\))?))?", regex_constants::icase);

    //7,插入记录
    //INSERT INTO table_name (column1, column2, ...) VALUES (value1, value2, ...)
    std::regex insertRecordRegex("INSERT\\s+INTO\\s+(\\w+)\\s*\\(([^\\)]+)\\)\\s*VALUES\\s*\\(([^\\)]+)\\)", std::regex_constants::icase);

    // 8, 删除记录
    std::regex deleteRecord("DELETE\\s+FROM\\s+(\\w+)\\s+WHERE\\s+(.+)", std::regex_constants::icase);


    //9,修改记录
    std::regex modifyRecord("UPDATE\\s+(\\w+)\\s+SET\\s+(.+)\\s+WHERE\\s+(.+)", std::regex_constants::icase);


    //对于权限暂时只有all选项
    //10，查看权限
    //std::regex showpermission("SHOW\\s+GRANTS\\s+FOR\\s+(\\w+)", std::regex_constants::icase);

    //11.授予权限，
    //std::regex grantpermission("GRANT\\s+ALL\\s+ON\\s+(\\w+\\.\\w+)\\s+TO\\s+(\\w+)", std::regex_constants::icase);
    std::regex grantpermission("GRANT\\s+ALL\\s+ON\\s+(\\w+)\\s+TO\\s+(\\w+)", std::regex_constants::icase);



    //12.回收权限
    //std::regex revokepermission("REVOKE\\s+ALL\\s+ON\\s+(\\w+\\.\\w+)\\s+FROM\\s+(\\w+)", std::regex_constants::icase);
    std::regex revokepermission("REVOKE\\s+ALL\\s+ON\\s+(\\w+)\\s+FROM\\s+(\\w+)", std::regex_constants::icase);


    std::regex grantPermissionRegex("GRANT\\s+(SELECT|INSERT|DELETE|UPDATE|ALL)\\s+ON\\s+(\\w+)\\s+TO\\s+(\\w+)", std::regex_constants::icase);
    std::regex revokePermissionRegex("REVOKE\\s+(SELECT|INSERT|DELETE|UPDATE|ALL)\\s+ON\\s+(\\w+)\\s+FROM\\s+(\\w+)", std::regex_constants::icase);

    //13：查询功能
    std::regex searchRecord("SELECT\\s+(.+)\\s+FROM\\s+(.+)(\\s+WHERE\\s(.+))?", std::regex_constants::icase);


    // 初始化用户目录，读取当前的用户和所使用的数据库
    //为了满足不同的电脑路径不同
    QDir *dir = new QDir(QDir::currentPath());
    dir->cdUp();


    //----------------后期需要修改-------------------------
    //是根据不同用户吗还是根据不同的数据库
    //QString dirPath = dir->path() + "/DBMS/data/sys/curuse.txt";
    //qDebug() << dir->path();


    std::smatch match;

    //创建数据库
    if (std::regex_search(readmess, match, createdatabase)) {
        QString dbname=QString::fromStdString(match[1]);
        class createdatabase* myDatabase = new class createdatabase();
        myDatabase->createonedata(dbname);
        ui->readline_2->append("----------------------分割线----------------------");
        ui->readline_2->append(ui->readline->toPlainText());
        ui->readline->setText("");

    }
    //删除数据库
    else if(std::regex_search(readmess, match, dropdatabase)){
        QString dbname=QString::fromStdString(match[1]);
        class dropdatabase* myDatabase = new class dropdatabase();
        myDatabase->droponedata(dbname);
        ui->readline_2->append("----------------------分割线----------------------");
        ui->readline_2->append(ui->readline->toPlainText());
        ui->readline->setText("");

    }

    //whx部分创建表
    else if(std::regex_search(readmess, match, createTable)){
        if(dname==""){
            QMessageBox::information(nullptr, "Warning", "请先使用use语句指定database");
            ui->readline_2->append("----------------------分割线----------------------");
            ui->readline_2->append(ui->readline->toPlainText());
            ui->readline->clear();
            return ;
        }
        // 提取匹配的部分
        QString tableName =QString::fromStdString(match[1]);
        QString folderPath = dir->path()+ "/DBMS/data"+ "/" + dname+ "/" +tableName;

        QDir dir2(folderPath);
        if (dir2.exists()) {
                QMessageBox::information(nullptr, "Warning", "已创建该表");
                ui->readline_2->append("----------------------分割线----------------------");
                ui->readline_2->append(ui->readline->toPlainText());
                ui->readline->clear();
                qDebug() << "Folder exists.";
                return;
        }
                    QString columnDefinitions =QString::fromStdString(match[2]);
                    class createtable* myDatabase = new class createtable();
                    myDatabase->init(dname,tableName,columnDefinitions);
                    ui->readline_2->append("----------------------分割线----------------------");
                    ui->readline_2->append(ui->readline->toPlainText());
                    ui->readline->setText("");
    }
    //识别数据库
    else if(std::regex_search(readmess, match, useDatabaseRegex)){
                QString tempdname = QString::fromStdString(match[1]);
                dname=tempdname;
                QString dirPath = dir->path() + "/DBMS/User"+ "/" + username+"/Permission.txt";
                // 打开文件进行读取
                std::ifstream inFile(dirPath.toStdString());
                if (!inFile.is_open()) {
                    std::cerr << "无法打开文件：" << dirPath.toStdString() << std::endl;
                    QMessageBox::information(nullptr, "Warning", "您登录的用户没有数据库操作权限！");
                    ui->readline_2->append("----------------------分割线----------------------");
                    ui->readline_2->append(ui->readline->toPlainText());
                    ui->readline->setText("");
                } else {
                    std::string line;
                    bool found = false;

                    // 逐行读取文件内容并检查是否包含 tempdname
                    while (std::getline(inFile, line)) {
                        QString lineStr = QString::fromStdString(line);

                        // 进行匹配
                        if (lineStr.split(" ").at(0)==tempdname) {
                            // 找到匹配，设置标志并跳出循环
                            found = true;
                            break;
                        }
                    }

                    // 关闭文件
                    inFile.close();

                    // 根据匹配结果输出信息
                    if (found) {
                        QMessageBox::information(nullptr, "Warning", "切换到数据库"+dname);
                        std::cout << "文件中包含目标字符串" << std::endl;
                        qDebug()<<dname<<endl;
                        ui->readline_2->append("----------------------分割线----------------------");
                        ui->readline_2->append(ui->readline->toPlainText());
                        ui->readline->setText("");
                    } else {
                        QMessageBox::information(nullptr, "Warning", "没有该数据库权限！");
                        std::cout << "文件中未找到目标字符串" << std::endl;
                        ui->readline_2->append("----------------------分割线----------------------");
                        ui->readline_2->append(ui->readline->toPlainText());
                        ui->readline->setText("");
                    }

               }
    }
    //删除table
    else if(std::regex_search(readmess, match, dropTableRegex)){
        if(dname==""){
            QMessageBox::information(nullptr, "Warning", "请先使用use语句指定database");
            ui->readline_2->append("----------------------分割线----------------------");
            ui->readline_2->append(ui->readline->toPlainText());
            ui->readline->clear();
            return ;
        }
        // 提取匹配的部分
        QString tableName =QString::fromStdString(match[1]);
        QString folderPath = dir->path()+ "/DBMS/data"+ "/" + dname+ "/" +tableName;

        QDir dir2(folderPath);
        if (!dir2.exists()) {
                QMessageBox::information(nullptr, "Warning", "无该表删除失败");
                ui->readline_2->append("----------------------分割线----------------------");
                ui->readline_2->append(ui->readline->toPlainText());
                ui->readline->clear();
                qDebug() << "Folder does not exist.";
                return;
        }
            QString tablename = QString::fromStdString(match[1]);
            class droptable* dtable = new class droptable();
            dtable->drop(tablename,dname);
            ui->readline_2->append("----------------------分割线----------------------");
            ui->readline_2->append(ui->readline->toPlainText());
            ui->readline->setText("");

}
    //修改table
    else if(std::regex_search(readmess, match, alterTableRegex)){
        if(dname==""){
            QMessageBox::information(nullptr, "Warning", "请先使用use语句指定database");
            ui->readline_2->append("----------------------分割线----------------------");
            ui->readline_2->append(ui->readline->toPlainText());
            ui->readline->clear();
            return ;
        }
               QString tableName = QString::fromStdString(match[1]);
               string operation = match[2];
               string objectName = match[3];
               string objectName2 = match[4];
               string objectType2 = match[5];//(可能为空)
               QDir *dir = new QDir(QDir::currentPath());
               dir->cdUp();
           //    QString dname = QString::fromStdString(dbName);
           //    QString name = QString::fromStdString(tableName);
               QString dirPath = dir->path() + "/DBMS/data"+ "/" + dname+ "/" +tableName+"/" +tableName+".txt";
               string filename = dirPath.toStdString();
               class altertable *atable = new class altertable();
               atable->alter(filename,operation,objectName,objectName2,objectType2);
               ui->readline_2->append("----------------------分割线----------------------");
               ui->readline_2->append(ui->readline->toPlainText());
               ui->readline->setText("");


     }
    // Insert Record
    else if(std::regex_search(readmess, match, insertRecordRegex)) {
        if(dname.isEmpty()) {
            QMessageBox::information(nullptr, "Warning", "请先使用USE语句指定数据库");
            ui->readline_2->append("----------------------分割线----------------------");
            ui->readline_2->append(ui->readline->toPlainText());
            ui->readline->clear();
            return;
        }

        QString permissionPath = dir->path() + "/DBMS/User/"+ username + "/Permission.txt";
           std::ifstream permissionFile(permissionPath.toStdString());
           bool hasPermission = false;
           if (permissionFile.is_open()) {
               std::string line;
               while (std::getline(permissionFile, line)) {
                   QString lineStr = QString::fromStdString(line);
                   if (lineStr.split(" ").at(0) == dname && (lineStr.split(" ").at(1) == "INSERT"||lineStr.split(" ").at(1) == "insert"||lineStr.split(" ").at(1) == "all")) {
                       hasPermission = true;
                       break;
                   }
               }
               permissionFile.close();
           }

           if (!hasPermission) {
               QMessageBox::information(nullptr, "Warning", "您没有向该数据库插入记录的权限！");
               ui->readline_2->append("----------------------分割线----------------------");
               ui->readline_2->append(ui->readline->toPlainText());
               ui->readline->clear();
               return;
           }


        QString tableName = QString::fromStdString(match[1]);
        QString columnNames = QString::fromStdString(match[2]);
        QString values = QString::fromStdString(match[3]);

        // Split column names and values
        QStringList columnList = columnNames.split(",", QString::SkipEmptyParts);
        QStringList valueList = values.split(",", QString::SkipEmptyParts);

        // Check if the number of columns matches the number of values
        if (columnList.size() != valueList.size()) {
            QMessageBox::information(nullptr, "Warning", "插入的列数和值的数量不匹配");
            return;
        }

        // Trim column names and values
        for (int i = 0; i < columnList.size(); ++i) {
            columnList[i] = columnList[i].trimmed();
            valueList[i] = valueList[i].trimmed();
        }

        // Perform the insertion
        class insertrecord* myDatabase = new class insertrecord();
        myDatabase->insert(dname, tableName, columnList, valueList);
        ui->readline_2->append("----------------------分割线----------------------");
        ui->readline_2->append(ui->readline->toPlainText());
        ui->readline->clear();
    }

    // 删除记录
    else if(std::regex_search(readmess, match, deleteRecord)) {
        if(dname.isEmpty()) {
            QMessageBox::information(nullptr, "Warning", "请先使用USE语句指定数据库");
            ui->readline_2->append("----------------------分割线----------------------");
            ui->readline_2->append(ui->readline->toPlainText());
            ui->readline->clear();
            return;
        }
        QString permissionPath = dir->path() + "/DBMS/User/"+ username + "/Permission.txt";
           std::ifstream permissionFile(permissionPath.toStdString());
           bool hasPermission = false;
           if (permissionFile.is_open()) {
               std::string line;
               while (std::getline(permissionFile, line)) {
                   QString lineStr = QString::fromStdString(line);
                   if (lineStr.split(" ").at(0) == dname && (lineStr.split(" ").at(1) == "DELETE"||lineStr.split(" ").at(1) == "delete"||lineStr.split(" ").at(1) == "all")) {
                       hasPermission = true;
                       break;
                   }
               }
               permissionFile.close();
           }

           if (!hasPermission) {
               QMessageBox::information(nullptr, "Warning", "您没有向该数据库插入记录的权限！");
               ui->readline_2->append("----------------------分割线----------------------");
               ui->readline_2->append(ui->readline->toPlainText());
               ui->readline->clear();
               return;
           }

        QString tableName = QString::fromStdString(match[1]);
        QString whereClause = QString::fromStdString(match[2]);

        // Perform the deletion
        class droprecord* myDatabase = new class droprecord();
        myDatabase->deleteFrom(dname, tableName, whereClause);

        ui->readline_2->append("----------------------分割线----------------------");
        ui->readline_2->append(ui->readline->toPlainText());
        ui->readline->clear();
    }

    // 修改记录
    else if (std::regex_search(readmess, match, modifyRecord)) {
        if (dname.isEmpty()) {
            QMessageBox::information(nullptr, "Warning", "请先使用USE语句指定数据库");
            ui->readline_2->append("----------------------分割线----------------------");
            ui->readline_2->append(ui->readline->toPlainText());
            ui->readline->clear();
            return;
        }

        QString permissionPath = dir->path() + "/DBMS/User/"+ username + "/Permission.txt";
           std::ifstream permissionFile(permissionPath.toStdString());
           bool hasPermission = false;
           if (permissionFile.is_open()) {
               std::string line;
               while (std::getline(permissionFile, line)) {
                   QString lineStr = QString::fromStdString(line);
                   if (lineStr.split(" ").at(0) == dname && (lineStr.split(" ").at(1) == "UPDATE"||lineStr.split(" ").at(1) == "update"||lineStr.split(" ").at(1) == "all")) {
                       hasPermission = true;
                       break;
                   }
               }
               permissionFile.close();
           }

           if (!hasPermission) {
               QMessageBox::information(nullptr, "Warning", "您没有向该数据库插入记录的权限！");
               ui->readline_2->append("----------------------分割线----------------------");
               ui->readline_2->append(ui->readline->toPlainText());
               ui->readline->clear();
               return;
           }

        QString tableName = QString::fromStdString(match[1]);
        QString setClause = QString::fromStdString(match[2]);
        QString whereClause = QString::fromStdString(match[3]);

        // Perform the modification
        class modifyrecord* myDatabase = new class modifyrecord();
        myDatabase->modify(dname, tableName, setClause, whereClause);

        ui->readline_2->append("----------------------分割线----------------------");
        ui->readline_2->append(ui->readline->toPlainText());
        ui->readline->clear();
    }
    //权限授予
    else if(std::regex_search(readmess, match, grantPermissionRegex)){
        QString type=QString::fromStdString(match[1]);
        QString dbName = QString::fromStdString(match[2]);
        QString userName = QString::fromStdString(match[3]);


        //创建存放权限的文件
        QString usernamePath = dir->path() + "/DBMS/User/"+userName;
        QString dbnamePath = dir->path() + "/DBMS/data/"+dbName;

        QDir dir1(usernamePath);
        QDir dir2(dbnamePath);
            if (!dir1.exists()||!dir2.exists()) {
                QMessageBox::information(nullptr, "Warning", "没有该数据库或者用户名");
                qDebug() << "文件夹不存在";
                ui->readline_2->append("----------------------分割线----------------------");
                ui->readline_2->append(ui->readline->toPlainText());
                ui->readline->setText("");
                return;
            } else {
                qDebug() << "文件夹存在";
            }


        QString usernamegrantPath = dir->path() + "/DBMS/User/"+username+"/Permission.txt";
        // 创建一个的文件并打开它，使用 std::ios::app 标志来追加写入数据
        std::ofstream outFile(usernamegrantPath.toStdString(), std::ios::app);

        // 检查文件是否成功打开
        if (outFile.is_open()) {
            // 将数据逐行写入文件
            outFile << dbName.toStdString()<<" "<<type.toStdString()<<endl;
            // 关闭文件
            outFile.close();
            qDebug()<< "数据追加成功。\n";
        } else {
            qDebug() << "无法打开文件。\n";
        }
        QMessageBox::information(nullptr, "Warning", "权限授予成功");
        ui->readline_2->append("----------------------分割线----------------------");
        ui->readline_2->append(ui->readline->toPlainText());
        ui->readline->clear();


    }

    //回收权限
    else if(std::regex_search(readmess, match, revokePermissionRegex)){
        QString type= QString::fromStdString(match[1]);
        QString dbName = QString::fromStdString(match[2]);
        QString userName = QString::fromStdString(match[3]);

        QString usernamegrantPath = dir->path() + "/DBMS/User/"+userName+"/Permission.txt";
        QString tempFilePath = dir->path() + "/DBMS/User/"+userName+"/temp.txt"; // 临时文件路径

        // 打开原文件进行读取
        std::ifstream inFile(usernamegrantPath.toStdString());
        if (!inFile.is_open()) {
            qDebug() << "无法打开文件：" <<endl;
            QMessageBox::information(nullptr, "Warning", "该用户无数据库操作权限！");
            ui->readline_2->append("----------------------分割线----------------------");
            ui->readline_2->append(ui->readline->toPlainText());
            ui->readline->setText("");
        } else {
            std::string line;
            bool found = false;

            // 创建临时文件
            std::ofstream tempFile(tempFilePath.toStdString(), std::ios::app);

            // 逐行读取原文件内容并匹配
            while (std::getline(inFile, line)) {
                QString lineStr = QString::fromStdString(line);

                // 进行匹配
                if (((lineStr.split(" ").at(1)!=type&&lineStr.split(" ").at(1)!="all") || lineStr.split(" ").at(1)!="all")||lineStr.split(" ").at(0)!=dbName) {
                    // 将非匹配成功的行写入临时文件
                    tempFile << line << std::endl;
                    qDebug()<<type<<lineStr.split(" ").at(1)<<endl;
                } else {
                    // 找到匹配，设置标志
                    if(lineStr.split(" ").at(1)=="all"&&type!="all"){
                        QStringList lists;
                        lists<<"select"<<"update"<<"delete"<<"insert";
                        for(int i=0;i<4;i++){
                            if(lists[i]!=type) {
                                line=dbName.toStdString()+" "+lists.at(i).toStdString();
                                tempFile<<line<<std::endl;
                            }
                        }
                    }
                    found = true;
                }
            }

            // 关闭文件
            inFile.close();
            tempFile.close();

            // 根据匹配结果输出信息
            if (found) {
                qDebug() << "匹配成功，已删除该行" << endl;
                QMessageBox::information(nullptr, "OK！", "回收权限成功");

                // 删除原文件
                QFile::remove(usernamegrantPath);

                // 将临时文件重命名为原文件
                QFile::rename(tempFilePath, usernamegrantPath);
            } else {
                qDebug() << "未找到匹配" << endl;
                QMessageBox::information(nullptr, "Warning", "回收权限失败，该用户没有该数据库操作权限!");
                // 删除临时文件
                QFile::remove(tempFilePath);

            }
        ui->readline_2->append("----------------------分割线----------------------");
        ui->readline_2->append(ui->readline->toPlainText());
        ui->readline->clear();

    }

}
    // 查询记录
       else if (std::regex_search(readmess, match, searchRecord))
       {
           if (dname.isEmpty()) {
               QMessageBox::information(nullptr, "Warning", "请先使用USE语句指定数据库");
               return;
           }
           QMessageBox::information(nullptr, "success", "查询成功");
           // 要查询的属性名
           QString attrList = QString::fromStdString(match[1]).trimmed();
           // 要查询的列名
           QString tableList = QString::fromStdString(match[2]).replace(";", "").trimmed();
           // 查询条件
           QString whereClause = QString::fromStdString(match[3]);

           whereClause.replace("WHERE", "").replace(";", "");

           whereClause = whereClause.trimmed();

           SearchRecord* MyDatabase = new SearchRecord;

           ui->readline_2->append("----------------------分割线----------------------");
           ui->readline_2->append(ui->readline->toPlainText());
           ui->readline->clear();

           MyDatabase->selectFunction(ui->readline_2, dname, attrList, tableList, whereClause);
       }



    else {
       //当所有的SQL语句不匹配的时候
        ui->readline_2->append("----------------------分割线----------------------");
        ui->readline_2->append(ui->readline->toPlainText());
        ui->readline->setText("");
        QMessageBox::information(nullptr, "Warning", "您的SQL语句有误请重新输入");
        ui->readline_2->append("您的SQL语句有误请重新输入");
    }
}



void UserInterface::on_GO_2_clicked()
{
    // 打开文件选择对话框
           QString filePath = QFileDialog::getOpenFileName(nullptr, "选择文件", QDir::homePath(), "All Files (*.*)");
           // 如果用户选择了文件，则打印文件路径
           if (filePath.isEmpty()) {
                   qDebug() << "未选择文件";
                   return ;
               }
               // 打开文件
               QFile file(filePath);
               if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                   qDebug() << "无法打开文件：" << file.errorString();
                   return ;
               }
               // 读取文件内容
               QTextStream in(&file);
               QStringList dataList;
               QString temp="";
               while (!in.atEnd()) {
                   QString line = in.readLine().trimmed(); // 去除首尾空白
                   if (!line.isEmpty()) {
                       temp=temp+line;
                       if (line.endsWith(";")) {
                           dataList.append(temp);
                           temp="";
                           //qDebug() << "字符串结尾是分号";
                       }
                       //dataList.append(line);
                   }
               }

               // 关闭文件
               file.close();

               // 将文件内容按分号分隔存储到QStringList中
               //QStringList dataList = fileContent.split(";", QString::SkipEmptyParts);

               // 输出分隔后的数据
               //qDebug() << "读取到的数据：" << dataList;
               for (int i = 0; i < dataList.size(); ++i) {
                   QString temp=dataList.at(i).trimmed(); // trimmed()函数用于移除字符串两端的空白字符
                   openFile(temp);

               }



}
void UserInterface::openFile(QString text){
    //执行语句
    ui->readline->setText(text);
    emit on_GO_clicked();


}
void UserInterface::receiveData(const QString &data)
{
    // 在 username 中显示接收到的数据
    username=data;
   //qDebug() <<username+";;;"<<endl;
}
void UserInterface::writelog(QString username,QString operation,QString date){
    QDir *dir = new QDir(QDir::currentPath());
    dir->cdUp();

    QString logFilePath = dir->path() + "/DBMS/log/log.txt";
    // 打开文件进行追加写入
        QFile file(logFilePath);
        if (!file.open(QIODevice::Append | QIODevice::Text)) {
            qDebug() << "无法打开文件：" << logFilePath;
            return;
        }

        // 使用 QTextStream 来写入文件内容
        QTextStream out(&file);
        out << username << "||" << operation << "||"  << date << endl;

        // 关闭文件
        file.close();
}
