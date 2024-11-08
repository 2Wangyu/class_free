#ifndef SIGNUPWIDGET_H
#define SIGNUPWIDGET_H

#include <QWidget>

namespace Ui {
class signupwidget;
}

class signupwidget : public QWidget
{
    Q_OBJECT

public:
    explicit signupwidget(QWidget *parent = nullptr);
    ~signupwidget();
     QString  code;

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::signupwidget *ui;
};

#endif // SIGNUPWIDGET_H
