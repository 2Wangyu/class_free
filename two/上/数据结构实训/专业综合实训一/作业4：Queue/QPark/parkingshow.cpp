#include "parkingshow.h"
#include "ui_parkingshow.h"
#include<QMessageBox>
#include<QGraphicsItem>
#include<QVector>
#include"Park.h"
#include<QDate>
#include<QDateTime>
#include<QTimer>
#include<QGraphicsPixmapItem>
#include<QThread>
#include<QPropertyAnimation>
#include<QLabel>
#include<QApplication>
#include<QPushButton>
#include"linechartwidget.h"
#include<QString>
#include<random>
#include <chrono>
#include<string>
#include<QChar>
#include<QGraphicsLineItem>
#include<QDebug>
#include <QFile>
#include <QTextStream>


ParkingShow::ParkingShow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ParkingShow)
{


    ui->setupUi(this);


}

ParkingShow::~ParkingShow()
{
    delete ui;
}


void ParkingShow::on_start_clicked()
{

    for(int i=0;i<100;i++){
        QPixmap pixmap(":/car/img/car.jpg");
        QGraphicsPixmapItem *map=new QGraphicsPixmapItem(pixmap);
        items.append(map);
}
//输入参数开始停车
    if(ui->carnum->text()==NULL||ui->waitnum->text()==NULL){
        //弹出需要输入数字的提醒
        QMessageBox *box1=new QMessageBox();
        QString string="please enter the waiting num or parknum!";
        box1->setText(string);
        box1->setWindowTitle("warning!");
        box1->exec();
    }
    else{
        //对一些内容进行展示
        int num=ui->carnum->text().toInt();
        ui->emptycar->setText(QString::number(num));
        carPark=new QVector<Park>(num);

        //当前日期的显示
        QDateTime dt;
        QDate date;
        dt.setDate(date.currentDate());
        QString currentDate = dt.toString("yyyy:MM:dd");
        ui->data->setText(currentDate);


        //时间显示
        QTimer * timer1;   // 新建一个时间定时器
        timer1 = new QTimer;
        connect(timer1,&QTimer::timeout,this,&ParkingShow::showTime);   // 信号连接 每一秒执行一次槽函数
        timer1->start(1000);

        ui->graphicsView->setScene(scene);
        //对停车场场位初始化
        initGraphic(num);





            //car->outtime=ui->time->text();
            //ui->textEdit_2->append("入口"+QString::number(car->enter)+":"+car->name+" 在"+car.outtime+"已经出库.车位："+car->num+
                                   //"此次收费："+ car->money);



        }

}








void ParkingShow::initGraphic(int num){

    for(int i=0;i<num;i++){
    QGraphicsRectItem *rect2 = new QGraphicsRectItem(100*i, 0, 50, 100);
    rect2->setBrush(Qt::red);
     //rect2->setPos(-1100+100*i,80);
    scene->addItem(rect2);


    Park* park=new Park(100*i,0,i+1,nullptr);
    carPark->replace(i,*park);
    //carPark->insert(i+1,*park);


    }
    QGraphicsLineItem *linein=new QGraphicsLineItem(-100,-100,-100,100);
    QGraphicsLineItem *linein1=new QGraphicsLineItem(-100,150,-100,200);
    QGraphicsLineItem *lineout=new QGraphicsLineItem(100*num,-100,100*num,100);
     QGraphicsLineItem *lineout1=new QGraphicsLineItem(100*num,150,100*num,200);
    scene->addItem(linein);
    scene->addItem(linein1);
    scene->addItem(lineout);
    scene->addItem(lineout1);

    ui->graphicsView->show();
    ui->textEdit->append("停车场已经就绪！");
    ui->textEdit->append("开始停车！");



}





void ParkingShow::on_enter1_clicked()
{
    if(ui->newcar->text()==NULL){
        QMessageBox *box1=new QMessageBox();
        QString string="请输入进入停车场的车牌!";
        box1->setText(string);
        box1->setWindowTitle("warning!");
        box1->exec();
    }
    else{

        int num=ui->lineEdit_enter1->text().toInt()+1;
        if(num>ui->waitnum->text().toInt()){
           QMessageBox *box1=new QMessageBox();
           QString string="已超出最大排队数目!";
           box1->setText(string);
           box1->setWindowTitle("warning!");
           box1->exec();
                                   }
        else{
        ui->lineEdit_enter1->setText(QString::number(num));
        Car *car=new Car(ui->newcar->text(),1);
        queue1->EnQueue(car);
        ui->textEdit->append("入口1："+ui->time->text()+" "+car->name+" 开始排队");

    }
}


}

