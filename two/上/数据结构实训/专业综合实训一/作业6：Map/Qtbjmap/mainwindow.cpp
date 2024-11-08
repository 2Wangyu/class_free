#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QApplication>
#include <QPushButton>
#include<QLabel>
#include<QTextEdit>
#include<QBoxLayout>
#include<QDialog>
#include"graph.h"
#include<QStack>
#include<stack>
#include<vector>
#include<QSqlDatabase>
#include<QMessageBox>
#include <QSqlError>
#include <QPluginLoader>
#include<QSqlQuery>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);


    // 调用 Initmap 函数
    Initmap();
     linkedatabasescene();
     linkedatabasepath();
    g=new Graph;

}

MainWindow::~MainWindow()
{
    delete ui;
    delete g;
}
//数据库存储信息
void MainWindow::linkedatabasescene(){
    // QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    // db.setHostName("127.0.0.1");  //连接本地主机
    // db.setPort(3306);
    // db.setDatabaseName("数据库名");
    // db.setUserName("用户名");
    // db.setPassword("密码");
    // bool ok = db.open();
    // if (ok){
    //     QMessageBox::information(this, "infor", "link success");
    // }
    // else {
    //     QMessageBox::information(this, "infor", "link failed");
    //     qDebug()<<"error open database because"<<db.lastError().text();
    // }

    // //输出可用数据库
    // qDebug()<<"available drivers:";
    // QStringList drivers = QSqlDatabase::drivers();
    // foreach(QString driver, drivers)
    //     qDebug()<<driver;
    QSqlDatabase database;

    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        // 建立和SQlite数据库的连接
        database = QSqlDatabase::addDatabase("QSQLITE");
        // 设置数据库文件的名字
        database.setDatabaseName("MyDataBase1.db");
    }
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }
    else
    {
        qDebug() << "success";
        // 用于执行sql语句的对象
        QSqlQuery sqlQuery1;

        // 检查表是否存在，如果存在则删除
        if(sqlQuery1.exec("SELECT COUNT(*) FROM sqlite_master WHERE type='table' AND name='scene'"))
        {
            sqlQuery1.exec("DROP TABLE scene");
        }
        // 构建创建数据库的sql语句字符串
        QString createSql1 = QString("CREATE TABLE scene (\
                                    id INT PRIMARY KEY NOT NULL,\
                                    name TEXT NOT NULL,\
                                    coordinate TEXT NOT NULL,\
                                    introduction TEXT NOT NULL)");
                            //sqlQuery1.prepare(createSql1);
        // 执行sql语句
        if(!sqlQuery1.exec(createSql1))
        {
            qDebug() << "Error: Fail to create table. " << sqlQuery1.lastError();
        }
        else
        {     qDebug() << "Table created!";
        }
        sqlQuery1.prepare("INSERT INTO scene VALUES(:id,:name,:coordinate,:introduction)");

        sqlQuery1.bindValue(":id", 1);
        sqlQuery1.bindValue(":name", "体育馆");
        sqlQuery1.bindValue(":coordinate", "75,-300");
        sqlQuery1.bindValue(":introduction", "嘿嘿嘿，最喜欢的地方，每个礼拜来健身");
        if(!sqlQuery1.exec())
        {
            qDebug() << "Error: Fail to insert data. " << sqlQuery1.lastError();
        }
        else
        {
            qDebug() << "Insert successfully. " << sqlQuery1.lastError();
        }

        sqlQuery1.bindValue(":id", 2);
        sqlQuery1.bindValue(":name", "学活");
        sqlQuery1.bindValue(":coordinate", "0,0");
        sqlQuery1.bindValue(":introduction", "饭很好吃");
        if(!sqlQuery1.exec())
        {
            qDebug() << "Error: Fail to insert data. " << sqlQuery1.lastError();
        }
        else
        {
            qDebug() << "Insert successfully. " << sqlQuery1.lastError();
        }

        sqlQuery1.bindValue(":id", 3);
        sqlQuery1.bindValue(":name", "思西楼");
        sqlQuery1.bindValue(":coordinate", "150，-50");
        sqlQuery1.bindValue(":introduction", "还不错，高楼层的自习区域很不错");
        if(!sqlQuery1.exec())
        {
            qDebug() << "Error: Fail to insert data. " << sqlQuery1.lastError();
        }
        else
        {
            qDebug() << "Insert successfully. " << sqlQuery1.lastError();
        }

        sqlQuery1.bindValue(":id", 4);
        sqlQuery1.bindValue(":name", "思源楼");
        sqlQuery1.bindValue(":coordinate", "300，-50");
        sqlQuery1.bindValue(":introduction", "我自习最多的地方");
        if(!sqlQuery1.exec())
        {
            qDebug() << "Error: Fail to insert data. " << sqlQuery1.lastError();
        }
        else
        {
            qDebug() << "Insert successfully. " << sqlQuery1.lastError();
        }

        sqlQuery1.bindValue(":id", 5);
        sqlQuery1.bindValue(":name", "思东楼");
        sqlQuery1.bindValue(":coordinate", "450，-50");
        sqlQuery1.bindValue(":introduction", "基本没去过");
        if(!sqlQuery1.exec())
        {
            qDebug() << "Error: Fail to insert data. " << sqlQuery1.lastError();
        }
        else
        {
            qDebug() << "Insert successfully. " << sqlQuery1.lastError();
        }

        sqlQuery1.bindValue(":id", 6);
        sqlQuery1.bindValue(":name", "明湖");
        sqlQuery1.bindValue(":coordinate", "600，-150");
        sqlQuery1.bindValue(":introduction", "门前明湖下游过一群鸭，快来快来数一数！");
        if(!sqlQuery1.exec())
        {
            qDebug() << "Error: Fail to insert data. " << sqlQuery1.lastError();
        }
        else
        {
            qDebug() << "Insert successfully. " << sqlQuery1.lastError();
        }

        sqlQuery1.bindValue(":id", 7);
        sqlQuery1.bindValue(":name", "图书馆");
        sqlQuery1.bindValue(":coordinate", "750，-100");
        sqlQuery1.bindValue(":introduction", "没怎来过，但是考研人天天在这，也很难抢！");
        if(!sqlQuery1.exec())
        {
            qDebug() << "Error: Fail to insert data. " << sqlQuery1.lastError();
        }
        else
        {
            qDebug() << "Insert successfully. " << sqlQuery1.lastError();
        }

        sqlQuery1.bindValue(":id", 8);
        sqlQuery1.bindValue(":name", "逸夫楼");
        sqlQuery1.bindValue(":coordinate", "900，-20");
        sqlQuery1.bindValue(":introduction", "软院的大本营");
        if(!sqlQuery1.exec())
        {
            qDebug() << "Error: Fail to insert data. " << sqlQuery1.lastError();
        }
        else
        {
            qDebug() << "Insert successfully. " << sqlQuery1.lastError();
        }

        sqlQuery1.bindValue(":id", 9);
        sqlQuery1.bindValue(":name", "校史馆");
        sqlQuery1.bindValue(":coordinate", "150,150");
        sqlQuery1.bindValue(":introduction", "开学来过，交大的历史都在这里");
        if(!sqlQuery1.exec())
        {
            qDebug() << "Error: Fail to insert data. " << sqlQuery1.lastError();
        }
        else
        {
            qDebug() << "Insert successfully. " << sqlQuery1.lastError();
        }

        sqlQuery1.bindValue(":id", 10);
        sqlQuery1.bindValue(":name", "知行碑");
        sqlQuery1.bindValue(":coordinate", "300,175");
        sqlQuery1.bindValue(":introduction", "饮水思源，爱国荣校！");
        if(!sqlQuery1.exec())
        {
            qDebug() << "Error: Fail to insert data. " << sqlQuery1.lastError();
        }
        else
        {
            qDebug() << "Insert successfully. " << sqlQuery1.lastError();
        }
            //查询表内的数据
        QSqlQuery check1sqlQuery;
        check1sqlQuery.exec("SELECT * FROM scene");
            if(!check1sqlQuery.exec())
            {
                qDebug() << "Error: Fail to query table. " << check1sqlQuery.lastError();
            }
            else
            {
                while(check1sqlQuery.next())
                {
                    int id = check1sqlQuery.value(0).toInt();
                    QString name = check1sqlQuery.value(1).toString();
                    QString coordinate = check1sqlQuery.value(2).toString();
                    QString introduction = check1sqlQuery.value(3).toString();
                    qDebug()<<QString("id:%1    name:%2    coordinate:%3    introduction:%4").arg(id).arg(name).arg(coordinate).arg(introduction);
                }
            }

    }

}
void MainWindow::linkedatabasepath(){
    QSqlDatabase database;

    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        // 建立和SQlite数据库的连接
        database = QSqlDatabase::addDatabase("QSQLITE");
        // 设置数据库文件的名字
        database.setDatabaseName("MyDataBase2.db");
    }
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }
    else
    {
        qDebug() << "success";

        //道路信息的存储和查询
        // 用于执行sql语句的对象
        QSqlQuery sqlQuery2;
        // 检查表是否存在，如果存在则删除
        if(sqlQuery2.exec("SELECT COUNT(*) FROM sqlite_master WHERE type='table' AND name='path'"))
        {
            sqlQuery2.exec("DROP TABLE path");
        }
        // 构建创建数据库的sql语句字符串
        QString createSql2 = QString("CREATE TABLE path (\
                                     id INT PRIMARY KEY NOT NULL,\
                                     start INT NOT NULL,\
                                     end INT NOT NULL,\
                                     length INT NOT NULL,\
                                     introduction TEXT NOT NULL)");

            // 执行sql语句
            if(!sqlQuery2.exec(createSql2))
        {
            qDebug() << "Error: Fail to create table. " << sqlQuery2.lastError();
        }
        else
        {     qDebug() << "Table created!";
        }
        sqlQuery2.prepare("INSERT INTO path VALUES(:id,:start,:end,:length,:introduction)");

        sqlQuery2.bindValue(":id", 1);
        sqlQuery2.bindValue(":start", 1);
        sqlQuery2.bindValue(":end", 2);
        sqlQuery2.bindValue(":length", 303);
        sqlQuery2.bindValue(":introduction", "");
        if(!sqlQuery2.exec())
        {
            qDebug() << "Error: Fail to insert data. " << sqlQuery2.lastError();
        }
        else
        {
            qDebug() << "Insert successfully. " << sqlQuery2.lastError();
        }
        sqlQuery2.bindValue(":id", 2);
        sqlQuery2.bindValue(":start", 1);
        sqlQuery2.bindValue(":end", 3);
        sqlQuery2.bindValue(":length", 237);
        sqlQuery2.bindValue(":introduction", "");
        if(!sqlQuery2.exec())
        {
            qDebug() << "Error: Fail to insert data. " << sqlQuery2.lastError();
        }
        else
        {
            qDebug() << "Insert successfully. " << sqlQuery2.lastError();
        }
        sqlQuery2.bindValue(":id", 3);
        sqlQuery2.bindValue(":start", 1);
        sqlQuery2.bindValue(":end", 4);
        sqlQuery2.bindValue(":length", 279);
        sqlQuery2.bindValue(":introduction", "");
        if(!sqlQuery2.exec())
        {
            qDebug() << "Error: Fail to insert data. " << sqlQuery2.lastError();
        }
        else
        {
            qDebug() << "Insert successfully. " << sqlQuery2.lastError();
        }
         sqlQuery2.bindValue(":id", 4);
        sqlQuery2.bindValue(":start", 1);
        sqlQuery2.bindValue(":end", 5);
        sqlQuery2.bindValue(":length", 306);
        sqlQuery2.bindValue(":introduction", "");
        if(!sqlQuery2.exec())
        {
            qDebug() << "Error: Fail to insert data. " << sqlQuery2.lastError();
        }
        else
        {
            qDebug() << "Insert successfully. " << sqlQuery2.lastError();
        }
         sqlQuery2.bindValue(":id", 5);
        sqlQuery2.bindValue(":start", 1);
        sqlQuery2.bindValue(":end", 6);
        sqlQuery2.bindValue(":length", 324);
        sqlQuery2.bindValue(":introduction", "");
        if(!sqlQuery2.exec())
        {
            qDebug() << "Error: Fail to insert data. " << sqlQuery2.lastError();
        }
        else
        {
            qDebug() << "Insert successfully. " << sqlQuery2.lastError();
        }

         sqlQuery2.bindValue(":id", 6);
        sqlQuery2.bindValue(":start", 1);
        sqlQuery2.bindValue(":end", 7);
        sqlQuery2.bindValue(":length", 456);
        sqlQuery2.bindValue(":introduction", "");
        if(!sqlQuery2.exec())
        {
            qDebug() << "Error: Fail to insert data. " << sqlQuery2.lastError();
        }
        else
        {
            qDebug() << "Insert successfully. " << sqlQuery2.lastError();
        }
         sqlQuery2.bindValue(":id", 7);
        sqlQuery2.bindValue(":start", 1);
        sqlQuery2.bindValue(":end", 8);
        sqlQuery2.bindValue(":length", 597);
        sqlQuery2.bindValue(":introduction", "");
        if(!sqlQuery2.exec())
        {
            qDebug() << "Error: Fail to insert data. " << sqlQuery2.lastError();
        }
        else
        {
            qDebug() << "Insert successfully. " << sqlQuery2.lastError();
        }
         sqlQuery2.bindValue(":id", 8);
        sqlQuery2.bindValue(":start", 2);
        sqlQuery2.bindValue(":end",3);
        sqlQuery2.bindValue(":length", 173);
        sqlQuery2.bindValue(":introduction", "");
        if(!sqlQuery2.exec())
        {
            qDebug() << "Error: Fail to insert data. " << sqlQuery2.lastError();
        }
        else
        {
            qDebug() << "Insert successfully. " << sqlQuery2.lastError();
        }
        sqlQuery2.bindValue(":id", 9);
        sqlQuery2.bindValue(":start", 3);
        sqlQuery2.bindValue(":end", 4);
        sqlQuery2.bindValue(":length", 132);
        sqlQuery2.bindValue(":introduction", "");
        if(!sqlQuery2.exec())
        {
            qDebug() << "Error: Fail to insert data. " << sqlQuery2.lastError();
        }
        else
        {
            qDebug() << "Insert successfully. " << sqlQuery2.lastError();
        }
        sqlQuery2.bindValue(":id", 10);
        sqlQuery2.bindValue(":start", 4);
        sqlQuery2.bindValue(":end", 5);
        sqlQuery2.bindValue(":length", 146);
        sqlQuery2.bindValue(":introduction", "");
        if(!sqlQuery2.exec())
        {
            qDebug() << "Error: Fail to insert data. " << sqlQuery2.lastError();
        }
        else
        {
            qDebug() << "Insert successfully. " << sqlQuery2.lastError();}
        sqlQuery2.bindValue(":id", 11);
        sqlQuery2.bindValue(":start", 5);
        sqlQuery2.bindValue(":end", 6);
        sqlQuery2.bindValue(":length", 136);
        sqlQuery2.bindValue(":introduction", "");
        if(!sqlQuery2.exec())
        {
            qDebug() << "Error: Fail to insert data. " << sqlQuery2.lastError();
        }
        else
        {
            qDebug() << "Insert successfully. " << sqlQuery2.lastError();
        }
         sqlQuery2.bindValue(":id", 12);
        sqlQuery2.bindValue(":start", 6);
        sqlQuery2.bindValue(":end", 7);
        sqlQuery2.bindValue(":length", 192);
        sqlQuery2.bindValue(":introduction", "");
        if(!sqlQuery2.exec())
        {
            qDebug() << "Error: Fail to insert data. " << sqlQuery2.lastError();
        }
        else
        {
            qDebug() << "Insert successfully. " << sqlQuery2.lastError();}
        sqlQuery2.bindValue(":id", 13);
        sqlQuery2.bindValue(":start", 7);
        sqlQuery2.bindValue(":end", 8);
        sqlQuery2.bindValue(":length", 141);
        sqlQuery2.bindValue(":introduction", "");
        if(!sqlQuery2.exec())
        {
            qDebug() << "Error: Fail to insert data. " << sqlQuery2.lastError();
        }
        else
        {
            qDebug() << "Insert successfully. " << sqlQuery2.lastError();}
        sqlQuery2.bindValue(":id", 14);
        sqlQuery2.bindValue(":start", 9);
        sqlQuery2.bindValue(":end", 2);
        sqlQuery2.bindValue(":length", 152);
        sqlQuery2.bindValue(":introduction", "");
        if(!sqlQuery2.exec())
        {
            qDebug() << "Error: Fail to insert data. " << sqlQuery2.lastError();
        }
        else
        {
            qDebug() << "Insert successfully. " << sqlQuery2.lastError();}
        sqlQuery2.bindValue(":id", 15);
        sqlQuery2.bindValue(":start", 9);
        sqlQuery2.bindValue(":end", 3);
        sqlQuery2.bindValue(":length", 188);
        sqlQuery2.bindValue(":introduction", "");
        if(!sqlQuery2.exec())
        {
            qDebug() << "Error: Fail to insert data. " << sqlQuery2.lastError();
        }
        else
        {
            qDebug() << "Insert successfully. " << sqlQuery2.lastError();}
        sqlQuery2.bindValue(":id", 16);
        sqlQuery2.bindValue(":start", 9);
        sqlQuery2.bindValue(":end", 4);
        sqlQuery2.bindValue(":length", 207);
        sqlQuery2.bindValue(":introduction", "");
        if(!sqlQuery2.exec())
        {
            qDebug() << "Error: Fail to insert data. " << sqlQuery2.lastError();
        }
        else
        {
            qDebug() << "Insert successfully. " << sqlQuery2.lastError();}
        sqlQuery2.bindValue(":id", 17);
        sqlQuery2.bindValue(":start", 9);
        sqlQuery2.bindValue(":end", 5);
        sqlQuery2.bindValue(":length", 343);
        sqlQuery2.bindValue(":introduction", "");
        if(!sqlQuery2.exec())
        {
            qDebug() << "Error: Fail to insert data. " << sqlQuery2.lastError();
        }
        else
        {
            qDebug() << "Insert successfully. " << sqlQuery2.lastError();}
        sqlQuery2.bindValue(":id", 18);
        sqlQuery2.bindValue(":start", 9);
        sqlQuery2.bindValue(":end", 6);
        sqlQuery2.bindValue(":length", 456);
        sqlQuery2.bindValue(":introduction", "");
        if(!sqlQuery2.exec())
        {
            qDebug() << "Error: Fail to insert data. " << sqlQuery2.lastError();
        }
        else
        {
            qDebug() << "Insert successfully. " << sqlQuery2.lastError();}
        sqlQuery2.bindValue(":id", 19);
        sqlQuery2.bindValue(":start", 9);
        sqlQuery2.bindValue(":end", 7);
        sqlQuery2.bindValue(":length", 601);
        sqlQuery2.bindValue(":introduction", "");
        if(!sqlQuery2.exec())
        {
            qDebug() << "Error: Fail to insert data. " << sqlQuery2.lastError();
        }
        else
        {
            qDebug() << "Insert successfully. " << sqlQuery2.lastError();}
        sqlQuery2.bindValue(":id", 20);
        sqlQuery2.bindValue(":start", 9);
        sqlQuery2.bindValue(":end", 8);
        sqlQuery2.bindValue(":length", 676);
        sqlQuery2.bindValue(":introduction", "");
        if(!sqlQuery2.exec())
        {
            qDebug() << "Error: Fail to insert data. " << sqlQuery2.lastError();
        }
        else
        {
            qDebug() << "Insert successfully. " << sqlQuery2.lastError();
        sqlQuery2.bindValue(":id", 21);
        sqlQuery2.bindValue(":start", 10);
        sqlQuery2.bindValue(":end", 2);
        sqlQuery2.bindValue(":length", 286);
        sqlQuery2.bindValue(":introduction", "");
        if(!sqlQuery2.exec())
        {
            qDebug() << "Error: Fail to insert data. " << sqlQuery2.lastError();
        }
        else
        {
            qDebug() << "Insert successfully. " << sqlQuery2.lastError();
        }
        sqlQuery2.bindValue(":id", 22);
        sqlQuery2.bindValue(":start", 10);
        sqlQuery2.bindValue(":end", 3);
        sqlQuery2.bindValue(":length", 265);
        sqlQuery2.bindValue(":introduction", "");
        if(!sqlQuery2.exec())
        {
            qDebug() << "Error: Fail to insert data. " << sqlQuery2.lastError();
        }
        else
        {
            qDebug() << "Insert successfully. " << sqlQuery2.lastError();
        }
        sqlQuery2.bindValue(":id", 23);
        sqlQuery2.bindValue(":start", 10);
        sqlQuery2.bindValue(":end", 4);
        sqlQuery2.bindValue(":length",196);
        sqlQuery2.bindValue(":introduction", "");
        if(!sqlQuery2.exec())
        {
            qDebug() << "Error: Fail to insert data. " << sqlQuery2.lastError();
        }
        else
        {
            qDebug() << "Insert successfully. " << sqlQuery2.lastError();
        }
        sqlQuery2.bindValue(":id", 24);
        sqlQuery2.bindValue(":start", 10);
        sqlQuery2.bindValue(":end", 5);
        sqlQuery2.bindValue(":length", 257);
        sqlQuery2.bindValue(":introduction", "");
        if(!sqlQuery2.exec())
        {
            qDebug() << "Error: Fail to insert data. " << sqlQuery2.lastError();
        }
        else
        {
            qDebug() << "Insert successfully. " << sqlQuery2.lastError();
        }
        sqlQuery2.bindValue(":id", 25);
        sqlQuery2.bindValue(":start", 10);
        sqlQuery2.bindValue(":end", 6);
        sqlQuery2.bindValue(":length", 344);
        sqlQuery2.bindValue(":introduction", "");
        if(!sqlQuery2.exec())
        {
            qDebug() << "Error: Fail to insert data. " << sqlQuery2.lastError();
        }
        else
        {
            qDebug() << "Insert successfully. " << sqlQuery2.lastError();
        }
        sqlQuery2.bindValue(":id", 26);
        sqlQuery2.bindValue(":start", 10);
        sqlQuery2.bindValue(":end", 7);
        sqlQuery2.bindValue(":length", 533);
        sqlQuery2.bindValue(":introduction", "");
        if(!sqlQuery2.exec())
        {
            qDebug() << "Error: Fail to insert data. " << sqlQuery2.lastError();
        }
        else
        {
            qDebug() << "Insert successfully. " << sqlQuery2.lastError();
        }
        sqlQuery2.bindValue(":id", 27);
        sqlQuery2.bindValue(":start", 10);
        sqlQuery2.bindValue(":end", 8);
        sqlQuery2.bindValue(":length", 605);
        sqlQuery2.bindValue(":introduction", "");
        if(!sqlQuery2.exec())
        {
            qDebug() << "Error: Fail to insert data. " << sqlQuery2.lastError();
        }
        else
        {
            qDebug() << "Insert successfully. " << sqlQuery2.lastError();
        }
        sqlQuery2.bindValue(":id", 28);
        sqlQuery2.bindValue(":start", 9);
        sqlQuery2.bindValue(":end", 10);
        sqlQuery2.bindValue(":length", 144);
        sqlQuery2.bindValue(":introduction", "");
        if(!sqlQuery2.exec())
        {
            qDebug() << "Error: Fail to insert data. " << sqlQuery2.lastError();
        }
        else
        {
            qDebug() << "Insert successfully. " << sqlQuery2.lastError();
        }


        //查询表内的数据
        sqlQuery2.exec("SELECT * FROM path");
        if(!sqlQuery2.exec())
        {
            qDebug() << "Error: Fail to query table. " << sqlQuery2.lastError();
        }
        else
        {
            while(sqlQuery2.next())
            {
                int id=sqlQuery2.value(0).toInt();
                int start = sqlQuery2.value(1).toInt();
                int end = sqlQuery2.value(2).toInt();
                int length = sqlQuery2.value(3).toInt();
                QString introduction = sqlQuery2.value(4).toString();
                qDebug()<<QString("id:%1  start:%2    end:%3    length:%4    introduction:%5").arg(id).arg(start).arg(end).arg(length).arg(introduction);
            }
        }


        }

        }
}

