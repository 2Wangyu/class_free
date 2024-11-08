#include "MyPushButton.h"
#include <QDebug>
#include <QPropertyAnimation>

//参数1  正常显示图片路径  参数2  按下后切换图片路径
MyPushButton::MyPushButton(QString path)
{
    QImage originalImage(path);
    if (originalImage.isNull()) {
        qDebug() << "Failed to load image";
    }
    QImage upperImage = originalImage.copy(0, 0, originalImage.width(), originalImage.height()/2);
    hover = QPixmap::fromImage(upperImage);
    QImage lowerImage = originalImage.copy(0, originalImage.height()/2, originalImage.width(), originalImage.height()/2);
    click = QPixmap::fromImage(lowerImage);
    //设置按钮固定尺寸
    this->setFixedSize(hover.width(),hover.height());
    //设置不规则样式
    this->setStyleSheet("QPushButton{border:0px;}");  //有点类似于网页设计中的CSS语法
    //设置图标
    this->setIcon(hover);
    //设置图标大小
    this->setIconSize(QSize(hover.width(),hover.height()));
}

void MyPushButton::upzoom()
{
    //创建动画对象
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");  //参数1：让谁去做这个动画，参数2：动画的方式
    //设置动画间隔
    animation->setDuration(1000);
    //设置起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //设置结束位置（接口和起始位置不一样）
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));  //因为是向下跳跃，所以只有y坐标会增加
    //设置动画曲线（加速、减速、变速）
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start(QAbstractAnimation::DeleteWhenStopped);  //DeleteWhenStopped表示动画执行完毕后就释放对象，KeepWhenStopped则表示保存对象
}

void MyPushButton::downzoom()
{
    //创建动画对象
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");  //参数1：让谁去做这个动画，参数2：动画的方式
    //设置动画间隔
    animation->setDuration(1000);
    //设置起始位置
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height())); //这里和向下跳跃不同的是，他的起始位置是变化之后的位置
    //设置结束位置（接口和起始位置不一样）
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //设置动画曲线（加速、减速、变速）
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start(QAbstractAnimation::DeleteWhenStopped);  //DeleteWhenStopped表示动画执行完毕后就释放对象，KeepWhenStopped则表示保存对象
    //this->setIcon(hover);
}

void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    this->setIcon(click);
    emit clicked();
}

void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    this->setIcon(hover);
}
