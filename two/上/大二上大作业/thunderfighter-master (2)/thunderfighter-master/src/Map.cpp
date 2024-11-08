#include "Map.h"

Map::Map()
{
    //初始化加载地图对象
    map1.load(MAP_PATH);
    map2.load(MAP_PATH);

    //设置地图其实y轴坐标
    map1PosY = -GAME_HEIGHT;
    map2PosY = 0;

    //设置地图滚动速度
    scrollSpeed = MAP_SCROLL_SPEED;
}

void Map::mapPosition()
{
    //处理第一张图片滚动
    map1PosY += MAP_SCROLL_SPEED;
    if(map1PosY >= 0)
    {
        map1PosY =-GAME_HEIGHT;
    }

    //处理第二张图片滚动
    map2PosY += MAP_SCROLL_SPEED;
    if(map2PosY >= GAME_HEIGHT )
    {
        map2PosY =0;
    }
}
