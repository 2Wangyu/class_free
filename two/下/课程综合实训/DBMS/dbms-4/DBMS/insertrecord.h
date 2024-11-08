#ifndef INSERTRECORD_H
#define INSERTRECORD_H
#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <vector>
#include<QString>
class insertrecord
{
public:
    insertrecord();
    void insert(QString dbName, QString tableName, const QStringList& columnNames, const QStringList& values);
private:
    bool checkDataType(const QString& value, const std::string& columnType) {

        // Example: Check if the column type is "int" and the value can be converted to an integer
        if (columnType == "int" || columnType=="INT") {
            bool ok;
            value.toInt(&ok);
            return ok;
        }

        else if (columnType == "varchar"||columnType=="char") {

            return true;
        }

        // Unknown data type
        return false;
    }
};


#endif // INSERTRECORD_H