//初始化
void MainWindow::Initmap(){

    //对景点实际含义进行记录
    arr[1]=GYM;
    arr[2]=XUEHUO;
    arr[3]=SX;
    arr[4]=SY;
    arr[5]=SD;
    arr[6]=Lake;
    arr[7]=Library;
    arr[8]=YF;
    arr[9]=HISTORY;
    arr[10]=ZHIXING;

    ui->graphicsView->setScene(scene);
    // qDebug()<<ui->gym->x()<<ui->gym->y()<<ui->xuehuo->x()<<ui->xuehuo->y();
    // // 使用 QPen 设置线的属性，包括颜色
    // QPen pen;
    // pen.setColor(Qt::red);  // 设置线的颜色为红色
    // item1->setPen(pen);
    XUEHUO->setText("2:学活");
    XUEHUO->move(0,0);
    scene->addWidget(XUEHUO);

    SX->setText("3:思西");
    SX->move(150,-50);
    scene->addWidget(SX);

    YF->setText("8:逸夫楼");
    YF->move(900,-20);
    scene->addWidget(YF);

    GYM->setText("1:体育馆");
    GYM->move(75,-300);
    scene->addWidget(GYM);

    HISTORY->setText("9:校史馆");
    HISTORY->move(150,150);
    scene->addWidget(HISTORY);


    SY->setText("4:思源");
    SY->move(300,-50);
    scene->addWidget(SY);


    ZHIXING->setText("10:知行碑");
    ZHIXING->move(300,175);
    scene->addWidget(ZHIXING);


    SD->setText("5:思东");
    SD->move(450,-50);
    scene->addWidget(SD);


    Lake->setText("6:明湖");
    Lake->move(600,-150);
    scene->addWidget(Lake);


    Library->setText("7:图书馆");
    Library->move(750,-100);
    scene->addWidget(Library);

    // 创建线条项并添加到场景
    QGraphicsLineItem* item1 = new QGraphicsLineItem(arr[1]->x(),GYM->y(),XUEHUO->x(),XUEHUO->y());
    scene->addItem(item1);
    QGraphicsLineItem* item2 = new QGraphicsLineItem(GYM->x(),GYM->y(),SX->x(),SX->y());
    scene->addItem(item2);
    QGraphicsLineItem* item3 = new QGraphicsLineItem(GYM->x(),GYM->y(),SY->x(),SY->y());
    scene->addItem(item3);
    QGraphicsLineItem* item4 = new QGraphicsLineItem(GYM->x(),GYM->y(),SD->x(),SD->y());
    scene->addItem(item4);
    QGraphicsLineItem* item5 = new QGraphicsLineItem(GYM->x(),GYM->y(),YF->x(),YF->y());
    scene->addItem(item5);
    QGraphicsLineItem* item6 = new QGraphicsLineItem(GYM->x(),GYM->y(),Lake->x(),Lake->y());
    scene->addItem(item6);
    QGraphicsLineItem* item7 = new QGraphicsLineItem(GYM->x(),GYM->y(),Library->x(),Library->y());
    scene->addItem(item7);

    QLabel *label1=new QLabel("303");
    label1->move((GYM->x()+XUEHUO->x())/2,(XUEHUO->y()+GYM->y())/2);
    scene->addWidget(label1);
    QLabel *label2=new QLabel("237");
    label2->move((GYM->x()+SX->x())/2,(GYM->y()+SX->y())/2);
    scene->addWidget(label2);
    QLabel *label3=new QLabel("279");
    label3->move((GYM->x()+SY->x())/2,(GYM->y()+SY->y())/2);
    scene->addWidget(label3);
    QLabel *label4=new QLabel("306");
    label4->move((GYM->x()+SD->x())/2,(GYM->y()+SD->y())/2);
    scene->addWidget(label4);
    QLabel *label5=new QLabel("324");
    label5->move((GYM->x()+Lake->x())/2,(GYM->y()+Lake->y())/2);
    scene->addWidget(label5);
    QLabel *label6=new QLabel("456");
    label6->move((GYM->x()+Library->x())/2,(GYM->y()+Library->y())/2);
    scene->addWidget(label6);
    QLabel *label7=new QLabel("597");
    label7->move((GYM->x()+ YF->x())/2,(GYM->y()+YF->y())/2);
    scene->addWidget(label7);




    QGraphicsLineItem* item8 = new QGraphicsLineItem(XUEHUO->x(),XUEHUO->y(),SX->x(),SX->y());
    scene->addItem(item8);
    QGraphicsLineItem* item9 = new QGraphicsLineItem(SX->x(),SX->y(),SY->x(),SY->y());
    scene->addItem(item9);
    QGraphicsLineItem* item10 = new QGraphicsLineItem(SY->x(),SY->y(),SD->x(),SD->y());
    scene->addItem(item10);
    QGraphicsLineItem* item11 = new QGraphicsLineItem(SD->x(),SD->y(),Lake->x(),Lake->y());
    scene->addItem(item11);
    QGraphicsLineItem* item12 = new QGraphicsLineItem(Lake->x(),Lake->y(),Library->x(),Library->y());
    scene->addItem(item12);
    QGraphicsLineItem* item13 = new QGraphicsLineItem(Library->x(),Library->y(),YF->x(),YF->y());
    scene->addItem(item13);

    QLabel *label8=new QLabel("173");
    label8->move((XUEHUO->x()+ SX->x())/2,(XUEHUO->y()+SX->y())/2);
    scene->addWidget(label8);
    QLabel *label9=new QLabel("132");
    label9->move((SX->x()+ SY->x())/2,(SX->y()+SY->y())/2);
    scene->addWidget(label9);
    QLabel *label10=new QLabel("146");
    label10->move((SY->x()+ SD->x())/2,(SY->y()+SD->y())/2);
    scene->addWidget(label10);
    QLabel *label11=new QLabel("136");
    label11->move((SD->x()+ Lake->x())/2,(SD->y()+Lake->y())/2);
    scene->addWidget(label11);
    QLabel *label12=new QLabel("192");
    label12->move((Lake->x()+ Library->x())/2,(Library->y()+Lake->y())/2);
    scene->addWidget(label12);
    QLabel *label13=new QLabel("141");
    label13->move((Library->x()+ YF->x())/2,(Library->y()+YF->y())/2);
    scene->addWidget(label13);


    QGraphicsLineItem* item14 = new QGraphicsLineItem(HISTORY->x(),HISTORY->y(),XUEHUO->x(),XUEHUO->y());
    scene->addItem(item14);
    QGraphicsLineItem* item15 = new QGraphicsLineItem(HISTORY->x(),HISTORY->y(),SX->x(),SX->y());
    scene->addItem(item15);
    QGraphicsLineItem* item16 = new QGraphicsLineItem(HISTORY->x(),HISTORY->y(),SY->x(),SY->y());
    scene->addItem(item16);
    QGraphicsLineItem* item17 = new QGraphicsLineItem(HISTORY->x(),HISTORY->y(),SD->x(),SD->y());
    scene->addItem(item17);
    QGraphicsLineItem* item18 = new QGraphicsLineItem(HISTORY->x(),HISTORY->y(),Lake->x(),Lake->y());
    scene->addItem(item18);
    QGraphicsLineItem* item19 = new QGraphicsLineItem(HISTORY->x(),HISTORY->y(),Library->x(),Library->y());
    scene->addItem(item19);
    QGraphicsLineItem* item20 = new QGraphicsLineItem(HISTORY->x(),HISTORY->y(),YF->x(),YF->y());
    scene->addItem(item20);

    QLabel *label14=new QLabel("152");
    label14->move((HISTORY->x()+ XUEHUO->x())/2,(HISTORY->y()+XUEHUO->y())/2);
    scene->addWidget(label14);
    QLabel *label15=new QLabel("188");
    label15->move((HISTORY->x()+ SX->x())/2,(HISTORY->y()+SX->y())/2);
    scene->addWidget(label15);
    QLabel *label16=new QLabel("207");
    label16->move((HISTORY->x()+ SY->x())/2,(HISTORY->y()+SY->y())/2);
    scene->addWidget(label16);
    QLabel *label17=new QLabel("343");
    label17->move((HISTORY->x()+ SD->x())/2,(HISTORY->y()+SD->y())/2);
    scene->addWidget(label17);
    QLabel *label18=new QLabel("456");
    label18->move((HISTORY->x()+ Lake->x())/2,(HISTORY->y()+Lake->y())/2);
    scene->addWidget(label18);
    QLabel *label19=new QLabel("601");
    label19->move((HISTORY->x()+ Library->x())/2,(HISTORY->y()+Library->y())/2);
    scene->addWidget(label19);
    QLabel *label20=new QLabel("676");
    label20->move((HISTORY->x()+ YF->x())/2,(HISTORY->y()+YF->y())/2);
    scene->addWidget(label20);



    QGraphicsLineItem* item21 = new QGraphicsLineItem(ZHIXING->x(),ZHIXING->y(),XUEHUO->x(),XUEHUO->y());
    scene->addItem(item21);
    QGraphicsLineItem* item23 = new QGraphicsLineItem(ZHIXING->x(),ZHIXING->y(),SX->x(),SX->y());
    scene->addItem(item23);
    QGraphicsLineItem* item22 = new QGraphicsLineItem(ZHIXING->x(),ZHIXING->y(),SY->x(),SY->y());
    scene->addItem(item22);
    QGraphicsLineItem* item24 = new QGraphicsLineItem(ZHIXING->x(),ZHIXING->y(),SD->x(),SD->y());
    scene->addItem(item24);
    QGraphicsLineItem* item25 = new QGraphicsLineItem(ZHIXING->x(),ZHIXING->y(),Lake->x(),Lake->y());
    scene->addItem(item25);
    QGraphicsLineItem* item26 = new QGraphicsLineItem(ZHIXING->x(),ZHIXING->y(),Library->x(),Library->y());
    scene->addItem(item26);
    QGraphicsLineItem* item27 = new QGraphicsLineItem(ZHIXING->x(),ZHIXING->y(),YF->x(),YF->y());
    scene->addItem(item27);
    QLabel *label21=new QLabel("286");
    label21->move((ZHIXING->x()+ XUEHUO->x())/2,(ZHIXING->y()+XUEHUO->y())/2);
    scene->addWidget(label21);
    QLabel *label22=new QLabel("265");
    label22->move((ZHIXING->x()+ SX->x())/2,(ZHIXING->y()+SX->y())/2);
    scene->addWidget(label22);
    QLabel *label23=new QLabel("196");
    label23->move((ZHIXING->x()+ SY->x())/2,(ZHIXING->y()+SY->y())/2);
    scene->addWidget(label23);
    QLabel *label24=new QLabel("257");
    label24->move((ZHIXING->x()+ SD->x())/2,(ZHIXING->y()+SD->y())/2);
    scene->addWidget(label24);
    QLabel *label25=new QLabel("344");
    label25->move((ZHIXING->x()+ Lake->x())/2,(ZHIXING->y()+Lake->y())/2);
    scene->addWidget(label25);
    QLabel *label26=new QLabel("533");
    label26->move((ZHIXING->x()+ Library->x())/2,(ZHIXING->y()+Library->y())/2);
    scene->addWidget(label26);
    QLabel *label27=new QLabel("605");
    label27->move((ZHIXING->x()+ YF->x())/2,(ZHIXING->y()+YF->y())/2);
    scene->addWidget(label27);


    QGraphicsLineItem* item28 = new QGraphicsLineItem(HISTORY->x(),HISTORY->y(),ZHIXING->x(),ZHIXING->y());
    scene->addItem(item28);
    QLabel *label28=new QLabel("144");
    label28->move((ZHIXING->x()+ HISTORY->x())/2,(ZHIXING->y()+HISTORY->y())/2);
    scene->addWidget(label28);



}


