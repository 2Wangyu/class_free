#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QWidget>
#include "pausewidegt.h"
#include "Map.h"
#include "Plane.h"
#include "EnemyPlane.h"
#include "Bomb.h"
#include "Config.h"
#include <QTimer>
#include <QPainter>
#include <QMouseEvent>
#include <QMediaPlayer>
#include <QMediaContent>
#include <QLabel>
class GameScene : public QWidget
{
    Q_OBJECT
public:
    explicit GameScene(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void playGame();
    void readyGame();
    void updatePosition();//更新坐标
    void movePlane();
    void enemyToScene(); //敌机出场
    void collisionDetection();//碰撞检测

signals:
    void backMainScene();

protected:
    void mousePressEvent(QMouseEvent  *event)  override;//生成暂停窗口
    void mouseReleaseEvent(QMouseEvent  *event)  override;
    void mouseMoveEvent(QMouseEvent *event) override;//鼠标移动
    void keyPressEvent(QKeyEvent* event) override;//键盘移动
    void keyReleaseEvent(QKeyEvent *event) override;//键盘移动

private:
    PauseWidegt *pauseWidget;
    QRect  pauseRect;//暂停键
    bool isPause;//是否暂停
    bool isReady;//是否准备就绪
    QLabel *readyLabel;
    Map map;
    QTimer mapTimer;
    QTimer readyTimer;
    Plane plane;
    bool upKeyPressed;
    bool downKeyPressed;
    bool leftKeyPressed;
    bool rightKeyPressed;

    EnemyPlane enemys[ENEMY_NUM];//敌机数组
    int recorder;//敌机出场间隔记录

    Bomb bombs[BOMB_NUM];//爆炸数组
    QMediaPlayer *mediaPlayer;
};

#endif // GAMESCENE_H