void ParkingShow::on_enter2_clicked()
{

    if(ui->newcar->text()==NULL){
        QMessageBox *box1=new QMessageBox();
        QString string="请输入进入停车场的车牌!";
        box1->setText(string);
        box1->setWindowTitle("warning!");
        box1->exec();
    }
    else{
    int num=ui->lineEdit_enter2->text().toInt()+1;
    if(num>ui->waitnum->text().toInt()){
        QMessageBox *box1=new QMessageBox();
        QString string="已超出最大排队数目!";
        box1->setText(string);
        box1->setWindowTitle("warning!");
        box1->exec();
    }
    else{
    ui->lineEdit_enter2->setText(QString::number(num));
    Car *car=new Car(ui->newcar->text(),2);
    queue2->EnQueue(car);
     ui->textEdit->append("入口2："+ui->time->text()+" "+car->name+"开始排队");
    }
}
}

void ParkingShow::showTime()  // 显示时间槽函数
{
    QString string;
    QDateTime Timedata = QDateTime::currentDateTime();   //  获取当前时间
    string = Timedata.toString("hh:mm:ss");   //  设置显示格式
    ui->time->setText(string);
}



void ParkingShow::on_outcar_clicked()
{
    if(carinpark==0){
        QMessageBox *box1=new QMessageBox();
        QString string="停车场内没有车!";
        box1->setText(string);
        box1->setWindowTitle("warning!");
        box1->exec();


    }
    else{
        QVector<Park>::iterator it;
        //出库前的准备活动

        //挑选出出那个车子
//        while(true){
//        std::random_device rd;
//        std::mt19937 gen(rd());
//        std::uniform_int_distribution<> dis(1, ui->carnum->text().toInt());
//        int random_number = dis(gen);
//        int i=1;
//        for(it = carPark->begin();i<random_number ; ++it) {

//               i++;

//        }
//        if(it->car!=nullptr)
//            break;

//    }
        int outnum=ui->lineEdit_2->text().toInt();
        int i=1;
        for(it = carPark->begin();i<outnum ; ++it) {
                          i++;
            }
        if(it->car==nullptr){
            QMessageBox *box1=new QMessageBox();
            QString string="没车怎么出（愤怒）!";
            box1->setText(string);
            box1->setWindowTitle("warning!");
            box1->exec();


        }
        else{


        std::random_device rd;
        std::mt19937 gen(rd());
        //
        //
        //
        //
        //
        //这里为了让程序更容易展示，改变在停车场内的停车时间，设为1-3秒
        std::uniform_int_distribution<> dis(1, 3);
        int random_number = dis(gen);
        std::this_thread::sleep_for(std::chrono::seconds(random_number));
        //开始出库
        QGraphicsPixmapItem *map=items[it->car->pixmap];
        ui->textEdit->append("入口"+QString::number(it->car->enter)+":"+it->car->name+"准备出库.车位："+QString::number(it->car->num) );
        int carnum=ui->emptycar->text().toUInt()+1;
        ui->emptycar->setText(QString::number(carnum));


        //计算运动的时间
        int time=(ui->carnum->text().toInt()*100-it->car->x)/20;

        // 创建QTransform对象，并设置旋转角度
            QTransform transform;
            transform.rotate(90); // 旋转45度
        map->setPos(map->x(),map->y()+50);
        map->setPixmap(map->pixmap().transformed(transform));

       // map->setRotation(0);
        //水平移动
        QTimer * timer1;   // 新建一个时间定时器
        timer1 = new QTimer;
        QObject::connect(timer1, &QTimer::timeout, [=](){

                map->setPos(map->x()+20,100+50);

                });
        timer1->start(1000);  // 每隔1000毫秒移动一次
        QTimer::singleShot(1000*(time+1), [timer1,it]() {
                timer1->stop();
                it->car=nullptr;

            });
        timer1->start();

        //计算money
        it->car->outtime=ui->time->text();

        QString timein=it->car->intime;
        QString timeout=it->car->outtime;
        int temp1=timein.mid(3,2).toInt();
        int temp2=timeout.mid(3,2).toInt();

        int time1=timein.right(2).toInt();
        int time2=timeout.right(2).toInt();

        qDebug()<<temp1<<temp2;

        it->car->monye=(time2-time1+(temp2-temp1)*60)/5*1.5;


        carinpark--;
        ui->carout->setText(it->car->name);
        ui->outmessage->setText(QString::number(it->car->num));
        ui->cartime->setText(QString::number(time2-time1+(temp2-temp1)*60));
        ui->moneypay->setText(QString::number(it->car->monye));

        x.push_back(++countcount);
        y.push_back(it->car->monye);
        drawname.push_back(it->car->name);

        ui->textEdit->append("入口"+QString::number(it->car->enter)+":"+it->car->name+" "+"已经停出场，在车位："+QString::number(it->car->num)+"，进入停车场："+
                           it->car->intime+",出停车场的时间为："+it->car->outtime+",收费:"+QString::number(it->car->monye)  );
        ui->textEdit_2->append("入口"+QString::number(it->car->enter)+"，车牌名："+it->car->name+" 在车位："+QString::number(it->car->num)+"，进入停车场："+
                               it->car->intime+",出停车场的时间为："+it->car->outtime+",收费:"+QString::number(it->car->monye) );

}
    }
}