void MainWindow::on_gym_clicked()
{
    QDialog dialog;
    dialog.setWindowTitle("体育馆！");
    dialog.setGeometry(0,0,400,400);

    // 添加图片
    QLabel *imageLabel = new QLabel(&dialog);
    QPixmap pixmap(":/back/image/OIP.jpg");
    imageLabel->setPixmap(pixmap);

    // 添加编辑框
    QTextEdit *editBox = new QTextEdit(&dialog);
    editBox->setText("嘿嘿嘿，最喜欢的地方，每个礼拜来健身");

    // 创建垂直布局，将图片和编辑框添加到布局中
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(imageLabel);
    layout->addWidget(editBox);

    // 将布局设置为对话框的布局
    dialog.setLayout(layout);

    // 显示对话框并运行程序
    dialog.exec();
}


void MainWindow::on_xuehuo_clicked()
{
    QDialog dialog;
    dialog.setWindowTitle("学活！");
    dialog.setGeometry(0,0,400,400);

    // 添加图片
    QLabel *imageLabel = new QLabel(&dialog);
    QPixmap pixmap(":/back/image/xuehuo.jpg");
    imageLabel->setPixmap(pixmap);

    // 添加编辑框
    QTextEdit *editBox = new QTextEdit(&dialog);
    editBox->setText("饭很好吃");

    // 创建垂直布局，将图片和编辑框添加到布局中
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(imageLabel);
    layout->addWidget(editBox);

    // 将布局设置为对话框的布局
    dialog.setLayout(layout);

    // 显示对话框并运行程序
    dialog.exec();
}


