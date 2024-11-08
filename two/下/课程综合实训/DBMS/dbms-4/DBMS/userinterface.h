#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <QWidget>
#include "createtable.h"
#include "droptable.h"
#include "altertable.h"

namespace Ui {
class UserInterface;
}

class UserInterface : public QWidget
{
    Q_OBJECT

public:
    explicit UserInterface(QWidget *parent = nullptr);
    ~UserInterface();
    QString username;
    void writelog(QString username,QString operation,QString date);

private slots:
    void on_GO_clicked();

    // 连接按钮的clicked()信号和槽函数
    //connect(GO, &QPushButton::clicked, this, &Widget::openFile);



    void on_GO_2_clicked();

private:
    Ui::UserInterface *ui;

public slots:
    void openFile(QString text);

public slots:
    void receiveData(const QString &data); // 定义一个接收数据的槽函数


};

#endif // USERINTERFACE_H
