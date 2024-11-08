#include "Bullet.h"

Bullet::Bullet()
{
    //初始化加载子弹资源
    QImage originalImage(BULLET_PATH);
    QImage leftImage = originalImage.copy(10, 0, 24, originalImage.height()*2/3);
    bullet = QPixmap::fromImage(leftImage);

    //子弹坐标 初始坐标可随意设置，后期会重置
    x = GAME_WIDTH*0.5 - bullet.width()*0.5;
    y = GAME_HEIGHT;

    //子弹状态
    free = true;

    //子弹速度
    speed = BULLET_SPEED;

    //子弹矩形框
    rect.setWidth(bullet.width());
    rect.setHeight(bullet.height());
    rect.moveTo(x,y);
}
void Bullet::updatePosition()
{
    //如果子弹是空闲状态，不需要坐标计算
    //玩家飞机可以控制子弹的空闲状态为false
    if(free)
    {
        return;
    }
    //子弹向上移动
    y  -= speed;
    rect.moveTo(x,y);
    if(y <= -rect.height())
    {
        free = true;
    }
}
