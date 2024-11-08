#ifndef CONFIG_H
#define CONFIG_H

/**********  游戏配置数据 **********/
#define GAME_WIDTH  640  //宽度
#define GAME_HEIGHT 990  //高度
#define GAME_TITLE "Thunderfighter" //标题
#define GAME_ICON ":/image/Icon.png"
#define MAP_PATH ":/image/map/map1.jpg"
#define MAP_SCROLL_SPEED 2
#define GAME_RATE  10
#define BLOOD_HEIGHT 44
#define PLANE_PATH ":/image/plane/p-01a.png"
#define BULLET_PATH ":/image/bullet/zhujizidan.png"
#define BULLET_SPEED 10
#define BULLET_NUM 30   //弹匣中子弹总数
#define BULLET_INTERVAL 30 //发射子弹时间间隔
#define ENEMY_PATH  ":/image/plane/c-05.png"  //敌机资源图片
#define ENEMY_SPEED 5  //敌机移动速度
#define ENEMY_NUM   20  //敌机总数量
#define ENEMY_INTERVAL  30  //敌机出场时间间隔
#define BOMB_PATH  ":/image/effect/boom.png"   //爆炸资源图片
#define BOMB_NUM  20     //爆炸数量
#define BOMB_MAX  8      //爆炸图片最大索引
#define BOMB_INTERVAL 5   //爆炸切图时间间隔
#define SOUND_BACKGROUND ":/sounds/aLiEz1.mp3"
#define SOUND_BOMB ":/sounds/blast.wav"
#define READY_PATH ":/image/ui/main/readygo.png"

#endif // CONFIG_H
