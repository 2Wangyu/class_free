#include "altertable.h"
#include"QMessageBox"

altertable::altertable(){

}

void altertable::alter(const string& filename, const string& operation, const string& oldColumnName, const string& newColumnName, const string& newColumnType) {


    // 打开文件
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cerr << "Error: Unable to open file." << endl;
        QMessageBox::information(nullptr, "Warning", "没有该表！");
        return;
    }

    // 读取文件内容到内存中
    vector<pair<string, string>> columns; // 存储列名和数据类型的向量数组
    string line;
    while (getline(inputFile, line)) {
        // 解析行，提取列名和数据类型
        regex columnRegex("(\\w+)\\s+(\\w+(?:\\(\\d+\\))?)");
        smatch matches;
        if (regex_match(line, matches, columnRegex)) {
            // 提取匹配的部分
            string columnName = matches[1];
            string columnType = matches[2];
            columns.push_back(make_pair(columnName, columnType));
        }
    }
    inputFile.close();

    // 修改表结构
    // add 列名，类型
    if (operation == "ADD"||operation == "add") {
        //检查增加的是否已经存在
        for (auto it = columns.begin(); it != columns.end(); ++it) {
            if (it->first == oldColumnName) {
                QMessageBox::information(nullptr, "Warning", "该列已经存在，add失败！");
                return ;
            }
        }
        // 添加新列
        columns.push_back(make_pair(oldColumnName, newColumnName));
    } else if (operation == "DROP"||operation == "drop") {
        // 删除列
        //drop 列名
        bool flag=false;
        for (auto it = columns.begin(); it != columns.end(); ++it) {
            if (it->first == oldColumnName) {
                columns.erase(it);
                flag=true;
                break;
            }
        }
        if(flag==false){
            QMessageBox::information(nullptr, "Warning", "没有该列，drop失败！");
            return;
        }


    } else if (operation == "MODIFY"|| operation == "modify") {
        // 修改列数据类型或列名
        //modify 列名 新列名 类型
        for (auto& column : columns) {
            if (column.first == oldColumnName) {
                if (!newColumnName.empty()) {
                    column.first = newColumnName;
                }
                if (!newColumnType.empty()) {
                    column.second = newColumnType;
                }
                break;
            }
        }
    }
    // 可以根据需要添加更多的操作

    // 覆盖原文件
    ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        QMessageBox::information(nullptr, "Warning", "修改表失败！");
        cerr << "Error: Unable to open file for writing." << endl;
        return;
    }else {
    for (const auto& column : columns) {

        outputFile << column.first << " " << column.second << endl;
    }
    outputFile.close();
    QMessageBox::information(nullptr, "！！！", "修改成功");

    cout << "Table modified successfully." << endl;
    }
}