void MainWindow::on_sx_clicked()
{
    QDialog dialog;
    dialog.setWindowTitle("思西楼！");
    dialog.setGeometry(0,0,400,400);

    // 添加图片
    QLabel *imageLabel = new QLabel(&dialog);
    QPixmap pixmap(":/back/image/SX.png");
    imageLabel->setPixmap(pixmap);

    // 添加编辑框
    QTextEdit *editBox = new QTextEdit(&dialog);
    editBox->setText("还不错，高楼层的自习区域很不错");

    // 创建垂直布局，将图片和编辑框添加到布局中
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(imageLabel);
    layout->addWidget(editBox);

    // 将布局设置为对话框的布局
    dialog.setLayout(layout);

    // 显示对话框并运行程序
    dialog.exec();
}


void MainWindow::on_sy_clicked()
{
    QDialog dialog;
    dialog.setWindowTitle("思源楼！");
    dialog.setGeometry(0,0,500,500);

    // 添加图片
    QLabel *imageLabel = new QLabel(&dialog);
    QPixmap pixmap(":/back/image/SY.jpg");
    imageLabel->setPixmap(pixmap);

    // 添加编辑框
    QTextEdit *editBox = new QTextEdit(&dialog);
    editBox->setText("我自习最多的地方");

    // 创建垂直布局，将图片和编辑框添加到布局中
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(imageLabel);
    layout->addWidget(editBox);

    // 将布局设置为对话框的布局
    dialog.setLayout(layout);

    // 显示对话框并运行程序
    dialog.exec();
}


