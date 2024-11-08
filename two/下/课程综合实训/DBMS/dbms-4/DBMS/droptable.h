#ifndef DROPTABLE_H
#define DROPTABLE_H

#include <iostream>
#include <regex>
#include <string>
#include <cstdio>
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

class droptable
{
public:
    droptable();
    void drop(QString tablename,QString basename);
};

#endif // DROPTABLE_H
