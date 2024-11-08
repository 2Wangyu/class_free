#include "widget.h"
#include "ui_widget.h"
#include <QIcon>
#include <QPainter>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setFixedSize(GAME_WIDTH,GAME_HEIGHT);
    this->setWindowTitle(GAME_TITLE);
    this->setWindowIcon(QIcon(GAME_ICON));

    MyPushButton* startBut = new MyPushButton(":/image/ui/main/button-enter.png");
    startBut->setParent(this);
    startBut->move(this->width()*0.5 - startBut->width()*0.5 ,this->height()*0.6);
    connect(startBut,&MyPushButton::clicked,[=](){
        //startBut->upzoom(); //不太好看
        //startBut->downzoom();
        QTimer::singleShot(300,this,[=]{
            this->gameScene = new GameScene();
            this->gameScene->move(this->pos());//处理窗口移动问题
            connect(gameScene,&GameScene::backMainScene,[=](){
                QTimer::singleShot(300,this,[=]{
                    this->show();
                    this->gameScene->hide();
                });
            });
            this->gameScene->show();
            this->hide();
        });
    });

    MyPushButton* quitBut = new MyPushButton(":/image/ui/main/button-quit.png");
    quitBut->setParent(this);
    quitBut->move(this->width()*0.5 - quitBut->width()*0.5 ,this->height()*0.7);
    connect(quitBut,&MyPushButton::clicked,[=](){
        //quitBut->upzoom();
        //quitBut->downzoom();
        this->close();
    });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/image/ui/main/cover.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    pix.load(":/image/ui/main/cover-logo.png");
    //pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(this->width()*0.5 - pix.width()*0.5,40,pix);

}
