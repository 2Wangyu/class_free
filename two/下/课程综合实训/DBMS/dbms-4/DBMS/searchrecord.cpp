#include "searchrecord.h"
#include <QDebug>
#define INT "int"
#define NUMBER "number"
#define VARCHAR "varchar"

SearchRecord::SearchRecord()
{

}


void SearchRecord::selectFunction(QTextEdit* textEdit,const QString& dbName, const QString& attrList, const QString& tableList, const QString& whereClause)
{
    QStringList attrs;
    bool isSELECTStar;
    // 将传入的QString分割为QStringList
    if(attrList == "*")
    {
        isSELECTStar = true;
    }
    else
    {
        isSELECTStar = false;
        attrs = attrList.split(",", QString::SkipEmptyParts);
    }
    QStringList attr_type;
    QStringList tables = tableList.split(",", QString::SkipEmptyParts);
    std::string where_clause_std = whereClause.toStdString();

    int reg_type;
    QString compare_attr_table;
    QString compare_attr;
    int compare_attr_index;
    QString compare_operator;
    QString compare_value;

    QStringList tableScheme;
    QList<int> attr_index_list;

    // 关于where clause的正则化表达式
    // 1. 空字符串，及没有where
    std::regex clause_type_0("^$");
    // 2. 单表查询：WHERE 属性 >|=|< 数字值（int） 的条件
    std::regex clause_type_1("(\\w+)\\s*([<=>]+)\\s*(.+)\\s*");
    // 3. 多表查询
    std::regex clause_type_3("(\\w+)([\\.])(\\w+)\\s*([<=>]+)\\s*(.+)\\s*");

    std::smatch match;
    // 解析where clause
    if(std::regex_match(where_clause_std, match, clause_type_0))
    {
        reg_type = 0;
    }
    else if(std::regex_match(where_clause_std, match, clause_type_1))
    {
        compare_attr = QString::fromStdString(match[1]);
        compare_operator = QString::fromStdString(match[2]);
        compare_value = QString::fromStdString(match[3]);
        reg_type = 1;
    }
    else if(std::regex_match(where_clause_std, match, clause_type_3))
    {
        compare_attr_table = QString::fromStdString(match[1]);
        compare_attr = QString::fromStdString(match[3]);
        compare_operator = QString::fromStdString(match[4]);
        compare_value = QString::fromStdString(match[5]);
        reg_type = 3;
    }
    // 不合法条件
    else
    {
        QMessageBox::critical(nullptr, "ERROR", "Illigal Condition In Where Clause");
        return;
    }

    QDir dir(QDir::currentPath());
    dir.cdUp();
    QString DBPath = dir.path() + "/DBMS/data/" + dbName;
    //将读取到的attrs中内容的空白除去
    for(int i = 0; i < attrs.length(); i++)
    {
        attrs[i] = attrs[i].trimmed();
    }

    //将读取到的tables中内容的空白除去
    for(int i = 0; i < tables.length(); i++)
    {
        tables[i] = tables[i].trimmed();
    }






    //先实现单表查询
    if(tables.length() == 1)
    {
        QString table_name = tables[0];
        QString table_path = DBPath + "/" + table_name +"/" + table_name + ".txt";
        QString record_path = DBPath + "/" + table_name + "/" + table_name+"_record.txt";

        QFile table_file(table_path);
        QFile record_file(record_path);

        if(!table_file.open(QIODevice::ReadOnly) || !record_file.open(QIODevice::ReadOnly))
        {
            QMessageBox::critical(nullptr, "Error", "Failed to open table files for selecting information");
        }

        QTextStream table_in(&table_file);
        QTextStream record_in(&record_file);
        // 读取表模式
        QString tempString;
        while(!table_in.atEnd())
        {
            // 读取字段名
            table_in >> tempString;
            // 防止读到最后一个空行但是没有内容
            if(tempString != "")
                tableScheme.append(tempString);
            // 读取类型
            table_in >> tempString;
            attr_type.append(tempString);
        }
        table_file.close();

        if(isSELECTStar)
        {
            attrs = tableScheme;
        }

        // 检查SELECT后的字段名是否合法，当SELECT*时不用判断该条件，因为上面直接使用tableScheme深拷贝给attrs
        if(!containAll(tableScheme, attrs))
        {
            textEdit->setText("Error:the attribute name in SELECT clause is not found in table scheme");
            return;
        }

        // 获取要查询的属性在表模式中的索引
        attr_index_list = get_index_list(tableScheme, attrs);

        // 输出表
        textEdit->append("查询结果\r\n");
        QTextCursor cursor = textEdit->textCursor();
        // 防止手动对游标进行更改，每次查询都更新游标到textedit最后面
        cursor.movePosition(QTextCursor::End);
        // 创建表对象
        // 插入一行用来展示表模式
        QTextTable* table = cursor.insertTable(1, attrs.length());
        // 输出表模式
        for(int i = 0; i < attrs.length(); i++)
        {
            QTextTableCell cell = table->cellAt(0, i);
            QTextCursor cell_cursor = cell.firstCursorPosition();
            cell_cursor.insertText(attrs[i]);
        }

        // 第一种正则化表达式的格式，也就是 attr compare_op value 的条件格式
        if(reg_type == 0)
        {
            int count = 1;
            QStringList lineElement;
            while(!record_in.atEnd())
            {
                lineElement = record_in.readLine().split(" ", QString::SkipEmptyParts);
                table->insertRows(count, 1);
                for(int i = 0; i < attr_index_list.size(); i++)
                {
                    QTextTableCell cell = table->cellAt(count, i);
                    QTextCursor cell_cursor = cell.firstCursorPosition();
                    cell_cursor.insertText(lineElement[attr_index_list[i]]);
                }
            }
        }
        else if(reg_type == 1)
        {
            compare_attr_index = tableScheme.indexOf(compare_attr);
            // 检查WHERE从句后的字段名是否合法
            if(compare_attr_index == -1)
            {
                textEdit->append("Error:attribute in where clause is not found in table scheme");
                return;
            }
            // 如果不存在这样的属性
            QStringList lineElement;
            // 计数变量，表示插入的元组数
            int count = 1;
            if(compare_operator == "=")
            {
                // 检查WHERE从句后的运算符是否支持该类型的属性进行比较
                if(attr_type[compare_attr_index] != INT && attr_type[compare_attr_index] != NUMBER && attr_type[compare_attr_index] != VARCHAR)
                {
                    textEdit->append("Error:attribute type in where clause dose not support the judge condition");
                    return;
                }
                while(!record_in.atEnd())
                {
                    lineElement = record_in.readLine().split(" ", QString::SkipEmptyParts);
                    if(lineElement[compare_attr_index] == compare_value)
                    {
                        table->insertRows(count, 1);
                        for(int i = 0; i < attr_index_list.length(); i++)
                        {
                            QTextTableCell cell = table->cellAt(count, i);
                            QTextCursor cell_cursor = cell.firstCursorPosition();
                            cell_cursor.insertText(lineElement[attr_index_list[i]]);
                        }
                        count++;
                    }
                }
            }
            else if(compare_operator == "<")
            {
                // 检查WHERE从句后的运算符是否支持该类型的属性进行比较
                if(attr_type[compare_attr_index] != INT && attr_type[compare_attr_index] != NUMBER)
                {
                    textEdit->append("Error:attribute type in where clause dose not support the judge condition");
                    return;
                }
                while(!record_in.atEnd())
                {
                    lineElement = record_in.readLine().split(" ", QString::SkipEmptyParts);
                    if(lineElement[compare_attr_index].toInt() < compare_value.toInt())
                    {
                        table->insertRows(count, 1);
                        for(int i = 0; i < attr_index_list.length(); i++)
                        {
                            QTextTableCell cell = table->cellAt(count, i);
                            QTextCursor cell_cursor = cell.firstCursorPosition();
                            cell_cursor.insertText(lineElement[attr_index_list[i]]);
                        }
                        count++;
                    }
                }
            }
            else if(compare_operator == ">")
            {
                // 检查WHERE从句后的运算符是否支持该类型的属性进行比较
                if(attr_type[compare_attr_index] != INT && attr_type[compare_attr_index] != NUMBER)
                {
                    textEdit->append("Error:attribute type in where clause dose not support the judge condition");
                    return;
                }
                while(!record_in.atEnd())
                {
                    lineElement = record_in.readLine().split(" ", QString::SkipEmptyParts);
                    if(lineElement[compare_attr_index].toInt() > compare_value.toInt())
                    {
                        table->insertRows(count, 1);
                        for(int i = 0; i < attr_index_list.length(); i++)
                        {
                            QTextTableCell cell = table->cellAt(count, i);
                            QTextCursor cell_cursor = cell.firstCursorPosition();
                            cell_cursor.insertText(lineElement[attr_index_list[i]]);
                        }
                        count++;
                    }
                }

            }
            else if(compare_operator == "<=")
            {
                // 检查WHERE从句后的运算符是否支持该类型的属性进行比较
                if(attr_type[compare_attr_index] != INT && attr_type[compare_attr_index] != NUMBER)
                {
                    textEdit->append("Error:attribute type in where clause dose not support the judge condition");
                    return;
                }
                while(!record_in.atEnd())
                {
                    lineElement = record_in.readLine().split(" ", QString::SkipEmptyParts);
                    if(lineElement[compare_attr_index].toInt() <= compare_value.toInt())
                    {
                        table->insertRows(count, 1);
                        for(int i = 0; i < attr_index_list.length(); i++)
                        {
                            QTextTableCell cell = table->cellAt(count, i);
                            QTextCursor cell_cursor = cell.firstCursorPosition();
                            cell_cursor.insertText(lineElement[attr_index_list[i]]);
                        }
                        count++;
                    }
                }
            }
            else if(compare_operator == ">=")
            {
                // 检查WHERE从句后的运算符是否支持该类型的属性进行比较
                if(attr_type[compare_attr_index] != INT && attr_type[compare_attr_index] != NUMBER)
                {
                    textEdit->append("Error:attribute type in where clause dose not support the judge condition");
                    return;
                }
                while(!record_in.atEnd())
                {
                    lineElement = record_in.readLine().split(" ", QString::SkipEmptyParts);
                    if(lineElement[compare_attr_index].toInt() >= compare_value.toInt())
                    {
                        table->insertRows(count, 1);
                        for(int i = 0; i < attr_index_list.length(); i++)
                        {
                            QTextTableCell cell = table->cellAt(count, i);
                            QTextCursor cell_cursor = cell.firstCursorPosition();
                            cell_cursor.insertText(lineElement[attr_index_list[i]]);
                        }
                        count++;
                    }
                }
            }
            else
            {
                QMessageBox::critical(nullptr, "Error", "Where clause is wrong");
            }
        }
        else
        {
            QMessageBox::critical(nullptr, "Error", "Where clause is wrong");
            return;
        }
        record_file.close();
    }





    // 实现多表查询
    else
    {
        QList<QStringList> tables_scheme_list;
        QList<QStringList> tables_scheme_type_list;

        QString tempString;
        qDebug() << "tables.length" << tables.length();
        for(int i = 0; i < tables.length(); i++)
        {
            qDebug() << DBPath + "/" + tables[i] + "/" + tables[i] + ".txt";
            QFile table_file(DBPath + "/" + tables[i] + "/" + tables[i] + ".txt");
            if(!table_file.open(QIODevice::ReadOnly))
            {
                QMessageBox::critical(nullptr, "Error", "Failed to open table files");
                return;
            }
            QTextStream in(&table_file);

            QStringList table_scheme_list;
            QStringList table_scheme_type_list;

            // 如果是SELECT*
            if(isSELECTStar)
            {
                while(!in.atEnd())
                {
                    // 读取表名
                    in >> tempString;
                    // 防止在文件最后一行读到空行
                    if(tempString != "")
                    {
                        attrs.append(tempString);
                        table_scheme_list.append(tempString);
                    }
                    // 读取表类型
                    in >> tempString;
                    table_scheme_type_list.append(tempString);
                }
                tables_scheme_list.append(table_scheme_list);
                tables_scheme_type_list.append(table_scheme_type_list);
                table_scheme_list.clear();
                table_scheme_type_list.clear();
                table_file.close();
            }
            else
            {
                while(!in.atEnd())
                {
                    // 读取表名
                    in >> tempString;
                    // 防止在文件最后一行读到空行
                    if(tempString != "")
                    {
                        table_scheme_list.append(tempString);
                    }
                    // 读取表类型
                    in >> tempString;
                    table_scheme_type_list.append(tempString);
                }
                tables_scheme_list.append(table_scheme_list);
                tables_scheme_type_list.append(table_scheme_type_list);
                table_file.close();
                table_scheme_list.clear();
                table_scheme_type_list.clear();
            }
        }

        QStringList temp_line;
        QList<QStringList> attrs_in_tables;
        QList<QList<int>> attrs_in_tables_sequence;
        QList<QList<int>> attrs_in_tables_index;
        if(!isSELECTStar)
        {
            for(int i = 0; i < tables.length(); i++)
            {
                QStringList attrs_in_one_table;
                QList<int> attrs_in_one_table_seq;
                for(int j = 0; j < attrs.length(); j++)
                {
                    temp_line = attrs[j].split(".", QString::SkipEmptyParts);
                    if(!tables.contains(temp_line[0]))
                    {
                        QMessageBox::critical(nullptr, "Error", "In select clause : No such table in from clause");
                        return;
                    }
                    if(tables[i] == temp_line[0])
                    {
                        attrs_in_one_table.append(temp_line[1]);
                        attrs_in_one_table_seq.append(j);
                    }
                }
                attrs_in_tables.append(attrs_in_one_table);
                attrs_in_tables_sequence.append(attrs_in_one_table_seq);
                attrs_in_tables_index.append(get_index_list(tables_scheme_list[i], attrs_in_one_table));
                // 甚至不需要创建文件，我只需要给每个表中的属性标志一下是第几个要查询的属性就可以了呗
            }
            for(int i = 0; i < tables.length(); i++)
            {
                // 检查SELECT后的表名是否合法
                if(!containAll(tables_scheme_list[i], attrs_in_tables[i]))
                {
                    QMessageBox::critical(nullptr, "Error", "attributes after SELECT clause do not exists in given tables");
                }
            }
        }

        qDebug() << "attrs";
        for(int i = 0; i < attrs.length(); i++)
        {
            qDebug() << attrs[i];
        }

        textEdit->append("输出结果：");
        QTextCursor cursor = textEdit->textCursor();
        cursor.movePosition(QTextCursor::End);
        QTextTable* table = cursor.insertTable(1, attrs.length());
        // 输出表模式
        for(int i = 0; i < attrs.length(); i++)
        {
            QTextTableCell cell = table->cellAt(0, i);
            QTextCursor cell_cursor = cell.firstCursorPosition();
            cell_cursor.insertText(attrs[i]);
        }

        int count = 0;
        // 输出表记录
        // 写入临时结果表
        if(isSELECTStar)
        {
            if(reg_type == 0)
            {
                while(tables.length() > 1)
                {
                    QString temp_file_path = DBPath + "/select" + QString::number(count) + "_record.txt";
                    QString table1 = tables.takeFirst();
                    QString table2 = tables.takeFirst();
                    QFile temp_table_file(temp_file_path);
                    QFile table_in_1;
                    QFile table_in_2;
                    if(table1.contains("select"))
                    {
                        table_in_1.setFileName(DBPath + "/" + table1 + "_record.txt");
                    }
                    else
                    {
                        table_in_1.setFileName(DBPath + "/" + table1 + "/" + table1 + "_record.txt");
                    }
                    if(table2.contains("select"))
                    {
                        table_in_2.setFileName(DBPath + "/" + table2 + "_record.txt");
                    }
                    else
                    {
                        table_in_2.setFileName(DBPath + "/" + table2 + "/" + table2 + "_record.txt");
                    }
                    QTextStream temp_out(&temp_table_file);
                    QTextStream in_1(&table_in_1);
                    QTextStream in_2(&table_in_2);
                    if(!temp_table_file.open(QIODevice::WriteOnly) || !table_in_1.open(QIODevice::ReadOnly) || !table_in_2.open(QIODevice::ReadOnly))
                    {
                        QMessageBox::critical(nullptr, "Error", "can not create temp table");
                        return;
                    }
                    QString in_1_line;
                    QString in_2_line;
                    while(!in_1.atEnd())
                    {
                        in_1_line = in_1.readLine();
                        table_in_2.seek(0);
                        while(!in_2.atEnd())
                        {
                            in_2_line = in_2.readLine();
                            temp_out << in_1_line << " " << in_2_line << endl;
                        }
                        //table_in_2.close();
                    }
                    table_in_2.close();
                    table_in_1.close();
                    temp_table_file.close();
                    tables.insert(0, "select" + QString::number(count));
                    // 第二次循环以后每次要吧第一个表文件删除掉，并且不最后一次循环，因为最终结果表要保留
                    if(count >= 1)
                    {
                        table_in_1.remove();
                    }
                    count++;
                }
            }
            else if(reg_type == 3)
            {
                // 检查where从句是否合法
                int table_index = tables.indexOf(compare_attr_table);
                // 获取where从句中进行比较的属性在其所在表中的索引
                compare_attr_index = tables_scheme_list[table_index].indexOf(compare_attr);
                QString compare_attr_type = tables_scheme_type_list[table_index][compare_attr_index];
                if(compare_attr == -1)
                {
                    QMessageBox::critical(nullptr, "Error", "In where clause : No such attribute in the given table");
                    return;
                }
                // 对where从句中的属性进行类型检查

                if(compare_operator == "=")
                {
                    if(compare_attr_type != INT && compare_attr_type != NUMBER && compare_attr_type != VARCHAR)
                    {
                        QMessageBox::critical(nullptr, "Error", "In where clause : No such attribute in the given table");
                        return;
                    }
                    while(tables.length() > 1)
                    {
                        QString temp_file_path = DBPath + "/select" + QString::number(count) + "_record.txt";
                        QString temp_table1 = tables.takeFirst();
                        QString temp_table2 = tables.takeFirst();
                        QFile temp_table_file(temp_file_path);
                        QFile table_in_1;
                        QFile table_in_2;
                        if(temp_table1.contains("select"))
                        {
                            table_in_1.setFileName(DBPath + "/" + temp_table1 + "_record.txt");
                        }
                        else
                        {
                            table_in_1.setFileName(DBPath + "/" + temp_table1 + "/" + temp_table1 + "_record.txt");
                        }
                        if(temp_table2.contains("select"))
                        {
                            table_in_2.setFileName(DBPath + "/" + temp_table2 + "_record.txt");
                        }
                        else
                        {
                            table_in_2.setFileName(DBPath + "/" + temp_table2 + "/" + temp_table2 + "_record.txt");
                        }
                        QTextStream temp_out(&temp_table_file);
                        QTextStream in_1(&table_in_1);
                        QTextStream in_2(&table_in_2);
                        if(!temp_table_file.open(QIODevice::WriteOnly) || !table_in_1.open(QIODevice::ReadOnly) || !table_in_2.open(QIODevice::ReadOnly))
                        {
                            QMessageBox::critical(nullptr, "Error", "can not create temp table");
                            return;
                        }
                        QString in_1_line;
                        QString in_2_line;
                        if(temp_table1 == compare_attr_table)
                        {
                            // 实际上只有第一个最初的第一个表含有要查的属性才会这样
                            while(!in_1.atEnd())
                            {
                                in_1_line = in_1.readLine();
                                QStringList in_1_list = in_1_line.split(" ", QString::SkipEmptyParts);
                                if(in_1_list[compare_attr_index].toInt() == compare_value.toInt())
                                {
                                    table_in_2.seek(0);
                                    while(!in_2.atEnd())
                                    {
                                        in_2_line = in_2.readLine();
                                        temp_out << in_1_line << " " << in_2_line << endl;
                                    }
                                }
                            }
                        }
                        else if(temp_table2 == compare_attr_table)
                        {
                            while(!in_1.atEnd())
                            {
                                in_1_line = in_1.readLine();
                                table_in_2.seek(0);
                                while(!in_2.atEnd())
                                {
                                    in_2_line = in_2.readLine();
                                    QStringList in_2_list = in_2_line.split(" ", QString::SkipEmptyParts);
                                    if(in_2_list[compare_attr_index].toInt() == compare_value.toInt())
                                    {
                                        temp_out << in_1_line << " " << in_2_line << endl;
                                    }
                                }
                            }
                        }
                        else
                        {
                            while(!in_1.atEnd())
                            {
                                in_1_line = in_1.readLine();
                                table_in_2.seek(0);
                                while(!in_2.atEnd())
                                {
                                    in_2_line = in_2.readLine();
                                    temp_out << in_1_line << " " << in_2_line << endl;
                                }
                            }
                        }

                        table_in_2.close();
                        table_in_1.close();
                        temp_table_file.close();
                        tables.insert(0, "select" + QString::number(count));
                        // 第二次循环以后每次要吧第一个表文件删除掉，并且不最后一次循环，因为最终结果表要保留
                        if(count >= 1)
                        {
                            table_in_1.remove();
                        }
                        count++;
                    }
                }
                else if(compare_operator == ">")
                {
                    if(compare_attr_type != INT && compare_attr_type != NUMBER)
                    {
                        QMessageBox::critical(nullptr, "Error", "In where clause : No such attribute in the given table");
                        return;
                    }
                    while(tables.length() > 1)
                    {
                        QString temp_file_path = DBPath + "/select" + QString::number(count) + "_record.txt";
                        QString temp_table1 = tables.takeFirst();
                        QString temp_table2 = tables.takeFirst();
                        QFile temp_table_file(temp_file_path);
                        QFile table_in_1;
                        QFile table_in_2;
                        if(temp_table1.contains("select"))
                        {
                            table_in_1.setFileName(DBPath + "/" + temp_table1 + "_record.txt");
                        }
                        else
                        {
                            table_in_1.setFileName(DBPath + "/" + temp_table1 + "/" + temp_table1 + "_record.txt");
                        }
                        if(temp_table2.contains("select"))
                        {
                            table_in_2.setFileName(DBPath + "/" + temp_table2 + "_record.txt");
                        }
                        else
                        {
                            table_in_2.setFileName(DBPath + "/" + temp_table2 + "/" + temp_table2 + "_record.txt");
                        }
                        QTextStream temp_out(&temp_table_file);
                        QTextStream in_1(&table_in_1);
                        QTextStream in_2(&table_in_2);
                        if(!temp_table_file.open(QIODevice::WriteOnly) || !table_in_1.open(QIODevice::ReadOnly) || !table_in_2.open(QIODevice::ReadOnly))
                        {
                            QMessageBox::critical(nullptr, "Error", "can not create temp table");
                            return;
                        }
                        QString in_1_line;
                        QString in_2_line;
                        if(temp_table1 == compare_attr_table)
                        {
                            // 实际上只有第一个最初的第一个表含有要查的属性才会这样
                            while(!in_1.atEnd())
                            {
                                in_1_line = in_1.readLine();
                                QStringList in_1_list = in_1_line.split(" ", QString::SkipEmptyParts);
                                if(in_1_list[compare_attr_index].toInt() > compare_value.toInt())
                                {
                                    table_in_2.seek(0);
                                    while(!in_2.atEnd())
                                    {
                                        in_2_line = in_2.readLine();
                                        temp_out << in_1_line << " " << in_2_line << endl;
                                    }
                                }
                            }
                        }
                        else if(temp_table2 == compare_attr_table)
                        {
                            while(!in_1.atEnd())
                            {
                                in_1_line = in_1.readLine();
                                table_in_2.seek(0);
                                while(!in_2.atEnd())
                                {
                                    in_2_line = in_2.readLine();
                                    QStringList in_2_list = in_2_line.split(" ", QString::SkipEmptyParts);
                                    if(in_2_list[compare_attr_index].toInt() > compare_value.toInt())
                                    {
                                        temp_out << in_1_line << " " << in_2_line << endl;
                                    }
                                }
                            }
                        }
                        else
                        {
                            while(!in_1.atEnd())
                            {
                                in_1_line = in_1.readLine();
                                table_in_2.seek(0);
                                while(!in_2.atEnd())
                                {
                                    in_2_line = in_2.readLine();
                                    temp_out << in_1_line << " " << in_2_line << endl;
                                }
                            }
                        }

                        table_in_2.close();
                        table_in_1.close();
                        temp_table_file.close();
                        tables.insert(0, "select" + QString::number(count));
                        // 第二次循环以后每次要吧第一个表文件删除掉，并且不最后一次循环，因为最终结果表要保留
                        if(count >= 1)
                        {
                            table_in_1.remove();
                        }
                        count++;
                    }
                }
                else if(compare_operator == "<")
                {
                    if(compare_attr_type != INT && compare_attr_type != NUMBER)
                    {
                        QMessageBox::critical(nullptr, "Error", "In where clause : No such attribute in the given table");
                        return;
                    }
                    while(tables.length() > 1)
                    {
                        QString temp_file_path = DBPath + "/select" + QString::number(count) + "_record.txt";
                        QString temp_table1 = tables.takeFirst();
                        QString temp_table2 = tables.takeFirst();
                        QFile temp_table_file(temp_file_path);
                        QFile table_in_1;
                        QFile table_in_2;
                        if(temp_table1.contains("select"))
                        {
                            table_in_1.setFileName(DBPath + "/" + temp_table1 + "_record.txt");
                        }
                        else
                        {
                            table_in_1.setFileName(DBPath + "/" + temp_table1 + "/" + temp_table1 + "_record.txt");
                        }
                        if(temp_table2.contains("select"))
                        {
                            table_in_2.setFileName(DBPath + "/" + temp_table2 + "_record.txt");
                        }
                        else
                        {
                            table_in_2.setFileName(DBPath + "/" + temp_table2 + "/" + temp_table2 + "_record.txt");
                        }
                        QTextStream temp_out(&temp_table_file);
                        QTextStream in_1(&table_in_1);
                        QTextStream in_2(&table_in_2);
                        if(!temp_table_file.open(QIODevice::WriteOnly) || !table_in_1.open(QIODevice::ReadOnly) || !table_in_2.open(QIODevice::ReadOnly))
                        {
                            QMessageBox::critical(nullptr, "Error", "can not create temp table");
                            return;
                        }
                        QString in_1_line;
                        QString in_2_line;
                        if(temp_table1 == compare_attr_table)
                        {
                            // 实际上只有第一个最初的第一个表含有要查的属性才会这样
                            while(!in_1.atEnd())
                            {
                                in_1_line = in_1.readLine();
                                QStringList in_1_list = in_1_line.split(" ", QString::SkipEmptyParts);
                                if(in_1_list[compare_attr_index].toInt() < compare_value.toInt())
                                {
                                    table_in_2.seek(0);
                                    while(!in_2.atEnd())
                                    {
                                        in_2_line = in_2.readLine();
                                        temp_out << in_1_line << " " << in_2_line << endl;
                                    }
                                }
                            }
                        }
                        else if(temp_table2 == compare_attr_table)
                        {
                            while(!in_1.atEnd())
                            {
                                in_1_line = in_1.readLine();
                                table_in_2.seek(0);
                                while(!in_2.atEnd())
                                {
                                    in_2_line = in_2.readLine();
                                    QStringList in_2_list = in_2_line.split(" ", QString::SkipEmptyParts);
                                    if(in_2_list[compare_attr_index].toInt() < compare_value.toInt())
                                    {
                                        temp_out << in_1_line << " " << in_2_line << endl;
                                    }
                                }
                            }
                        }
                        else
                        {
                            while(!in_1.atEnd())
                            {
                                in_1_line = in_1.readLine();
                                table_in_2.seek(0);
                                while(!in_2.atEnd())
                                {
                                    in_2_line = in_2.readLine();
                                    temp_out << in_1_line << " " << in_2_line << endl;
                                }
                            }
                        }

                        table_in_2.close();
                        table_in_1.close();
                        temp_table_file.close();
                        tables.insert(0, "select" + QString::number(count));
                        // 第二次循环以后每次要吧第一个表文件删除掉，并且不最后一次循环，因为最终结果表要保留
                        if(count >= 1)
                        {
                            table_in_1.remove();
                        }
                        count++;
                    }
                }
                else if(compare_operator == "<=")
                {
                    if(compare_attr_type != INT && compare_attr_type != NUMBER)
                    {
                        QMessageBox::critical(nullptr, "Error", "In where clause : No such attribute in the given table");
                        return;
                    }
                    while(tables.length() > 1)
                    {
                        QString temp_file_path = DBPath + "/select" + QString::number(count) + "_record.txt";
                        QString temp_table1 = tables.takeFirst();
                        QString temp_table2 = tables.takeFirst();
                        QFile temp_table_file(temp_file_path);
                        QFile table_in_1;
                        QFile table_in_2;
                        if(temp_table1.contains("select"))
                        {
                            table_in_1.setFileName(DBPath + "/" + temp_table1 + "_record.txt");
                        }
                        else
                        {
                            table_in_1.setFileName(DBPath + "/" + temp_table1 + "/" + temp_table1 + "_record.txt");
                        }
                        if(temp_table2.contains("select"))
                        {
                            table_in_2.setFileName(DBPath + "/" + temp_table2 + "_record.txt");
                        }
                        else
                        {
                            table_in_2.setFileName(DBPath + "/" + temp_table2 + "/" + temp_table2 + "_record.txt");
                        }
                        QTextStream temp_out(&temp_table_file);
                        QTextStream in_1(&table_in_1);
                        QTextStream in_2(&table_in_2);
                        if(!temp_table_file.open(QIODevice::WriteOnly) || !table_in_1.open(QIODevice::ReadOnly) || !table_in_2.open(QIODevice::ReadOnly))
                        {
                            QMessageBox::critical(nullptr, "Error", "can not create temp table");
                            return;
                        }
                        QString in_1_line;
                        QString in_2_line;
                        if(temp_table1 == compare_attr_table)
                        {
                            // 实际上只有第一个最初的第一个表含有要查的属性才会这样
                            while(!in_1.atEnd())
                            {
                                in_1_line = in_1.readLine();
                                QStringList in_1_list = in_1_line.split(" ", QString::SkipEmptyParts);
                                if(in_1_list[compare_attr_index].toInt() <= compare_value.toInt())
                                {
                                    table_in_2.seek(0);
                                    while(!in_2.atEnd())
                                    {
                                        in_2_line = in_2.readLine();
                                        temp_out << in_1_line << " " << in_2_line << endl;
                                    }
                                }
                            }
                        }
                        else if(temp_table2 == compare_attr_table)
                        {
                            while(!in_1.atEnd())
                            {
                                in_1_line = in_1.readLine();
                                table_in_2.seek(0);
                                while(!in_2.atEnd())
                                {
                                    in_2_line = in_2.readLine();
                                    QStringList in_2_list = in_2_line.split(" ", QString::SkipEmptyParts);
                                    if(in_2_list[compare_attr_index].toInt() <= compare_value.toInt())
                                    {
                                        temp_out << in_1_line << " " << in_2_line << endl;
                                    }
                                }
                            }
                        }
                        else
                        {
                            while(!in_1.atEnd())
                            {
                                in_1_line = in_1.readLine();
                                table_in_2.seek(0);
                                while(!in_2.atEnd())
                                {
                                    in_2_line = in_2.readLine();
                                    temp_out << in_1_line << " " << in_2_line << endl;
                                }
                            }
                        }

                        table_in_2.close();
                        table_in_1.close();
                        temp_table_file.close();
                        tables.insert(0, "select" + QString::number(count));
                        // 第二次循环以后每次要吧第一个表文件删除掉，并且不最后一次循环，因为最终结果表要保留
                        if(count >= 1)
                        {
                            table_in_1.remove();
                        }
                        count++;
                    }
                }
                else if(compare_operator == ">=")
                {
                    if(compare_attr_type != INT && compare_attr_type != NUMBER)
                    {
                        QMessageBox::critical(nullptr, "Error", "In where clause : No such attribute in the given table");
                        return;
                    }
                    while(tables.length() > 1)
                    {
                        QString temp_file_path = DBPath + "/select" + QString::number(count) + "_record.txt";
                        QString temp_table1 = tables.takeFirst();
                        QString temp_table2 = tables.takeFirst();
                        QFile temp_table_file(temp_file_path);
                        QFile table_in_1;
                        QFile table_in_2;
                        if(temp_table1.contains("select"))
                        {
                            table_in_1.setFileName(DBPath + "/" + temp_table1 + "_record.txt");
                        }
                        else
                        {
                            table_in_1.setFileName(DBPath + "/" + temp_table1 + "/" + temp_table1 + "_record.txt");
                        }
                        if(temp_table2.contains("select"))
                        {
                            table_in_2.setFileName(DBPath + "/" + temp_table2 + "_record.txt");
                        }
                        else
                        {
                            table_in_2.setFileName(DBPath + "/" + temp_table2 + "/" + temp_table2 + "_record.txt");
                        }
                        QTextStream temp_out(&temp_table_file);
                        QTextStream in_1(&table_in_1);
                        QTextStream in_2(&table_in_2);
                        if(!temp_table_file.open(QIODevice::WriteOnly) || !table_in_1.open(QIODevice::ReadOnly) || !table_in_2.open(QIODevice::ReadOnly))
                        {
                            QMessageBox::critical(nullptr, "Error", "can not create temp table");
                            return;
                        }
                        QString in_1_line;
                        QString in_2_line;
                        if(temp_table1 == compare_attr_table)
                        {
                            // 实际上只有第一个最初的第一个表含有要查的属性才会这样
                            while(!in_1.atEnd())
                            {
                                in_1_line = in_1.readLine();
                                QStringList in_1_list = in_1_line.split(" ", QString::SkipEmptyParts);
                                if(in_1_list[compare_attr_index].toInt() >= compare_value.toInt())
                                {
                                    table_in_2.seek(0);
                                    while(!in_2.atEnd())
                                    {
                                        in_2_line = in_2.readLine();
                                        temp_out << in_1_line << " " << in_2_line << endl;
                                    }
                                }
                            }
                        }
                        else if(temp_table2 == compare_attr_table)
                        {
                            while(!in_1.atEnd())
                            {
                                in_1_line = in_1.readLine();
                                table_in_2.seek(0);
                                while(!in_2.atEnd())
                                {
                                    in_2_line = in_2.readLine();
                                    QStringList in_2_list = in_2_line.split(" ", QString::SkipEmptyParts);
                                    if(in_2_list[compare_attr_index].toInt() >= compare_value.toInt())
                                    {
                                        temp_out << in_1_line << " " << in_2_line << endl;
                                    }
                                }
                            }
                        }
                        else
                        {
                            while(!in_1.atEnd())
                            {
                                in_1_line = in_1.readLine();
                                table_in_2.seek(0);
                                while(!in_2.atEnd())
                                {
                                    in_2_line = in_2.readLine();
                                    temp_out << in_1_line << " " << in_2_line << endl;
                                }
                            }
                        }
                        table_in_2.close();
                        table_in_1.close();
                        temp_table_file.close();
                        tables.insert(0, "select" + QString::number(count));
                        // 第二次循环以后每次要吧第一个表文件删除掉，并且不最后一次循环，因为最终结果表要保留
                        if(count >= 1)
                        {
                            table_in_1.remove();
                        }
                        count++;
                    }
                }
                else
                {
                    QMessageBox::critical(nullptr, "Error", "No such operator in where clause");
                    return;
                }
            }
            else
            {
                QMessageBox::critical(nullptr, "Error", "where clause is wrong");
                return;
            }
        }
        else
        {
            if(reg_type == 0)
            {
                QStringList temp_table;
                // 先建立临时表,将每个表的所选属性提取出来
                for(int i = 0; i < tables.length(); i++)
                {
                    QString temp_path = DBPath + "/select" + QString::number(i) + "_record.txt";
                    QString table_path = DBPath + "/" + tables[i] + "/" + tables[i] + "_record.txt";
                    QFile temp_file(temp_path);
                    QTextStream temp_out(&temp_file);
                    QFile table_file(table_path);
                    QTextStream table_in(&table_file);
                    if(!temp_file.open(QIODevice::WriteOnly) || !table_file.open(QIODevice::ReadOnly))
                    {
                        QMessageBox::critical(nullptr, "Error", "Failed to open files");
                    }
                    QStringList line;
                    while(!table_in.atEnd())
                    {
                        line = table_in.readLine().split(" ", QString::SkipEmptyParts);
                        for(int j = 0; j < attrs_in_tables[i].length(); j++)
                        {
                            temp_out << line[attrs_in_tables_index[i][j]] << " ";
                        }
                        temp_out << endl;
                    }
                    table_file.close();
                    temp_file.close();
                    temp_table.append("select" + QString::number(i));
                }

                // 把筛选出来的表都连接在一个表上面
                while(temp_table.length() > 1)
                {
                    QString path1 = DBPath + "/" + temp_table.takeFirst() + "_record.txt";
                    QString path2 = DBPath + "/" + temp_table.takeFirst() + "_record.txt";
                    QString final_path = DBPath + "/final" + QString::number(count) + "_record.txt";
                    QFile file1(path1);
                    QFile file2(path2);
                    QFile final_file(final_path);
                    QTextStream in1(&file1);
                    QTextStream in2(&file2);
                    QTextStream out(&final_file);
                    QString line1;
                    QString line2;
                    if(!final_file.open(QIODevice::WriteOnly) || !file1.open(QIODevice::ReadOnly) || !file2.open(QIODevice::ReadOnly))
                    {
                        QMessageBox::critical(nullptr, "Error", "File open failure 483" + path1 + path2);
                        return;
                    }
                    while(!in1.atEnd())
                    {
                        line1 = in1.readLine().trimmed();
                        file2.seek(0);
                        while(!in2.atEnd())
                        {
                            line2 = in2.readLine().trimmed();
                            out << line1 << " " << line2 << endl;
                        }
                    }
                    file2.close();
                    file1.close();
                    final_file.close();
                    file1.remove();
                    file2.remove();
                    temp_table.insert(0, "final" + QString::number(count));
                    count++;
                }
                // 对整合好的表进行列排序，之后即可输出了
                QStringList line;
                QString path_in = DBPath + "/" + temp_table[0] + "_record.txt";
                QString path_out = DBPath + "/finalsum_record.txt";
                QFile final_file(path_in);
                QFile final_sum(path_out);
                QTextStream in(&final_file);
                QTextStream out(&final_sum);
                if(!final_file.open(QIODevice::ReadOnly) || !final_sum.open(QIODevice::WriteOnly))
                {
                    // 第二次循环的时候打不开文件，不知道为什么
                    QMessageBox::critical(nullptr, "Error", "failed to open file");
                    return;
                }
                while(!in.atEnd())
                {
                    // final_file没有写入信息
                    line = in.readLine().split(" ", QString::SkipEmptyParts);
                    line = sort_by_sequence(line, attrs_in_tables, attrs_in_tables_sequence);
                    QString input = line.join(" ");
                    out << input << endl;
                }
                final_file.close();
                final_sum.close();
                final_file.remove();
                // 这里会导致原先tables[0]的文件不能被删除
                tables[0] = "finalsum";
            }
            else if(reg_type == 3)
            {
                int table_index = tables.indexOf(compare_attr_table);
                compare_attr_index = tables_scheme_list[table_index].indexOf(compare_attr);
                QString compare_attr_type = tables_scheme_type_list[table_index][compare_attr_index];
                if(compare_attr_index == -1)
                {
                    QMessageBox::critical(nullptr, "Error", "In where clause : No such attribute in the given table");
                    return;
                }
                // 储存每个表筛选后的结果
                QStringList temp_table;

                // 类型检查
                // ？？？

                // 先建立临时表,将每个表的所选属性提取出来
                if(compare_operator == "=")
                {
                    if(compare_attr_type != INT && compare_attr_type != NUMBER && compare_attr_type != VARCHAR)
                    {
                        QMessageBox::critical(nullptr, "Error", "In where clause : compare_attr_type is not supported");
                        return;
                    }
                    for(int i = 0; i < tables.length(); i++)
                    {
                        QString temp_path = DBPath + "/select" + QString::number(i) + "_record.txt";
                        QString table_path = DBPath + "/" + tables[i] + "/" + tables[i] + "_record.txt";
                        QFile temp_file(temp_path);
                        QTextStream temp_out(&temp_file);
                        QFile table_file(table_path);
                        QTextStream table_in(&table_file);
                        if(!temp_file.open(QIODevice::WriteOnly) || !table_file.open(QIODevice::ReadOnly))
                        {
                            QMessageBox::critical(nullptr, "Error", "Failed to open files");
                        }
                        QStringList line;
                        if(i == table_index)
                        {
                            while(!table_in.atEnd())
                            {
                                line = table_in.readLine().split(" ", QString::SkipEmptyParts);
                                if(line[compare_attr_index] == compare_value)
                                {
                                    for(int j = 0; j < attrs_in_tables[i].length(); j++)
                                    {
                                        temp_out << line[attrs_in_tables_index[i][j]] << " ";
                                    }
                                    temp_out << endl;
                                }
                            }
                        }
                        else
                        {
                            while(!table_in.atEnd())
                            {
                                line = table_in.readLine().split(" ", QString::SkipEmptyParts);
                                for(int j = 0; j < attrs_in_tables[i].length(); j++)
                                {
                                    temp_out << line[attrs_in_tables_index[i][j]] << " ";
                                }
                                temp_out << endl;
                            }
                        }
                        table_file.close();
                        temp_file.close();
                        temp_table.append("select" + QString::number(i));
                    }
                }
                else if(compare_operator == "<")
                {
                    if(compare_attr_type != INT && compare_attr_type != NUMBER)
                    {
                        QMessageBox::critical(nullptr, "Error", "In where clause : compare_attr_type is not supported");
                        return;
                    }
                    for(int i = 0; i < tables.length(); i++)
                    {
                        QString temp_path = DBPath + "/select" + QString::number(i) + "_record.txt";
                        QString table_path = DBPath + "/" + tables[i] + "/" + tables[i] + "_record.txt";
                        QFile temp_file(temp_path);
                        QTextStream temp_out(&temp_file);
                        QFile table_file(table_path);
                        QTextStream table_in(&table_file);
                        if(!temp_file.open(QIODevice::WriteOnly) || !table_file.open(QIODevice::ReadOnly))
                        {
                            QMessageBox::critical(nullptr, "Error", "Failed to open files");
                        }
                        QStringList line;
                        if(i == table_index)
                        {
                            while(!table_in.atEnd())
                            {
                                line = table_in.readLine().split(" ", QString::SkipEmptyParts);
                                if(line[compare_attr_index].toInt() < compare_value.toInt())
                                {
                                    for(int j = 0; j < attrs_in_tables[i].length(); j++)
                                    {
                                        temp_out << line[attrs_in_tables_index[i][j]] << " ";
                                    }
                                    temp_out << endl;
                                }
                            }
                        }
                        else
                        {
                            while(!table_in.atEnd())
                            {
                                line = table_in.readLine().split(" ", QString::SkipEmptyParts);
                                for(int j = 0; j < attrs_in_tables[i].length(); j++)
                                {
                                    temp_out << line[attrs_in_tables_index[i][j]] << " ";
                                }
                                temp_out << endl;
                            }
                        }
                        table_file.close();
                        temp_file.close();
                        temp_table.append("select" + QString::number(i));
                    }
                }
                else if(compare_operator == ">")
                {
                    if(compare_attr_type != INT && compare_attr_type != NUMBER && compare_attr_type != VARCHAR)
                    {
                        QMessageBox::critical(nullptr, "Error", "In where clause : compare_attr_type is not supported");
                        return;
                    }
                    for(int i = 0; i < tables.length(); i++)
                    {
                        QString temp_path = DBPath + "/select" + QString::number(i) + "_record.txt";
                        QString table_path = DBPath + "/" + tables[i] + "/" + tables[i] + "_record.txt";
                        QFile temp_file(temp_path);
                        QTextStream temp_out(&temp_file);
                        QFile table_file(table_path);
                        QTextStream table_in(&table_file);
                        if(!temp_file.open(QIODevice::WriteOnly) || !table_file.open(QIODevice::ReadOnly))
                        {
                            QMessageBox::critical(nullptr, "Error", "Failed to open files");
                        }
                        QStringList line;
                        if(i == table_index)
                        {
                            while(!table_in.atEnd())
                            {
                                line = table_in.readLine().split(" ", QString::SkipEmptyParts);
                                if(line[compare_attr_index].toInt() > compare_value.toInt())
                                {
                                    for(int j = 0; j < attrs_in_tables[i].length(); j++)
                                    {
                                        temp_out << line[attrs_in_tables_index[i][j]] << " ";
                                    }
                                    temp_out << endl;
                                }
                            }
                        }
                        else
                        {
                            while(!table_in.atEnd())
                            {
                                line = table_in.readLine().split(" ", QString::SkipEmptyParts);
                                for(int j = 0; j < attrs_in_tables[i].length(); j++)
                                {
                                    temp_out << line[attrs_in_tables_index[i][j]] << " ";
                                }
                                temp_out << endl;
                            }
                        }
                        table_file.close();
                        temp_file.close();
                        temp_table.append("select" + QString::number(i));
                    }
                }
                else if(compare_operator == "<=")
                {
                    if(compare_attr_type != INT && compare_attr_type != NUMBER && compare_attr_type != VARCHAR)
                    {
                        QMessageBox::critical(nullptr, "Error", "In where clause : compare_attr_type is not supported");
                        return;
                    }
                    for(int i = 0; i < tables.length(); i++)
                    {
                        QString temp_path = DBPath + "/select" + QString::number(i) + "_record.txt";
                        QString table_path = DBPath + "/" + tables[i] + "/" + tables[i] + "_record.txt";
                        QFile temp_file(temp_path);
                        QTextStream temp_out(&temp_file);
                        QFile table_file(table_path);
                        QTextStream table_in(&table_file);
                        if(!temp_file.open(QIODevice::WriteOnly) || !table_file.open(QIODevice::ReadOnly))
                        {
                            QMessageBox::critical(nullptr, "Error", "Failed to open files");
                        }
                        QStringList line;
                        if(i == table_index)
                        {
                            while(!table_in.atEnd())
                            {
                                line = table_in.readLine().split(" ", QString::SkipEmptyParts);
                                if(line[compare_attr_index].toInt() <= compare_value.toInt())
                                {
                                    for(int j = 0; j < attrs_in_tables[i].length(); j++)
                                    {
                                        temp_out << line[attrs_in_tables_index[i][j]] << " ";
                                    }
                                    temp_out << endl;
                                }
                            }
                        }
                        else
                        {
                            while(!table_in.atEnd())
                            {
                                line = table_in.readLine().split(" ", QString::SkipEmptyParts);
                                for(int j = 0; j < attrs_in_tables[i].length(); j++)
                                {
                                    temp_out << line[attrs_in_tables_index[i][j]] << " ";
                                }
                                temp_out << endl;
                            }
                        }
                        table_file.close();
                        temp_file.close();
                        temp_table.append("select" + QString::number(i));
                    }
                }
                else if(compare_operator == ">=")
                {
                    if(compare_attr_type != INT && compare_attr_type != NUMBER && compare_attr_type != VARCHAR)
                    {
                        QMessageBox::critical(nullptr, "Error", "In where clause : compare_attr_type is not supported");
                        return;
                    }
                    for(int i = 0; i < tables.length(); i++)
                    {
                        QString temp_path = DBPath + "/select" + QString::number(i) + "_record.txt";
                        QString table_path = DBPath + "/" + tables[i] + "/" + tables[i] + "_record.txt";
                        QFile temp_file(temp_path);
                        QTextStream temp_out(&temp_file);
                        QFile table_file(table_path);
                        QTextStream table_in(&table_file);
                        if(!temp_file.open(QIODevice::WriteOnly) || !table_file.open(QIODevice::ReadOnly))
                        {
                            QMessageBox::critical(nullptr, "Error", "Failed to open files");
                        }
                        QStringList line;
                        if(i == table_index)
                        {
                            while(!table_in.atEnd())
                            {
                                line = table_in.readLine().split(" ", QString::SkipEmptyParts);
                                if(line[compare_attr_index].toInt() >= compare_value.toInt())
                                {
                                    for(int j = 0; j < attrs_in_tables[i].length(); j++)
                                    {
                                        temp_out << line[attrs_in_tables_index[i][j]] << " ";
                                    }
                                    temp_out << endl;
                                }
                            }
                        }
                        else
                        {
                            while(!table_in.atEnd())
                            {
                                line = table_in.readLine().split(" ", QString::SkipEmptyParts);
                                for(int j = 0; j < attrs_in_tables[i].length(); j++)
                                {
                                    temp_out << line[attrs_in_tables_index[i][j]] << " ";
                                }
                                temp_out << endl;
                            }
                        }
                        table_file.close();
                        temp_file.close();
                        temp_table.append("select" + QString::number(i));
                    }
                }


                // 把筛选出来的表都连接在一个表上面
                while(temp_table.length() > 1)
                {
                    QString path1 = DBPath + "/" + temp_table.takeFirst() + "_record.txt";
                    QString path2 = DBPath + "/" + temp_table.takeFirst() + "_record.txt";
                    QString final_path = DBPath + "/final" + QString::number(count) + "_record.txt";
                    QFile file1(path1);
                    QFile file2(path2);
                    QFile final_file(final_path);
                    QTextStream in1(&file1);
                    QTextStream in2(&file2);
                    QTextStream out(&final_file);
                    QString line1;
                    QString line2;
                    if(!final_file.open(QIODevice::WriteOnly) || !file1.open(QIODevice::ReadOnly) || !file2.open(QIODevice::ReadOnly))
                    {
                        QMessageBox::critical(nullptr, "Error", "File open failure 483" + path1 + path2);
                        return;
                    }
                    while(!in1.atEnd())
                    {
                        line1 = in1.readLine().trimmed();
                        file2.seek(0);
                        while(!in2.atEnd())
                        {
                            line2 = in2.readLine().trimmed();
                            out << line1 << " " << line2 << endl;
                        }
                    }
                    file2.close();
                    file1.close();
                    final_file.close();
                    file1.remove();
                    file2.remove();
                    temp_table.insert(0, "final" + QString::number(count));
                    count++;
                }
                // 对整合好的表进行列排序，之后即可输出了
                QStringList line;
                QString path_in = DBPath + "/" + temp_table[0] + "_record.txt";
                QString path_out = DBPath + "/finalsum_record.txt";
                QFile final_file(path_in);
                QFile final_sum(path_out);
                QTextStream in(&final_file);
                QTextStream out(&final_sum);
                if(!final_file.open(QIODevice::ReadOnly) || !final_sum.open(QIODevice::WriteOnly))
                {
                    // 第二次循环的时候打不开文件，不知道为什么
                    QMessageBox::critical(nullptr, "Error", "failed to open file");
                    return;
                }
                while(!in.atEnd())
                {
                    // final_file没有写入信息
                    line = in.readLine().split(" ", QString::SkipEmptyParts);
                    line = sort_by_sequence(line, attrs_in_tables, attrs_in_tables_sequence);
                    QString input = line.join(" ");
                    out << input << endl;
                }
                final_file.close();
                final_sum.close();
                final_file.remove();
                // 这里会导致原先tables[0]的文件不能被删除
                tables[0] = "finalsum";
            }
            else
            {
                QMessageBox::critical(nullptr, "Error", "where clause is wrong");
                return;
            }
        }

        QString final_table = DBPath + "/" + tables[0] + "_record.txt";
        QFile final_file(final_table);
        if(!final_file.open(QIODevice::ReadOnly))
        {
            QMessageBox::critical(nullptr, "Error", "final table open failure");
            return;
        }
        QTextStream final_in(&final_file);
        int table_line_index = 1;
        QStringList line;
        while(!final_in.atEnd())
        {
            table->insertRows(table_line_index, 1);
            line = final_in.readLine().split(" ", QString::SkipEmptyParts);
            for(int i = 0; i < attrs.length(); i++)
            {
                QTextTableCell cell = table->cellAt(table_line_index, i);
                QTextCursor cell_cursor = cell.firstCursorPosition();
                cell_cursor.insertText(line[i]);
            }
            table_line_index++;
        }
        final_file.close();
        // 删除记录查询信息的最终表文件
        if(!final_file.remove())
        {
            QMessageBox::critical(nullptr, "Error", "can not remove temp files");
            return;
        }
    }
}

