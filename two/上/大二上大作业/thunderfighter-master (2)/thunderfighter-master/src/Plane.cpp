#include "Plane.h"
#include "Config.h"

Plane::Plane()
{
    //初始化加载飞机图片资源
    QImage originalImage(PLANE_PATH);
    QImage leftImage = originalImage.copy(0, 0, originalImage.height(), originalImage.height());
    plane = QPixmap::fromImage(leftImage);

    //初始化坐标
    x = GAME_WIDTH * 0.5 - plane.width()*0.5;
    y = GAME_HEIGHT - plane.height() - BLOOD_HEIGHT;

    //初始化矩形框
    rect.setWidth(plane.width());
    rect.setHeight(plane.height());
    rect.moveTo(x,y);

    recorder = 0;
}

void Plane::setPosition(int x, int y)
{
    this->x = x;
    this->y = y;
    rect.moveTo(x,y);
}

void Plane::shoot()
{
    //累加时间间隔记录变量
    recorder++;
    //判断如果记录数字 未达到发射间隔，直接return
    if(recorder < BULLET_INTERVAL)
    {
        return;
    }
    //到达发射时间处理
    //重置发射时间间隔记录
    recorder = 0;

    //发射子弹
    for(int i = 0 ; i < BULLET_NUM;i++)
    {
        //如果是空闲的子弹进行发射
        if(bullets[i].free)
        {
            //将改子弹空闲状态改为假
            bullets[i].free = false;
            //设置发射的子弹坐标
            bullets[i].x = x + rect.width()*0.5 - bullets[i].rect.width()*0.5;//正中央
            bullets[i].y = y - bullets[i].rect.height();
            break;
        }
    }
}
