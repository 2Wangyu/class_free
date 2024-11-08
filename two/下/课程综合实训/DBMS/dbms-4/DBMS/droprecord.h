#ifndef DROPRECORD_H
#define DROPRECORD_H

#include <fstream>
#include <iostream>
#include <QString>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include<QDebug>

using namespace std;
class droprecord {
public:
    droprecord();

    bool valueExists(const QString& filePath, const QString& targetKey) {
        currentrow=1;

        // Open the file for reading
            QFile file(filePath);
            if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                return false; // Failed to open file
            }

            QTextStream in(&file);
            while (!in.atEnd()) {
                QString line = in.readLine();
                QString firstColumnValue = line.split(" ").at(0); //space is the separator
                if (firstColumnValue == targetKey) {
                    file.close();
                    return true;
                }
                currentrow++;
            }

            file.close();
            return false;
    }

    void deleteFrom(const QString& dbName, const QString& tableName, const QString& whereClause) {
        QDir dir(QDir::currentPath());
        dir.cdUp();
        QString filePathForCheck = dir.path() + "/DBMS/data/" + dbName + "/" + tableName+"/"+tableName + ".txt";
        QString filePath = dir.path() + "/DBMS/data/" + dbName + "/" + tableName+"/"+tableName + "_record.txt";

        // Open the file for reading
        //delete from student where id=1
        cout<<"drop:"+filePath.toStdString()<<endl;

        //做属性存在检验

        QString key = whereClause.section("=", 0, 0,QString::SectionSkipEmpty).trimmed();
        QString value=whereClause.section("=", 1, 1).trimmed();


        if (valueExists(filePathForCheck, key)) {
            qDebug()<<"row "<<currentrow<<endl;
            // Delete records based on where clause
            QFile file(filePath);
            if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
                QMessageBox::critical(nullptr, "Error", "Failed to open record file for read/write deletion");
                return;
            }
            QTextStream in(&file);
            QStringList lines;

            while(!in.atEnd()){
                QString line=in.readLine();
                QString ColumnValue = line.split(" ").at(currentrow-1); //space is the separator
                qDebug()<<line<<endl;
                qDebug()<<ColumnValue<<endl;
                if (ColumnValue == value) {
                    //file.close();
                    continue;
                }else{
                    lines.append(line);
                }

            }
            file.resize(0); // Clear the file content
            QTextStream out(&file);
            for (const QString& line : lines) {
                out << line << endl;
            }
            file.close();
            QMessageBox::information(nullptr, "Success", "Records deleted successfully");

         } else {
                // 目标值不存在，给出相应的提示或处理
                QMessageBox::warning(nullptr, "Error", "key does not exist in the file.");
         }

        //qDebug()<<content<<endl;





    }
private:
    int currentrow=1;
};


#endif // DROPRECORD_H
