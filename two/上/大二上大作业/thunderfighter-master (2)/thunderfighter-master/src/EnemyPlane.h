#ifndef ENEMYPLANE_H
#define ENEMYPLANE_H
#include <QPixmap>
#include "Config.h"

class EnemyPlane
{
public:
    EnemyPlane();
    void updatePosition(); //更新坐标

public:
    QPixmap enemy;//敌机资源对象
    int x;//敌机坐标
    int y;
    QRect rect;//敌机的矩形边框（用于碰撞检测）
    int speed;
    bool free;//敌机是否闲置
};

#endif // ENEMYPLANE_H
