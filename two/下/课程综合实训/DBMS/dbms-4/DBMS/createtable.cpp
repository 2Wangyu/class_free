#include "createtable.h"

createtable::createtable()
{

}

void createtable::init(QString dbName, QString tableName,QString columnDefinitions){
    std::cout << columnDefinitions.toStdString() << endl;
    QDir *dir = new QDir(QDir::currentPath());
    dir->cdUp();

    //创建数据库文件夹
    // 创建QDir对象
    QDir newdir;
    // 定义你想要创建的文件夹的路径
    QString directoryPath = dir->path() + "/DBMS/data/"+dbName+"/"+tableName;
    // 使用mkdir方法创建文件夹
    // 如果需要创建多级目录，可以传递true作为第二个参数
    bool result = newdir.mkdir(directoryPath); // true 表示如果上级目录不存在也创建
    if (result) {
        qDebug() << "文件夹创建成功：" << directoryPath;
    }
    else {
        qDebug() << "文件夹创建失败：" << directoryPath;
    }



    QString dirPath = dir->path() + "/DBMS/data"+ "/" + dbName+ "/" +tableName+"/" +tableName+".txt";
    // 使用字符串流来分割 columnDefinitions
           string c = columnDefinitions.toStdString();
           stringstream ss(c);
           vector<pair<string, string>> columns; // 用 pair<string, string> 表示列名和数据类型

           string column;
           while (getline(ss, column, ',')) {
               stringstream columnSS(column);
               string columnName, columnType;
               columnSS >> columnName >> columnType;
               columns.push_back(make_pair(columnName, columnType));
           }

        //qDebug() << dir->path();
    //string filePath = db_folder + "/" + dbName + "/" + tableName + ".txt";
           string path = dirPath.toStdString();
           cout<<path;
           ofstream file(path);
           if (file.is_open()) {
               // 写入列名
               for (auto& column : columns) {
                    file << column.first <<" "<<column.second << endl;
                          }
               file.close();
                QMessageBox::information(nullptr, "！！！", "创建成功！");
               //cout << "Table '" +tableName+ "' created successfully." << endl;
           } else {
               QMessageBox::information(nullptr, "", "创建失败！");
               cout << "Error: Unable to create table." << endl;
          }
}
