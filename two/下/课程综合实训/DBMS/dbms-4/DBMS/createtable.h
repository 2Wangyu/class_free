#ifndef CREATETABLE_H
#define CREATETABLE_H
#include<QString>
#include<vector>
#include<string>
#include "userinterface.h"
#include "ui_userinterface.h"
#include"createdatabase.h"
#include"dropdatabase.h"
#include <sstream>
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
using namespace std;
class createtable
{
public:
    createtable();
    void init(QString dbName, QString tableName,QString columnDefinitions);
};

#endif // CREATETABLE_H
