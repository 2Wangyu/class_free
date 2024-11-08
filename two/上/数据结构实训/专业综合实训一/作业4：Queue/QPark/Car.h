#ifndef CAR_H
#define CAR_H
#include<QString>
class Car{
public:
    Car(QString name,int enter){
        this->name=name;
        this->enter=enter;
        //this->intime=intime;

    };
    Car(){};
    ~Car(){};

    //车牌号
QString name;
//入口
int enter;
//当前车的坐标位置
int x;
int y;
//进出的时间
QString intime;
QString outtime;

//车位编号
int num;

//收费
double monye;
//表示图片信息
int pixmap;



};



#endif // CAR_H
