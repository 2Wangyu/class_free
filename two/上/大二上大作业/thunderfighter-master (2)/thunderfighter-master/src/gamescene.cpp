#include "gamescene.h"
#include <QIcon>
#include <QPushButton>
#include <QDebug>

#include <QFile>

GameScene::GameScene(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(GAME_WIDTH,GAME_HEIGHT);
    this->setWindowTitle(GAME_TITLE);
    this->setWindowIcon(QIcon(GAME_ICON));
    pauseRect = QRect(30, 946, 60, 40);//暂停键的区域
    mapTimer.setInterval(GAME_RATE);
    isPause = false;
    isReady = false;
    readyLabel = new QLabel(this);
    srand((unsigned int)time(NULL));//随机数种子
    readyGame();
}

void GameScene::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,map.map1PosY , map.map1);
    painter.drawPixmap(0,map.map2PosY , map.map2);
    painter.drawPixmap(plane.x,plane.y, plane.plane);
    //绘制敌机
    for(int i = 0 ; i< ENEMY_NUM;i++){
        if(enemys[i].free == false){
            painter.drawPixmap(enemys[i].x,enemys[i].y,enemys[i].enemy);
        }
    }
    //绘制子弹
    for(int i = 0 ;i < BULLET_NUM;i++){//如果子弹状态为非空闲，计算发射位置
        if(!plane.bullets[i].free){
            painter.drawPixmap(plane.bullets[i].x,plane.bullets[i].y,plane.bullets[i].bullet);
        }
    }
    //绘制爆炸图片
    for(int i = 0 ; i < BOMB_NUM;i++){
        if(bombs[i].free == false){
            painter.drawPixmap(bombs[i].x,bombs[i].y,bombs[i].pixArr[bombs[i].index]);
        }
    }
    QPixmap pix;
    pix.load(":/image/ui/blood/fight.png");//加载底部
    painter.drawPixmap(0,this->height() - pix.height(),pix);
    if(!isReady){
        int count = 3;
        QTimer *timer = new QTimer();
        connect(timer, &QTimer::timeout, [&](){
            count--;
            if(count > 1) {
                QImage originalImage(READY_PATH);
                QImage image = originalImage.copy(0, 100, originalImage.width(), 80);
                pix = QPixmap::fromImage(image);
                readyLabel->setPixmap(pix);
                readyLabel->setGeometry(this->width()/2 - pix.width()/2,this->height()/2 - pix.height()/2,  pix.width(), pix.height());
            }else if(count > 0){
                QImage originalImage(READY_PATH);
                QImage image = originalImage.copy(0, 0, originalImage.width(), 100);
                pix = QPixmap::fromImage(image);
                readyLabel->setPixmap(pix);
                readyLabel->setGeometry(this->width()/2 - pix.width()/2,this->height()/2 - pix.height()/2,  pix.width(), pix.height());
            }else{
                timer->stop(); // 到达倒计时结束时停止计时器
                isReady = true;
            }
        });
        timer->start(1000); // 启动计时器，时间间隔为1秒
    }
}

void GameScene::playGame()
{
    //启动定时器
    mapTimer.start();
    connect(&mapTimer,&QTimer::timeout,[=](){
        //更新游戏中元素的坐标
        if(!isPause){
            enemyToScene();
            updatePosition();
            update();//重新绘制
            collisionDetection();
        }
    });
}

void GameScene::readyGame()
{
    mediaPlayer = new QMediaPlayer(this);
    mediaPlayer->setMedia(QUrl::fromLocalFile("D:/QT/item/Thunderfighter/sounds/aLIEz.mp3"));
 /*   connect(mediaPlayer,  &QMediaPlayer::stateChanged,  this,  [this](QMediaPlayer::State  state)  {
         if  (state  ==  QMediaPlayer::PlayingState)  {
             qDebug()  <<  "播放状态：播放中";
         }  else  if  (state  ==  QMediaPlayer::PausedState)  {
             qDebug()  <<  "播放状态：暂停";
         }  else  if  (state  ==  QMediaPlayer::StoppedState)  {
             qDebug()  <<  "播放状态：停止";
         }
    });*/
    mediaPlayer->play();
    readyTimer.start();


}

void GameScene::updatePosition()
{
    map.mapPosition();//更新地图坐标
    movePlane();//更新飞机坐标
    //敌机坐标计算
    for(int i = 0 ; i< ENEMY_NUM;i++){
        //非空闲敌机 更新坐标
       if(enemys[i].free == false){
              enemys[i].updatePosition();
       }
    }
    plane.shoot();//发射子弹
    //计算子弹坐标
    for(int i = 0 ;i < BULLET_NUM;i++)
    {
        //如果子弹状态为非空闲，计算发射位置
        if(!plane.bullets[i].free){
            plane.bullets[i].updatePosition();
        }
    }
    //计算爆炸播放的图片
    for(int i = 0 ; i < BOMB_NUM;i++)
    {
        if(bombs[i].free == false){
               bombs[i].updateInfo();
        }
    }
}

void GameScene::enemyToScene()
{
    recorder++;
    if(recorder < ENEMY_INTERVAL)
    {
        return;
    }

    recorder = 0;

    for(int i = 0 ; i< ENEMY_NUM;i++)
    {
        if(enemys[i].free)
        {
            //敌机空闲状态改为false
            enemys[i].free = false;
            //设置坐标
            enemys[i].x = rand() % (GAME_WIDTH - enemys[i].rect.width());
            enemys[i].y = -enemys[i].rect.height();
            break;
        }
    }
}

