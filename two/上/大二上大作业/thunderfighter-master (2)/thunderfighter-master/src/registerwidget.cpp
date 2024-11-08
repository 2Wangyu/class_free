#include "registerwidget.h"
#include "ui_registerwidget.h"
#include "user.h"
#include "qmessagebox.h"
#include <QPainter>
#include "Config.h"
#include <QTime>
#include "smtp.h"
#include "codewidget.h"

RegisterWidget::RegisterWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegisterWidget)
{
    ui->setupUi(this);
    this->setWindowTitle(GAME_TITLE);
    this->setWindowIcon(QIcon(GAME_ICON));

    backBut = new MyPushButton(":/image/ui/main/login005.png");
    backBut->setParent(this);
    backBut->move(this->width()*0.15 - backBut->width()*0.15,this->height()*0.8);
    connect(backBut,&MyPushButton::clicked,this,&RegisterWidget::backclicked);
    registerBut = new MyPushButton(":/image/ui/main/login003.png");
    registerBut->setParent(this);
    registerBut->move(this->width()*0.85 - registerBut->width()*0.85 ,this->height()*0.8);
    connect(registerBut,&MyPushButton::clicked,this,&RegisterWidget::getCodeclicked);
    /*
    getCodeBut = new MyPushButton(":/image/ui/main/login006.png");
    getCodeBut->setParent(this);
    getCodeBut->move(this->width()*0.5 - getCodeBut->width()*0.5 ,this->height()*0.9);
    connect(getCodeBut,&MyPushButton::clicked,this,&RegisterWidget::getCodeclicked);*/
}

void RegisterWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/image/ui/main/cover2.jpg");
    painter.drawPixmap(0,0,pix);
    pix.load(":/image/ui/main/login001.png");
    painter.drawPixmap(this->width()/2-pix.width()/2,this->height()/3 - pix.height()/3,pix);
    qDebug() << this->width()/2-pix.width()/2 << this->height()/3 - pix.height()/3;
}

RegisterWidget::~RegisterWidget()
{
    delete ui;
}

void RegisterWidget::backclicked()
{
    setVisible(false);
}

void RegisterWidget::registerclicked()
{
    QString str="-R ";
    sendMessage(str+ui->lineEdit1->text()+" "+ui->lineEdit2->text()+" "+ui->lineEdit3->text());
}

void RegisterWidget::getCodeclicked()
{
    if(!ui->lineEdit1->text().isEmpty()){
        if(!ui->lineEdit2->text().isEmpty()){
            if(!ui->lineEdit3->text().compare(ui->lineEdit4->text())){
                QMessageBox::information(NULL, tr("输入验证码"),tr("请输入邮箱接收验证码，谢谢！"),
                                         QMessageBox::Ok);
                CodeWidget *codewidget = new CodeWidget();
                codewidget->show();
                connect(codewidget,&CodeWidget::identifySuc,[&](){
                    this->registerclicked();
                });
            }
            else {
                QMessageBox::information(NULL, tr("密码不一致请确认"),tr("请输入相同密码，谢谢！"),
                                         QMessageBox::Ok);
            }
        }
        else {
            QMessageBox::information(NULL, tr("请输昵称"),tr("请先输入昵称再注册，谢谢！"),
                                     QMessageBox::Ok);
        }
    }
    else {
        QMessageBox::information(NULL, tr("请输入用户名"),tr("请先输入用户名再注册，谢谢！"),
                                 QMessageBox::Ok);
    }
}

void RegisterWidget::getfromMainwindow(QString str){
    if(str=="t"){
        QMessageBox::information(this, tr("确认用户名和账号"),tr("请更改用户名或者账号，谢谢！"),
                                 QMessageBox::Ok);
    }
    else if(str=="f"){
        setVisible(false);
    }
}
