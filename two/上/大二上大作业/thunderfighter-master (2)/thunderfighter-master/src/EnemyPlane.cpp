#include "EnemyPlane.h"

EnemyPlane::EnemyPlane()
{
    enemy.load(ENEMY_PATH);
    x = 0;
    y = 0;
    free = true;
    speed = ENEMY_SPEED;
    //敌机矩形
    rect.setWidth(enemy.width());
    rect.setHeight(enemy.height());
    rect.moveTo(x,y);
}

void EnemyPlane::updatePosition()
{
    //空闲状态，不计算坐标
    if(free)
    {
        return;
    }

    y += speed;
    rect.moveTo(x,y);

    if(y >= GAME_HEIGHT + rect.height())
    {
        free = true;
    }
}
