#include "insertrecord.h"
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
using namespace std;
/*
 *
 * USE database yyy
----------------------分割线----------------------
INSERT INTO students (id) VALUES (1)
 */

insertrecord::insertrecord()
{

}

void insertrecord::insert(QString dbName, QString tableName, const QStringList &columnNames, const QStringList &values)
{
          QDir *dir = new QDir(QDir::currentPath());
          dir->cdUp();
          QString filePath = dir->path() + "/DBMS/data/" + dbName + "/" + tableName+"/"+tableName + ".txt";

          // Read column names and types from the table file
          cout<<filePath.toStdString()<<endl;
          std::ifstream file(filePath.toStdString());
          if (!file.is_open()) {
              cout<<filePath.toStdString()<<endl;
              QMessageBox::critical(nullptr, "Error", "Failed to open table file for read insertion");
              return;
          }

          std::vector<std::pair<std::string, std::string>> columns; // Store column names and types

          std::string columnName, columnType;
          while (file >> columnName >> columnType) {
              columns.push_back(std::make_pair(columnName, columnType));
          }
          file.close();

          // Check if the number of column names and values matches the number of columns in the table
          if (columnNames.size() != values.size() || columnNames.size() != columns.size()) {
              QMessageBox::critical(nullptr, "Error", "Column names, values, or column count mismatch");
              return;
          }

          // Check if the column names in the values match the column names in the table
          for (int i = 0; i < columnNames.size(); ++i) {
              if (columnNames[i] != QString::fromStdString(columns[i].first)) {
                  QMessageBox::critical(nullptr, "Error", "Column name mismatch: " + columnNames[i]);
                  return;
              }
              if (!checkDataType(values[i], columns[i].second)) {
                  QMessageBox::critical(nullptr, "Error", "Data type mismatch for column: " + columnNames[i]);
                  return;
              }
          }

          // Insert record
          dir->cdUp();
          filePath = dir->path() + "/dbms-4/DBMS/data/" + dbName + "/" + tableName +"/"+tableName+ "_record" + ".txt";

          std::ofstream outFile(filePath.toStdString(), std::ios_base::app);
          if (!outFile.is_open()) {
              cout<<filePath.toStdString()<<endl;
              QMessageBox::critical(nullptr, "Error", "Failed to open table file for write insertion");
              return;
          }

          // Write values to the file
          for (int i = 0; i < values.size(); ++i) {
              outFile << values[i].toStdString();
              if (i < values.size() - 1) {
                  outFile << " ";
              }
          }
          outFile << std::endl;
          outFile.close();

          QMessageBox::information(nullptr, "Success", "Record inserted successfully");
}