void MainWindow::on_sd_clicked()
{
    QDialog dialog;
    dialog.setWindowTitle("思东楼！");
    dialog.setGeometry(0,0,600,400);

    // 添加图片
    QLabel *imageLabel = new QLabel(&dialog);
    QPixmap pixmap(":/back/image/sd.jpg");
    imageLabel->setPixmap(pixmap);

    // 添加编辑框
    QTextEdit *editBox = new QTextEdit(&dialog);
    editBox->setText("基本没去过");

    // 创建垂直布局，将图片和编辑框添加到布局中
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(imageLabel);
    layout->addWidget(editBox);

    // 将布局设置为对话框的布局
    dialog.setLayout(layout);

    // 显示对话框并运行程序
    dialog.exec();
}


void MainWindow::on_minghu_clicked()
{
    QDialog dialog;
    dialog.setWindowTitle("明湖！");
    dialog.setGeometry(0,0,800,500);

    // 添加图片
    QLabel *imageLabel = new QLabel(&dialog);
    QPixmap pixmap(":/back/image/Lake.jpg");
    imageLabel->setPixmap(pixmap);

    // 添加编辑框
    QTextEdit *editBox = new QTextEdit(&dialog);
    editBox->setText("门前明湖下游过一群鸭，快来快来数一数！");

    // 创建垂直布局，将图片和编辑框添加到布局中
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(imageLabel);
    layout->addWidget(editBox);

    // 将布局设置为对话框的布局
    dialog.setLayout(layout);

    // 显示对话框并运行程序
    dialog.exec();
}


