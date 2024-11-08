#ifndef MALL_H
#define MALL_H

#include <QWidget>
#include <QStyleOption>
#include <QPainter>
#include <QStyle>
namespace Ui {
class mall;
}

class MallWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MallWidget(QWidget *parent = nullptr);
    ~MallWidget();

    QString getPlanePath() const;
    void setPlanePath(const QString &value);

signals:
    void equipPlane();

private slots:
    void on_plane1_clicked();
    void on_plane2_clicked();
    void on_plane3_clicked();
    void on_plane4_clicked();
    void on_plane5_clicked();
    void on_pay_clicked();

private:
    Ui::mall *ui;
    QString planePath;
};

#endif // MALL_H
