#ifndef BULLET_H
#define BULLET_H

#include "Config.h"
#include <QPixmap>

class Bullet
{
public:
    Bullet();
    void updatePosition();//更新子弹坐标

public:
    QPixmap bullet;//子弹资源对象
    int x;//子弹坐标
    int y;
    QRect rect;//子弹的矩形边框（用于碰撞检测）
    int speed;
    bool free;//子弹是否闲置
};

#endif // BULLET_H