void MainWindow::on_library_clicked()
{
    QDialog dialog;
    dialog.setWindowTitle("图书馆！");
    dialog.setGeometry(0,0,800,600);

    // 添加图片
    QLabel *imageLabel = new QLabel(&dialog);
    QPixmap pixmap(":/back/image/Library (1).jpg");
    imageLabel->setPixmap(pixmap);

    // 添加编辑框
    QTextEdit *editBox = new QTextEdit(&dialog);
    editBox->setText("没怎来过，但是考研人天天在这，也很难抢！");

    // 创建垂直布局，将图片和编辑框添加到布局中
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(imageLabel);
    layout->addWidget(editBox);

    // 将布局设置为对话框的布局
    dialog.setLayout(layout);

    // 显示对话框并运行程序
    dialog.exec();
}


void MainWindow::on_yf_clicked()
{
    QDialog dialog;
    dialog.setWindowTitle("逸夫楼！");
    dialog.setGeometry(0,0,650,500);

    // 添加图片
    QLabel *imageLabel = new QLabel(&dialog);
    QPixmap pixmap(":/back/image/YF.jpg");
    imageLabel->setPixmap(pixmap);

    // 添加编辑框
    QTextEdit *editBox = new QTextEdit(&dialog);
    editBox->setText("软院的大本营");

    // 创建垂直布局，将图片和编辑框添加到布局中
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(imageLabel);
    layout->addWidget(editBox);

    // 将布局设置为对话框的布局
    dialog.setLayout(layout);

    // 显示对话框并运行程序
    dialog.exec();
}


