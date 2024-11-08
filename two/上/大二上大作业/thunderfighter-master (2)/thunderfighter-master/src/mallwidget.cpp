#include "mallwidget.h"
#include "ui_mallwidget.h"
#include "Config.h"
#include<QMessageBox>

MallWidget::MallWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::mall)
{
    ui->setupUi(this);
    this->setWindowTitle(GAME_TITLE);
    this->setWindowIcon(QIcon(GAME_ICON));
    //和原来的界面相同的位置
    this->move(500,0);
    // 设置背景图片
    setAutoFillBackground(true);    // 这句要加上, 否则可能显示不出背景图.
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,
                     QBrush(QPixmap(":/image/mall/background.jpg").scaled(    // 缩放背景图.
                         this->size(),
                         Qt::IgnoreAspectRatio,
                         Qt::SmoothTransformation)));    // 使用平滑的缩放方式
    this->setPalette(palette);
    this->show();
    ui->plane1->setText("100");
    ui->plane2->setText("300");
    ui->plane3->setText("500");
    ui->plane4->setText("1000");
    ui->plane5->setText("1200");
}

MallWidget::~MallWidget()
{
    delete ui;
}


void MallWidget::on_plane1_clicked()
{
    //账户中存储的金币，可以在ui里自动修改
    int money = ui->lineEdit_3->text().toInt();
    if(money >= 100 && ui->plane1->text() != "使用"){
        QMessageBox::information(NULL,"成功","您已经购买突击零式！");
        ui->lineEdit_3->setText(QString::number(money-100));
        ui->plane1->setText("使用");
        //之后的一些图片逻辑
    }else if(ui->plane1->text() == "使用"){
        setPlanePath(":/image/mall/i-p-01a.png");
        emit equipPlane();
        QMessageBox::information(NULL,"成功","已装备该飞机！");
    }else{
        QMessageBox::information(NULL,"失败","您的余额不足！");
    }
}

void MallWidget::on_plane2_clicked()
{
    //账户中存储的金币，可以在ui里自动修改
    int money = ui->lineEdit_3->text().toInt();
    if(money >= 300 && ui->plane2->text() != "使用"){
        QMessageBox::information(NULL,"成功","您已经购买尖锋零式,稍后游戏中将为您装备该飞机！");
        ui->lineEdit_3->setText(QString::number(money-300));
        ui->plane2->setText("使用");
        //之后的一些图片逻辑
    }else if(ui->plane2->text() == "使用"){
        setPlanePath(":/image/mall/i-p-02a.png");
        emit equipPlane();
        QMessageBox::information(NULL,"成功","已装备该飞机！");
    }else{
        QMessageBox::information(NULL,"失败","您的余额不足！");
    }
}


void MallWidget::on_plane3_clicked()
{
    //账户中存储的金币，可以在ui里自动修改
    int money = ui->lineEdit_3->text().toInt();
    if(money >= 500 && ui->plane3->text() != "使用"){
        QMessageBox::information(NULL,"成功","您已经购买猛禽零式,稍后游戏中将为您装备该飞机！");
        ui->lineEdit_3->setText(QString::number(money-500));
        ui->plane3->setText("使用");
        //之后的一些图片逻辑
    }else if(ui->plane3->text() == "使用"){
        setPlanePath(":/image/mall/i-p-03a.png");
        emit equipPlane();
        QMessageBox::information(NULL,"成功","已装备该飞机！");
    }else{
        QMessageBox::information(NULL,"失败","您的余额不足！");
    }
}


void MallWidget::on_plane4_clicked()
{
    //账户中存储的金币，可以在ui里自动修改
    int money = ui->lineEdit_3->text().toInt();
    if(money >= 1000 && ui->plane4->text() != "使用"){
        QMessageBox::information(NULL,"成功","您已经购买幻影零式,稍后游戏中将为您装备该飞机！");
        ui->lineEdit_3->setText(QString::number(money-1000));
        ui->plane4->setText("使用");
        //之后的一些图片逻辑
    }else if(ui->plane4->text() == "使用"){
        setPlanePath(":/image/mall/i-p-04a.png");
        emit equipPlane();
        QMessageBox::information(NULL,"成功","已装备该飞机！");
    }else{
        QMessageBox::information(NULL,"失败","您的余额不足！");
    }
}


void MallWidget::on_plane5_clicked()
{
    //账户中存储的金币，可以在ui里自动修改
    int money = ui->lineEdit_3->text().toInt();
    if(money >= 1200 && ui->plane5->text() != "使用"){
        QMessageBox::information(NULL,"成功","您已经购买异形零式,稍后游戏中将为您装备该飞机！");
        ui->lineEdit_3->setText(QString::number(money-1200));
        ui->plane5->setText("使用");
        //之后的一些图片逻辑
    }else if(ui->plane5->text() == "使用"){
        setPlanePath(":/image/mall/i-p-05a.png");
        emit equipPlane();
        QMessageBox::information(NULL,"成功","已装备该飞机！");
    }else{
        QMessageBox::information(NULL,"失败","您的余额不足！");
    }
}

void MallWidget::on_pay_clicked()
{
    int money=ui->lineEdit_3->text().toInt();

    QMessageBox::information(NULL,"成功","恭喜您充值成功，同时注意理性消费哦！");
    ui->lineEdit_3->setText(QString::number(money+1000));

}

QString MallWidget::getPlanePath() const
{
    return planePath;
}

void MallWidget::setPlanePath(const QString &value)
{
    planePath = value;
}




