#ifndef MAP_H
#define MAP_H
#include <QPixmap>
#include "Config.h"

class Map
{
public:
    Map();
    void mapPosition(); //地图滚动坐标计算

public:

    //地图图片对象
    QPixmap map1;
    QPixmap map2;

    //地图Y轴坐标
    int map1PosY;
    int map2PosY;

    //地图滚动幅度
    int scrollSpeed;
};

#endif // MAP_H
