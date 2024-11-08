#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include "registerwidget.h"
#include "MyPushButton.h"
#include "widget.h"
#include "user.h"

namespace Ui {
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    ~LoginWidget();

private slots:
    void loginclicked();
    void registerclicked();
    void playclicked();
    void receiveMessage(QString);
    void onReadMessage();   //处理服务端反馈的数据
    void onDisplayError(QAbstractSocket::SocketError e);    //打印错误信息
    void reconnect();

private:
    Ui::LoginWidget *ui;
    QTcpSocket* m_tcpSocket;
    RegisterWidget *registerwidget;
    MyPushButton *loginBut;
    MyPushButton *registerBut;
    MyPushButton *unconnectplayBut;
    User player;
    Widget *widget;
};

#endif // LOGINWIDGET_H
