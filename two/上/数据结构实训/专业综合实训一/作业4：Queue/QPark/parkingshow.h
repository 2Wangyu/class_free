#ifndef PARKINGSHOW_H
#define PARKINGSHOW_H
#include<QGraphicsScene>
#include <QMainWindow>
#include"Park.h"
#include<QVector>
#include"myqueue.h"
#include<QMutex>
#include<QThread>
#include<QGraphicsPixmapItem>
#include<QPixmap>

QT_BEGIN_NAMESPACE
namespace Ui { class ParkingShow; }
QT_END_NAMESPACE

class ParkingShow : public QMainWindow
{
    Q_OBJECT

public:
    //展示折线图的界面
    QWidget widget;
    void writeToFile(QString filePath, QString data);


    ParkingShow(QWidget *parent = nullptr);
    ~ParkingShow();
    //绘图所用
    QGraphicsScene *scene  =new QGraphicsScene(this);;
    //初始化停车位界面

    void initGraphic(int num);
    //存储停车场的容器
    //初始化停车场容器
    QVector<Park> *carPark ;
    //显示当前时间
    void showTime();
    //两个入口的排队队列:入口1和入口2
    myQueue *queue1=new myQueue;
    myQueue *queue2=new myQueue;

  //表示在停车场内的车
    int carinpark=0;
    //表示图片信息
    int pixmap=0;

    //定义互斥锁
    QMutex *mutex;
    //图片

    QList<QGraphicsPixmapItem *> items;


    //存储车的名字,收费，用于绘制折线图
    int countcount=0;
    QVector<double> x;
    //收费
    QVector<double> y;
    QVector<QString> drawname;



private slots:
    void on_start_clicked();

    void on_enter1_clicked();

    void on_enter2_clicked();

    void on_outcar_clicked();

    void on_entercar_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::ParkingShow *ui;

};
#endif // PARKINGSHOW_H
