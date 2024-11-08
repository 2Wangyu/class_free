#include "linechartwidget.h"

LineChartWidget::LineChartWidget(const QVector<double> &xValues, const QVector<double> &yValues, QWidget *parent) : QWidget(parent) {
    // 将绘图的参数保存起来，以便后续绘制折线图使用
    m_xValues = xValues;
    m_yValues = yValues;
    this->resize(1000,1000);

}


void LineChartWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    // 在窗口上绘制折线图，使用保存的 xValues 和 yValues 进行绘图操作...
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::blue, 2));  // 设置画笔颜色和宽度

        int xCount = m_xValues.size();
        int yCount = m_yValues.size();

        if (xCount != yCount) {
            return;  // 如果横坐标和纵坐标的数量不一致，直接返回
        }

        QPointF *points = new QPointF[xCount];  // 创建存储绘图点的数组
        for (int i = 0; i < xCount; ++i) {
            points[i] = QPointF(m_xValues[i]*40+100, m_yValues[i]*10);  // 将坐标点存入数组中

        }

        painter.drawPolyline(points, xCount);  // 绘制折线图
        delete[] points;  // 释放内存






}

