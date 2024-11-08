#ifndef PLANE_H
#define PLANE_H
#include <QPixmap>
#include "Config.h"
#include "Bullet.h"

class Plane{
public:
    Plane();
    void shoot();//发射子弹
    void setPosition(int x, int y);//设置飞机位置

public:
    QPixmap plane;//飞机资源 对象
    int x;//飞机坐标
    int y;
    QRect rect;//飞机的矩形边框
    Bullet bullets[BULLET_NUM];//弹匣
    int recorder;//发射间隔记录
};

#endif // PLANE_H
