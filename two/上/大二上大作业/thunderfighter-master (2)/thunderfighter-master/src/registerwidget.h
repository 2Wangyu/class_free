#ifndef REGISTERWIDGET_H
#define REGISTERWIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include "MyPushButton.h"

namespace Ui {
class RegisterWidget;
}

class RegisterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void getfromMainwindow(QString str);
    ~RegisterWidget();

private slots:
    void registerclicked();
    void backclicked();
    void getCodeclicked();

signals:
    void sendMessage(QString);

private:
    Ui::RegisterWidget *ui;
    MyPushButton *backBut;
    MyPushButton *registerBut;
    MyPushButton *getCodeBut;
    QString code;
};

#endif // REGISTERWIDGET_H
