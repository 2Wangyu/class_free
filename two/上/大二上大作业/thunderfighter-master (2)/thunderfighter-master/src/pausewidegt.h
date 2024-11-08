#ifndef PAUSEWIDEGT_H
#define PAUSEWIDEGT_H

#include <QWidget>
#include <QPainter>
#include "MyPushButton.h"
#include "Config.h"

class PauseWidegt : public QWidget
{
    Q_OBJECT
public:
    explicit PauseWidegt(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);

signals:
    void backMainScene();
    void continueGame();

};

#endif // PAUSEWIDEGT_H
