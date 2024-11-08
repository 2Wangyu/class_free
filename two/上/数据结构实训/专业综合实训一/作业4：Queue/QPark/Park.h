#ifndef PARK_H
#define PARK_H
#include"Car.h"
class Park{
public:
    Park()=default;
    Park(int x1,int y1,int num1,Car *car):x(x1),y(y1),num(num1),car(nullptr){};
    ~Park(){};



    //表示车位的坐标信息
    int x;
    int y;

    //占据车辆信息
    Car *car;
    //车位编号
    int num;



};


#endif // PARK_H