bool SearchRecord::containAll(const QStringList& list1, const QStringList& list2)
{
    for(int i = 0; i < list2.length(); i++)
    {
        if (!list1.contains(list2[i]))
        {
            return false;
        }
    }
    return true;
}

QList<int> SearchRecord::get_index_list(const QStringList& list1, const QStringList& list2)
{
    QList<int> index_list;
    for(int i = 0; i < list2.length(); i++)
    {
        index_list.append(list1.indexOf(list2[i]));
    }

    return index_list;
}

QStringList SearchRecord::sort_by_sequence(QStringList& list, const QList<QStringList>& attrs_in_tables , const QList<QList<int>>& sequence)
{
    QString* temp = new QString[list.length()];
    QString* extend = new QString[list.length()];
    int* sequence_extend = new int[list.length()];
    QStringList result;

    int table_count = 0;
    int attr_count = 0;
    // 将装有各个表属性的数组展开为一维数组
    for(int i = 0; i < list.length(); i++)
    {
        if(attr_count == attrs_in_tables[table_count].length())
        {
            attr_count = 0;
            table_count++;
        }
        extend[i] = attrs_in_tables[table_count][attr_count];
        sequence_extend[i] = sequence[table_count][attr_count];
        attr_count++;
    }

    for(int i = 0; i < list.length(); i++)
    {
        temp[sequence_extend[i]] = list[i];
    }

    for(int i = 0; i < list.length(); i++)
    {
        result.append(temp[i]);
    }
    delete[] sequence_extend;
    delete[] temp;
    return result;
}
