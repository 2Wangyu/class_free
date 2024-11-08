#include "pausewidegt.h"
#include <QDebug>

PauseWidegt::PauseWidegt(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(GAME_WIDTH,GAME_HEIGHT);

    MyPushButton* backBut = new MyPushButton(":/image/ui/main/button-back.png");
    backBut->setParent(this);
    backBut->move(8,this->height()*0.3 + 318*0.5);
    connect(backBut,&MyPushButton::clicked,[=](){
        emit this->backMainScene();
    });

    MyPushButton* resumeBut = new MyPushButton(":/image/ui/main/button-resume.png");
    resumeBut->setParent(this);
    resumeBut->move(this->width() - resumeBut->width() - 8,this->height()*0.3 + 318*0.5);
    connect(resumeBut,&MyPushButton::clicked,[=](){
        emit this->continueGame();
    });
}

void PauseWidegt::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/image/ui/main/pause.png");
    painter.drawPixmap(0,this->height()*0.3,pix);
    pix.load(":/image/ui/main/pausetxt.png");
    painter.drawPixmap(this->width() - pix.width(),this->height()*0.3,pix);
}