void MainWindow::on_history_clicked()
{
    QDialog dialog;
    dialog.setWindowTitle("校史馆！");
    dialog.setGeometry(0,0,500,500);

    // 添加图片
    QLabel *imageLabel = new QLabel(&dialog);
    QPixmap pixmap(":/back/image/History.jpg");
    imageLabel->setPixmap(pixmap);

    // 添加编辑框
    QTextEdit *editBox = new QTextEdit(&dialog);
    editBox->setText("开学来过，交大的历史都在这里");

    // 创建垂直布局，将图片和编辑框添加到布局中
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(imageLabel);
    layout->addWidget(editBox);

    // 将布局设置为对话框的布局
    dialog.setLayout(layout);

    // 显示对话框并运行程序
    dialog.exec();
}


void MainWindow::on_do_2_clicked()
{
    QDialog dialog;
    dialog.setWindowTitle("知行碑！");
    dialog.setGeometry(0,0,350,600);

    // 添加图片
    QLabel *imageLabel = new QLabel(&dialog);
    QPixmap pixmap(":/back/image/ZHIXING.jpg");
    imageLabel->setPixmap(pixmap);

    // 添加编辑框
    QTextEdit *editBox = new QTextEdit(&dialog);
    editBox->setText("饮水思源，爱国荣校！");

    // 创建垂直布局，将图片和编辑框添加到布局中
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(imageLabel);
    layout->addWidget(editBox);

    // 将布局设置为对话框的布局
    dialog.setLayout(layout);

    // 显示对话框并运行程序
    dialog.exec();
}

void MainWindow::InitEset(Eset *E,AMGraph *G){
    int k=0;
    //因为是无向矩阵，所以遍历上三角就可以了
    for (int  i= 0;  i< G->vertices; ++i) {
        for (int j= i+1; j< G->vertices; ++j) {
            if(G->edge[i][j]>0){
            E[k].start=i;
            E[k].end=j;
            E[k].weight=G->edge[i][j];
            k++;
            }
        }
    }

}
//冒泡排序
void MainWindow::Sort_Eset(Eset *E,int length){
    bool flag=true;
    for(int i=0;i<length-1&&flag;i++){//如果没有发生交换则代表有序
        flag=false;
        for (int var = 0; var < length-1; ++var) {
            if(E[var].weight>E[var+1].weight){
                flag=true;
                Eset temp=E[var];
                E[var]=E[var+1];
                E[var+1]=temp;
            }
        }
    }
}
void MainWindow::Krusal(AMGraph *G){
    //删除所有的线条
    QList<QGraphicsItem *> items = scene->items();
    for (QGraphicsItem *item : items) {
        if (item->type() == QGraphicsLineItem::Type) {
            scene->removeItem(item);
        }
    }

    Eset *E=new Eset[G->edges];
    InitEset(E,G);
    Sort_Eset(E,G->edges);
    //此时E图中的边为升序
    //建立V集合存放连通依赖点
    int V[28];
    for (int var = 0; var < G->vertices; ++var) {
        V[var]=var;
    }//先假设每一个独立点都为自己的连通依赖点，即所有点不相互邻接

    //依据边的信息，把点连接起来
    for (int var = 0; var < G->edges; ++var) {
        //找到边的两端
        int v1=E[var].start;
        int v2=E[var].end;

        //找到各自所属的连通分量所代表的编号
        int component1=V[v1];
        int component2=V[v2];
        //如果不相等，则可以连接起来
        if(component1!=component2){
            //在GUI界面绘制图形
            QGraphicsLineItem* item = new QGraphicsLineItem(arr[v1+1]->x(),arr[v1+1]->y(),arr[v2+1]->x(),arr[v2+1]->y());
            // 使用 QPen 设置线的属性，包括颜色
            QPen pen;
            pen.setColor(Qt::red);  // 设置线的颜色为红色
            item->setPen(pen);
            scene->addItem(item);
            //找到v2连通分量的所有点，将它的编号与v1相同
            for (int var = 0; var < G->vertices; ++var) {
                if(V[var]==component2){
                    V[var]=component1;
                }
            }
        }
    }
    delete []E;

}

void MainWindow::on_pushButton_3_clicked()
{
    Krusal(g->G);
}

///
///
///
///
///
///
///
///
void MainWindow::on_pushButton_2_clicked()
{
    int a1=ui->lineEdit->text().toInt();
    int a2=ui->lineEdit_2->text().toInt();
    sp_Dijkstra(g->G,a1,a2);
    //ui->textEdit->append("深度优先探索两点之间的可达路径");
    // DFS_AMGraph(g->G,a1,a2);
    ui->textEdit->append("所有可能的路径为");
    getPathofTwoNode(a1-1,a2-1);

}




void MainWindow::sp_Dijkstra(AMGraph *G,int v,int end){
    //判断所有端点到起始点的最短距离
    int index=v-1;
    int endindex=end-1;
    int *path=new int[G->vertices];
    sp(G,index,path);

    QStack <int>S;
    S.push(endindex);
    endindex=path[endindex];
    while(endindex!=index){
        S.push(endindex);
        endindex=path[endindex];
    }
    //开始画线
    int head=index;
    int pop;
    ui->textEdit->append("开始给出两景点之间的推荐路线");
    //景点之间的距离
    int length=0;

    //删除所有的线条
    QList<QGraphicsItem *> items = scene->items();
    for (QGraphicsItem *item : items) {
        if (item->type() == QGraphicsLineItem::Type) {
            scene->removeItem(item);
        }
    }

    while(!S.isEmpty()){
        pop=S.pop();

        //在GUI界面绘制图形
        QGraphicsLineItem* item = new QGraphicsLineItem(arr[head+1]->x(),arr[head+1]->y(),arr[pop+1]->x(),arr[pop+1]->y());
        length+=g->G->edge[head][pop];
        // 使用 QPen 设置线的属性，包括颜色
        QPen pen;
        pen.setColor(Qt::red);  // 设置线的颜色为红色
        item->setPen(pen);
        scene->addItem(item);


        head=pop;
    }
    ui->textEdit->append(QString::number(v)+"和"+QString::number(end)+"之间的最短路径为"+QString::number(length));



    delete []path;



}
int* MainWindow::sp(AMGraph *G,int v,int *path){
    //D表示各个顶点到v的距离
    //int D[G->vertices];
    int D[10];
    //集合S，如果点在S中则为true
    bool S[10];

    for (int i = 0; i < G->vertices; ++i) {
        //初始化变量
        if(G->edge[v][i]==0){
            D[i]=100000;
        }
        else{
            D[i]=G->edge[v][i];
        }

        S[i]=false;
        if(D[i]<100000){
            path[i]=v;
        }
        else{
            path[i]=-1;
        }
    }
    S[v]=true;
    D[v]=0;
    //初始化全部完成


    for (int source_var = 1; source_var < G->vertices; ++source_var) {
        //外循环，共需要顶点数次的遍历来确定最终的最短路径
        int min_index;
        int min=100000;

        for (int target_var = 0; target_var < G->vertices; ++target_var) {
            // 从D中选出最短的路径放入S中
        if(!S[target_var]&&D[target_var]<min){
                min_index=target_var;
                min=D[target_var];
                //找出最短的路径
        }

     }
        // 把该点放入S中
    S[min_index]=true;
        for (int adjacent_var = 0; adjacent_var < G->vertices; ++adjacent_var) {

            //这一行代码改了我一晚上
            //!
            //!
            //!
            //!
            //!
            //!
            //!
            //!
            //!
            //!
            //!
            //!
            //!
        if(!S[adjacent_var]&&((G->edge[min_index][adjacent_var]+D[min_index])<D[adjacent_var])&&G->edge[min_index][adjacent_var]!=0){
                // 遍历min_index的邻接点，进行判断
                D[adjacent_var]=G->edge[min_index][adjacent_var]+D[min_index];
                path[adjacent_var]=min_index;
            }


        }

    }
    return path;
   \
\
}


