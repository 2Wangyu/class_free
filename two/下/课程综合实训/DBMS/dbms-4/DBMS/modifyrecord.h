#ifndef MODIFYRECORD_H
#define MODIFYRECORD_H

#include <fstream>
#include <iostream>
#include <QString>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <qregularexpression.h>
#include <QMessageBox>

using namespace std;

class modifyrecord {
public:
    modifyrecord();
    bool valueExists(const QString& filePath, const QString& targetKey1,int &currentrow) {
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
                if (firstColumnValue == targetKey1) {
                    file.close();
                    return true;
                }
                currentrow++;
            }

            file.close();
            return false;
    }

    void modify(const QString& dbName, const QString& tableName, const QString& setClause, const QString& whereClause) {
        QDir dir(QDir::currentPath());
        dir.cdUp();
        QString filePath = dir.path() + "/DBMS/data/" + dbName + "/" + tableName +"/"+tableName+ "_record.txt";
        QString filePathForCheck = dir.path() + "/DBMS/data/" + dbName + "/" + tableName +"/"+tableName+ ".txt";


        // Open the file for reading
        //delete from student where id=1
        cout<<filePath.toStdString()<<endl;

        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::critical(nullptr, "Error", "Failed to open table file for read deletion");
            return;
        }

        QTextStream in(&file);
        QString content = in.readAll();
        file.close();

        // Open the file for writing
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::critical(nullptr, "Error", "Failed to open table file for write deletion");
            return;
        }

        //需要改进
        QTextStream out(&file);
        QString key=whereClause.section("=", 0, 0,QString::SectionSkipEmpty).trimmed();
        QString value=whereClause.section("=", 1, 1,QString::SectionSkipEmpty).trimmed();

        QString new_key=setClause.section("=", 0, 0,QString::SectionSkipEmpty).trimmed();
        QString new_val=setClause.section("=", 1, 1,QString::SectionSkipEmpty).trimmed();

        if(!valueExists(filePathForCheck,key,oldcurrentrow)||!valueExists(filePathForCheck,new_key,newcurrentrow)){
            QMessageBox::warning(nullptr, "Error", "key does not exist in the file.");
            return;
        }
        QStringList lines = content.split("\n", QString::SkipEmptyParts);
                for (const QString& line : lines) {
                    QStringList columns = line.split(" ", QString::SkipEmptyParts);
                    if (columns.size() >= oldcurrentrow) {
                        if (columns[oldcurrentrow - 1] == value) {
                            columns.replace(newcurrentrow - 1, new_val);
                        }
                    }
                    out << columns.join(" ") << endl;
                }

          file.close();
          QMessageBox::information(nullptr, "Success", "Records modified successfully");


//        QDir dir(QDir::currentPath());
//        dir.cdUp();
//        QString filePath = dir.path() + "/DBMS/data/" + dbName + "/" + tableName + "_record.txt";

//        // Open the file for reading
//        QFile file(filePath);
//        if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
//            QMessageBox::critical(nullptr, "Error", "Failed to open table file for read modification");
//            return;
//        }

//        QTextStream in(&file);
//        QString content = in.readAll();
//        file.close();

//        // Open the file for writing
//        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
//            QMessageBox::critical(nullptr, "Error", "Failed to open table file for write modification");
//            return;
//        }

//        QTextStream out(&file);

//        // Construct regex pattern for where clause
//        QString value = whereClause.section("=", 1, 1).trimmed();
//        QString pattern = "\\b" + value + "\\b";

//        // Split set clause into individual assignments
//        QStringList assignments = setClause.split(",", QString::SkipEmptyParts);

//        // Split each assignment into field name and new value
//        for (const QString& assignment : assignments) {
//            QStringList parts = assignment.split("=", QString::SkipEmptyParts);
//            if (parts.size() != 2) {
//                QMessageBox::critical(nullptr, "Error", "Invalid set clause: " + assignment);
//                return;
//            }

//            QString fieldName = parts[0].trimmed();
//            QString newValue = parts[1].trimmed();

//            // Construct regex pattern for field name
//            QString fieldPattern = "\\b" + fieldName + "\\b";

//            // Replace matching field value with new value
//            content.replace(QRegularExpression(fieldPattern), newValue);
//        }

//        // Write modified content back to file
//        out << content;
//        file.close();

//        QMessageBox::information(nullptr, "Success", "Records modified successfully");
    }
private:
    int oldcurrentrow;
    int newcurrentrow;
};

#endif // MODIFYRECORD_H

