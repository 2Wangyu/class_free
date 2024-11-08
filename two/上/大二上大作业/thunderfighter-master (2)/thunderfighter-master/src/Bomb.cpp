#include "Bomb.h"

Bomb::Bomb()
{
    //初始化爆炸图片数组
    QImage originalImage(BOMB_PATH);
    for(int i = 0;i < BOMB_MAX ;i++){
        QImage leftImage = originalImage.copy(originalImage.height()*i,0,originalImage.height(), originalImage.height());
        QPixmap pixmap = QPixmap::fromImage(leftImage);
        QSize  newSize(pixmap.width()*0.3, pixmap.height()*0.3);  //  设置新的宽度和高度
        pixmap = pixmap.scaled(newSize,  Qt::KeepAspectRatio,  Qt::SmoothTransformation);
        pixArr.push_back(pixmap);
    }
    x = 0;//初始化坐标
    y = 0;
    free = true;//初始化空闲状态
    index = 0;//当前播放图片下标
    recoder = 0;//爆炸间隔记录
}

void Bomb::updateInfo()
{
    //空闲状态
    if(free)
    {
        return;
    }
    recoder++;
    if(recoder < BOMB_INTERVAL)
    {
        //记录爆炸间隔未到，直接return，不需要切图
        return;
    }
    //重置记录
    recoder = 0;
    //切换爆炸播放图片
    index++;
    //注：数组中的下标从0开始，最大是6
    //如果计算的下标大于6，重置为0
    if(index > BOMB_MAX-1)
    {
        index = 0;
        free = true;
    }
}
