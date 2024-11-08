#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    //参数1  正常显示图片路径  参数2  按下后切换图片路径
    MyPushButton(QString path);

    QPixmap hover;//默认样式
    QPixmap click;//点击样式

    void upzoom();//向下跳跃
    void downzoom();//向上跳跃

    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

signals:
    void clicked();


public slots:
};

#endif // MYPUSHBUTTON_H