void GameScene::collisionDetection()
{
    //遍历所有非空闲的敌机
    for(int i = 0 ;i < ENEMY_NUM;i++){
        if(enemys[i].free){
            //空闲飞机 跳转下一次循环
            continue;
        }
        //遍历所有 非空闲的子弹
        for(int j = 0 ; j < BULLET_NUM;j++){
            if(plane.bullets[j].free){
                //空闲子弹 跳转下一次循环
                continue;
            }
            //如果子弹矩形框和敌机矩形框相交，发生碰撞，同时变为空闲状态即可
            if(enemys[i].rect.intersects(plane.bullets[j].rect))
            {
                enemys[i].free = true;
                plane.bullets[j].free = true;
                //播放爆炸效果
                for(int k = 0 ; k < BOMB_NUM;k++){
                    if(bombs[k].free){//爆炸状态设置为非空闲
                         bombs[k].free = false;
                         bombs[k].x = enemys[i].x;
                         bombs[k].y = enemys[i].y;
                         break;
                    }
                 }
            }
        }
    }
}

void GameScene::mousePressEvent(QMouseEvent *event)
{
    if  (pauseRect.contains(event->pos()))  {//目前有bug，鼠标可以一直点击
        isPause = true;
        mediaPlayer->pause();
        this->pauseWidget = new PauseWidegt(this);
        connect(pauseWidget,&PauseWidegt::backMainScene,[=](){
            emit this->backMainScene();
        });
        connect(pauseWidget,&PauseWidegt::continueGame,[=](){
            isPause = false;
            mediaPlayer->play();
            this->pauseWidget->hide();
        });
        this->pauseWidget->show();
    }
}

void GameScene::mouseReleaseEvent(QMouseEvent *event)
{
    if  (pauseRect.contains(event->pos()))  {
        qDebug()  <<  "Mouse released  in  the  rectangle";
    }
}

void GameScene::mouseMoveEvent(QMouseEvent *event)
{
    //防止闪现
    if(event->x() > plane.x && event->x() < plane.x + plane.rect.width()
            && event->y() > plane.y && event->y() < plane.y + plane.rect.height()){
        int x = event->x() - plane.rect.width()*0.5; //鼠标位置 - 飞机矩形的一半
        int y = event->y() - plane.rect.height()*0.5;

        //边界检测
        if(x <= 0 ){
            x = 0;
        }
        if(x >= GAME_WIDTH - plane.rect.width()){
            x = GAME_WIDTH - plane.rect.width();
        }
        if(y <= 0){
            y = 0;
        }
        if(y >= GAME_HEIGHT - plane.rect.height() - BLOOD_HEIGHT){
            y = GAME_HEIGHT - plane.rect.height() - BLOOD_HEIGHT;
        }
        plane.setPosition(x,y);
    }
}

void GameScene::movePlane()
{
    int x = plane.x;
    int y = plane.y;
    int step = 5; // 设置每次移动的步长

    // 按下上箭头键或者W键
    if (upKeyPressed)
    {
        y = y - step;
    }
    // 按下下箭头键或者S键
    if (downKeyPressed)
    {
        y = y + step;
    }
    // 按下左箭头键或者A键
    if (leftKeyPressed)
    {
        x = x - step;
    }
    // 按下右箭头键或者D键
    if (rightKeyPressed)
    {
        x = x + step;
    }
    //边界检测
    if(x <= 0 ){
        x = 0;
    }
    if(x >= GAME_WIDTH - plane.rect.width()){
        x = GAME_WIDTH - plane.rect.width();
    }
    if(y <= 0){
        y = 0;
    }
    if(y >= GAME_HEIGHT - plane.rect.height() - BLOOD_HEIGHT){
        y = GAME_HEIGHT - plane.rect.height() - BLOOD_HEIGHT;
    }
    plane.setPosition(x,y);
}

void GameScene::keyPressEvent(QKeyEvent *event)
{
    // 设置按键状态为已按下
    if (event->key() == Qt::Key_Up || event->key() == Qt::Key_W)
    {
        upKeyPressed = true;
    }
    if (event->key() == Qt::Key_Down || event->key() == Qt::Key_S)
    {
        downKeyPressed = true;
    }
    if (event->key() == Qt::Key_Left || event->key() == Qt::Key_A)
    {
        leftKeyPressed = true;
    }
    if (event->key() == Qt::Key_Right || event->key() == Qt::Key_D)
    {
        rightKeyPressed = true;
    }
}

void GameScene::keyReleaseEvent(QKeyEvent *event)
{
    // 设置按键状态为松开
    if (event->key() == Qt::Key_Up || event->key() == Qt::Key_W)
    {
        upKeyPressed = false;
    }
    if (event->key() == Qt::Key_Down || event->key() == Qt::Key_S)
    {
        downKeyPressed = false;
    }
    if (event->key() == Qt::Key_Left || event->key() == Qt::Key_A)
    {
        leftKeyPressed = false;
    }
    if (event->key() == Qt::Key_Right || event->key() == Qt::Key_D)
    {
        rightKeyPressed = false;
    }
}
