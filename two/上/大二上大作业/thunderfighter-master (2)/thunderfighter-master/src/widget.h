#ifndef WIDGET_H
#define WIDGET_H
#include "MyPushButton.h"
#include "gamescene.h"
#include "Config.h"
#include <QWidget>
#include <QDebug>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void paintEvent(QPaintEvent *event);

protected:


private:
    Ui::Widget *ui;
    GameScene *gameScene;
};
#endif // WIDGET_H
