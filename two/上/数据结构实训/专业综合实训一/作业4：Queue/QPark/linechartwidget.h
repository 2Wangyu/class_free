#ifndef LINECHARTWIDGET_H
#define LINECHARTWIDGET_H


#include<QWidget>
#include<QPainter>
#include<QPaintEvent>


class LineChartWidget : public QWidget {
    Q_OBJECT
public:
public:
    LineChartWidget(const QVector<double> &xValues, const QVector<double> &yValues, QWidget *parent = nullptr);
protected:
    void paintEvent(QPaintEvent *event);

protected:

    QVector<double> m_xValues;
    QVector<double> m_yValues;



};
#endif // LINECHARTWIDGET_H