void ParkingShow::on_entercar_clicked()
{

    //开始车位的展示和进入
            if(ui->lineEdit_enter1->text()=='0'){
                QMessageBox *box1=new QMessageBox();
                QString string="没有等待进入停车场的车辆!";
                box1->setText(string);
                box1->setWindowTitle("warning!");
                box1->exec();
            }
            else if(carinpark==ui->carnum->text().toInt()){
                QMessageBox *box1=new QMessageBox();
                QString string="停车场已经停满了!";
                box1->setText(string);
                box1->setWindowTitle("warning!");
                box1->exec();

            }
            else{

                 QGraphicsPixmapItem *map=items[pixmap];

                 scene->addItem(map);
            //初始化小车的位置
                 map->setPos(-100,100);
           //从入口中获取要停的车
                 Car *car=queue1->get();
                 queue1->DeQueue();
                 car->intime=ui->time->text();
                 car->pixmap=pixmap;
                 pixmap++;
                 ui->textEdit->append("入口"+QString::number(car->enter)+":"+car->name+" "+car->intime+" 进入停车场");
                 int carnum=ui->emptycar->text().toUInt()-1;
                 ui->emptycar->setText(QString::number(carnum));

            //确定要停放的位
                QVector<Park>::iterator it;
                for(it = carPark->begin(); it != carPark->end(); ++it) {
                   if(it->car!=nullptr){
                       continue;
                   }
                   else{
                       //存入信息
                       car->num=it->num;
                       it->car=car;
                       car->x=it->x;
                       car->y=it->y;
                       break;
                   }
                }
            ui->carin->setText(car->name);
            ui->inmessage->setText(QString::number(car->num));
            ui->lineEdit_14->setText(QString::number(car->enter));

            //计算运动的时间
            int time=(car->x+100)/10;
            //水平移动
            QTimer * timer;   // 新建一个时间定时器
            timer = new QTimer;
            QObject::connect(timer, &QTimer::timeout, [=](){
                    map->setPos(map->x()+10,map->y());
                    });
            timer->start(500);  // 每隔1000毫秒移动一次
            QTimer::singleShot(500*(time+1), [timer]() {
                    timer->stop();
                });

            //旋转
            QTimer * timer2;   // 新建一个时间定时器
            timer2 = new QTimer;
            connect(timer2, &QTimer::timeout, [=](){
            map->setRotation(-90);
        });
            timer2->start(500*(time+1));  // 每隔1000毫秒旋转一次
//            QTimer::singleShot(500*(time+2), [timer]() {
//                    timer->stop();
//                });
            int num=ui->lineEdit_enter1->text().toInt()-1;
            ui->lineEdit_enter1->setText(QString::number(num));
            carinpark++;
            ui->textEdit->append("入口"+QString::number(car->enter)+":"+car->name+" "+"已经停好车，在车位："+QString::number(car->num)+"位置信息是："+
                                                       QString::number(car->x)+","+QString::number(car->y));
            }

}



void ParkingShow::on_pushButton_clicked()
{

    LineChartWidget *window = new LineChartWidget(x,y);
//    int Count = drawname.size();
//    QVBoxLayout *layout;
//    window->setLayout(layout);
//    QPointF *points = new QPointF[Count];  // 创建存储绘图点的数组
//    for (int i = 0; i < Count; ++i) {
//          // 将坐标点存入数组中
//        QLabel *label = new QLabel("Hello, World!");
//        layout->addWidget(label);
//        label->move(x[i]*40+100, y[i]*40);
//    }
    window->show();



}
void ParkingShow::writeToFile(QString filePath, QString data) {
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << data;
        file.close();
    } else {
        qDebug() << "Unable to open file for writing";
    }
}
void ParkingShow::on_pushButton_2_clicked()
{
    writeToFile("C:/Qt/qt/QPark/message.txt",ui->textEdit_2->toPlainText());
}