//交互式的信息展示
void MainWindow::on_pushButton_clicked()
{
    QList<QGraphicsItem *> items = scene->items();
    for (QGraphicsItem *item : items) {
        if (item->type() == QGraphicsLineItem::Type) {
            scene->removeItem(item);
        }
    }
}


void MainWindow::on_pushButton_4_clicked()
{
    Initmap();
}
//深度优先求路径
void MainWindow::DFS(AMGraph *G, int v, int end, bool visited[10], QString string) {
    visited[v] = true;

    for (int var = 0; var < G->vertices; ++var) {
        if(G->edge[v][var] > 0 && !visited[var]) {
            string += "-";
            string += QString::number(var + 1);
            if(var == end) {
                ui->textEdit->append(string);
                continue;

            } else {
                DFS(G, var, end, visited, string);
            }
            //visited[var] = false;  // Reset visited flag for backtracking
        }
    }



}

void MainWindow::DFS_AMGraph(AMGraph *G, int start, int end) {
    bool visited[10] = {false};
    QString string = "";
    //std::stack<int> path;
    string += QString::number(start);
    DFS(G, start - 1, end - 1, visited, string);

}
//所有路径
void MainWindow::getPathofTwoNode(int startNode, int endNode)
{
    //利用深度优先遍历的方式来计算两个节点之间的所有路径
    visit[startNode] = true;
    stackV.push_back(startNode);
    findPath(startNode, endNode);
}

void MainWindow::findPath(int startNode, int endNode)
{
    if (startNode == endNode)
    {
        //找到一条路径，输出路径
        QString string="";
        for (int node : stackV)
            string+=QString::number(node+1)+"-";
        ui->textEdit->append(string);

        visit[*(stackV.end()-1)] = false;
        stackV.pop_back();
        return;
    }
    else
    {
        //找到startNode所有没有入栈的邻接点
        //int unStackedNum = 0;
        for (int i = 0; i<g->G->vertices; i++)
        {
            if (g->G->edge[startNode][i] && !visit[i])
            {
                //unStackedNum++;
                visit[i] = true;
                stackV.push_back(i);
                findPath(i, endNode);
            }
        }
        visit[*(stackV.end() - 1)] = false;
        stackV.pop_back();
    }

}




//多个景点之间的最短路径
void MainWindow::on_pushButton_5_clicked()
{
    //清除线条
    QList<QGraphicsItem *> items = scene->items();
    for (QGraphicsItem *item : items) {
        if (item->type() == QGraphicsLineItem::Type) {
            scene->removeItem(item);
        }
    }

    QString str = ui->lineEdit_4->text();
    QStringList list = str.split(',');
    std::map<int *, int> unvisit;
    std::map<int *, int> visit;
    // std::pmr::vector<int *> unvisit;
    // std::pmr::vector<int *> visit;
    int temparr[10]={0};
    int num=0;
    for(const QString &s : list) {
        //存入序号
        int *path=new int[g->G->vertices];
        path=sp(g->G,s.toInt()-1,path);
        unvisit.insert(std::make_pair(path,s.toInt()-1));
        //unvisit.push_back(path);
        temparr[num]=s.toInt()-1;
        //qDebug()<<s;
        num++;
    }
    //现在的i为所有的游历景点数
    //qDebug()<<i;

    auto it=unvisit.begin();
    visit.insert(std::make_pair(it->first,it->second));
    unvisit.erase(it);
    //visit.push_back(unvisit.back());
    //unvisit.pop_back();

    //得到所有最短路径的path
    for (int var = 1; var < num; ++var) {
        //外循环代表需要几个path求最短
        int minpath=100000;
        QStack <int> printv;

        for (const auto& pair : visit) {
            //每次要遍历的path数量取决于这是第几次外循环
            int *path=pair.first;
            for (const auto& pair1 : unvisit) {
                //可能出现的最短路径一定不是访问过的，只要求未访问过的到这个顶点的最短路径
                QStack <int> tempprintv;
                QStack <int>S;
                //终点序号
                int tempj=pair1.second;
                tempprintv.push(tempj);
                S.push(tempj);
                tempj=path[tempj];
                //它的起始顶点序号是]
                while(tempj!=pair.second)
                {
                    S.push(tempj);
                    tempj=path[tempj];
                    tempprintv.push(tempj);

                }
                //求这个最短路径的长度
                int head=pair.second;
                tempprintv.push(pair.second);
                int pop;
                //景点之间的距离
                int length=0;
                while(!S.isEmpty()){
                    pop=S.pop();
                    length+=g->G->edge[head][pop];
                    head=pop;
                }
                if(length<minpath){
                    minpath=length;
                    printv=tempprintv;

                }
            }

        }

        //开始画线

        int head=printv.pop();
        int pop;
        while(!printv.isEmpty()){
            pop=printv.pop();

            //在GUI界面绘制图形
            QGraphicsLineItem* item = new QGraphicsLineItem(arr[head+1]->x(),arr[head+1]->y(),arr[pop+1]->x(),arr[pop+1]->y());
            // 使用 QPen 设置线的属性，包括颜色
            QPen pen;
            pen.setColor(Qt::red);  // 设置线的颜色为红色
            item->setPen(pen);
            scene->addItem(item);
            head=pop;
        }
        // 通过value访问map的pair
        auto tempauto=unvisit.begin();

        for (; tempauto != unvisit.end(); ++tempauto) {
            if(tempauto->second==head){
                break;
            }
        }
        visit.insert(std::make_pair(tempauto->first,tempauto->second));
        unvisit.erase(tempauto);


    }

}

