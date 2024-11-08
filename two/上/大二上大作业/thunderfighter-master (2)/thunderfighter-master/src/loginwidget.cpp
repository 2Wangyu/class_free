#include "loginwidget.h"
#include "ui_loginwidget.h"
#include "user.h"
#include <QMessageBox>
#include <QPainter>
#include "widget.h"

LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
    this->setWindowTitle(GAME_TITLE);
    this->setWindowIcon(QIcon(GAME_ICON));

    loginBut = new MyPushButton(":/image/ui/main/login002.png");
    loginBut->setParent(this);
    loginBut->move(this->width()*0.85 - loginBut->width()*0.85,this->height()*0.7);
    connect(loginBut,&MyPushButton::clicked,this,&LoginWidget::loginclicked);
    registerBut = new MyPushButton(":/image/ui/main/login004.png");
    registerBut->setParent(this);
    registerBut->move(this->width()*0.15 - registerBut->width()*0.15 ,this->height()*0.7);
    connect(registerBut,&MyPushButton::clicked,this,&LoginWidget::registerclicked);
    unconnectplayBut = new MyPushButton(":/image/ui/main/button-deactivate.png");
    unconnectplayBut->setParent(this);
    unconnectplayBut->move(this->width()/2 - unconnectplayBut->width()/2,this->height()*0.8);
    connect(unconnectplayBut,&MyPushButton::clicked,this,&LoginWidget::playclicked);

    m_tcpSocket = new QTcpSocket(this);
    m_tcpSocket->abort();
    //连接服务端
    m_tcpSocket->connectToHost("127.0.0.1", 6666);
            connect(m_tcpSocket,&QTcpSocket::readyRead,
                    this,&LoginWidget::onReadMessage);
            connect(m_tcpSocket,SIGNAL(QAbstractSocket::SocketError),
                    this,SLOT(onDisplayError(QAbstractSocket::SocketError)));
}

void LoginWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/image/ui/main/cover2.jpg");
    painter.drawPixmap(0,0,pix);
    pix.load(":/image/ui/main/login000.png");
    painter.drawPixmap(this->width()/2-pix.width()/2,this->height()/3 - pix.height()/3,pix);
}

LoginWidget::~LoginWidget()
{
    delete ui;
}

void LoginWidget::reconnect(){
    qDebug() << "Disconnected from server, try to reconnect...";
    m_tcpSocket->abort();
    //连接服务端
    m_tcpSocket->connectToHost("127.0.0.1",6666);
}

void LoginWidget::loginclicked()
{
    if(!ui->lineEdit->text().isEmpty()){
        if(!ui->lineEdit_2->text().isEmpty()){
            QString str = "-L ";
            m_tcpSocket->write(str.toUtf8());
            m_tcpSocket->flush();
            m_tcpSocket->write(QString(ui->lineEdit->text()+" ").toUtf8());
            m_tcpSocket->flush();
            m_tcpSocket->write(ui->lineEdit_2->text().toUtf8());
            m_tcpSocket->flush();
        }
        else{
            qDebug() << "请先输入密码，谢谢！";
            QMessageBox::information(NULL, tr("请输入密码"),tr("请先输入密码，谢谢！"),QMessageBox::Ok);
        }
    }
    else{
        qDebug() << "请先输入密码，谢谢！";
        QMessageBox::information(NULL, tr("请输入账号"),tr("请先输入账号，谢谢！"),QMessageBox::Ok);
    }
}

void LoginWidget::registerclicked()
{
    registerwidget = new RegisterWidget();
    connect(registerwidget,SIGNAL(sendMessage(QString)),this,SLOT(receiveMessage(QString)));
    registerwidget->show();
}

void LoginWidget::playclicked()
{
    widget = new Widget();
    widget->move(this->pos());//处理窗口移动问题
    widget->show();
    this->hide();
}

void LoginWidget::onReadMessage()
{
    QByteArray bt;
    bt.resize(m_tcpSocket->bytesAvailable());
    m_tcpSocket->read(bt.data(),bt.size());
    QString string = QString(bt);
    QStringList list = string.split(" ");
    //将客户端反馈的数据显示到标签上
    if(list[0]=="-L"){
        if(list[1] == "t"){
            player.setUserAccount(list[2]);
            player.setUserPassword(list[3]);
            widget = new Widget();
            widget->move(this->pos());//处理窗口移动问题
            widget->show();
            widget->setIsSingle(false);
            connect(widget,&Widget::updateScore,[=]{
                qDebug() << m_tcpSocket->state();
                int score = widget->getScore();
                QString str = "-S ";
                m_tcpSocket->write(str.toUtf8());
                m_tcpSocket->flush();
                m_tcpSocket->write(QString(player.getUserAccount() +  " ").toUtf8());
                m_tcpSocket->flush();
                m_tcpSocket->write(QString(player.getUserPassword() +  " ").toUtf8());
                m_tcpSocket->flush();
                str = QString::number(score);
                m_tcpSocket->write(str.toUtf8());
                m_tcpSocket->flush();
            });
            connect(widget,&Widget::lookRanking,[=]{
                QString str = "-K ";
                m_tcpSocket->write(str.toUtf8());
                m_tcpSocket->flush();
            });
            this->hide();
            //QMessageBox::information(this, tr("登陆成功"),tr("登陆成功"),QMessageBox::Ok);
        }else{
            QMessageBox::information(this, tr("账号或密码信息有误"),tr("请输入正确的密码或账号信息"),QMessageBox::Ok);
        }
    }else if(list[0]=="-R"){
        registerwidget->getfromMainwindow(list[1]);
    }else if(list[0]=="-K"){
        widget->setList(list);
        widget->showRanking();
    }
}

void LoginWidget::onDisplayError(QAbstractSocket::SocketError e)
{
    qDebug()<<"SocketError:"<<e<<endl
           <<m_tcpSocket->errorString();
}

void LoginWidget::receiveMessage(QString user){
    m_tcpSocket->write(user.toUtf8());
    m_tcpSocket->flush();
}
