#ifndef BOMB_H
#define BOMB_H
#include "Config.h"
#include <QPixmap>
#include <QVector>

class Bomb
{
public:
    Bomb();
    void updateInfo();//更新信息（播放图片下标、播放间隔）

public:
    QVector<QPixmap> pixArr;//放爆炸资源数组
    int x;//爆炸位置
    int y;
    bool free;//爆炸状态
    int recoder;//爆炸切图的时间间隔
    int index;//爆炸时加载的图片下标
};

#endif // BOMB_H
