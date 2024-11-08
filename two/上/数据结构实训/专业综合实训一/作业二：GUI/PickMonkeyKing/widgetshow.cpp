#include "widgetshow.h"
#include<QVBoxLayout>
#include<QPushButton>
#include<QLineEdit>
#include<QFormLayout>
#include<QLabel>
#include<QTextEdit>
#include<QMessageBox>
#include"pickking.h"
#include<QPixmap>
#include<pickking.h>
#include<QList>
#include<QString>
#include<QDebug>

WidgetShow::WidgetShow(QWidget *parent)
    : QWidget(parent)
{
    //设置窗口的属性
    //设置窗口标题
    this->setWindowTitle("Pick monkey king");
    //设置窗口的固定大小
    this->setFixedSize(800,800);

    //创建两个显示图标的界面
    edit1=new QGridLayout();
    edit2=new QTextEdit();

    //
    QHBoxLayout* hbox = new QHBoxLayout();//创建布局管理器对象，为垂直布局
    //对水平的Box添加组件
    //创建两个输入猴子总数和出列编号的位置
    text1=new QLineEdit();
    text2=new QLineEdit();


    QFormLayout* fo1=new QFormLayout();
    fo1->addRow("number of Monkey",text1);
    QFormLayout* fo2=new QFormLayout();
    fo2->addRow("listing number",text2);

    //创建开始游戏的按钮
    button=new QPushButton;
    button->setText("Start");
    //设置点击按钮后的相关操作
    connect(button,&QPushButton::clicked,this,&WidgetShow::on_button_clicked);
    King=new QPushButton;
    King->setText("King");
    connect(King,&QPushButton::clicked,this,&WidgetShow::on_King_clicked);

    //加入布局管理器当中
    //hbox->setSpacing(30);//设置按钮之间的距离
    hbox->addLayout(fo1);
    hbox->addLayout(fo2);
    hbox->addWidget(button);//将组件添加到布局管理器
    hbox->addWidget(King);



    QVBoxLayout *vbox=new QVBoxLayout;
    vbox->addLayout(hbox);
    vbox->addLayout(edit1);
    vbox->addWidget(edit2);
    vbox->setStretch(0,1);//设置索引为0的按钮大小的比例系数为1
    vbox->setStretch(1,8);//设置索引为0的按钮大小的比例系数为1
    vbox->setStretch(2,8);//设置索引为0的按钮大小的比例系数为1


    setLayout(vbox);//为顶级widget设置一个布局管理器
}

WidgetShow::~WidgetShow()
{
}




//对游戏过程进行展示
void WidgetShow::on_button_clicked(){
    bool ok;
    QString temnum1=text1->text();
    QString temnum2=text2->text();
    if(temnum1==NULL||temnum2==NULL){

          //弹出需要输入数字的提醒
        QMessageBox *box1=new QMessageBox();
        box1->setText("Please enter the number!");
        box1->setWindowTitle("Warning!");
        box1->exec();

    }
    else{
    int num=temnum1.toInt(&ok);
    int listingnum=temnum2.toInt(&ok);
      if(num<=0||listingnum<=0){

          //弹出需要输入数字有误的提醒
          QMessageBox *box2=new QMessageBox();
          box2->setText("Please enter the correct number!");
          box2->setWindowTitle("Warning!");
          box2->exec();

      }
      else{
          int j=1;
          //展示未出列前猴子的排序
          while (j<=num) {
               //QVBoxLayout* vbox=new QVBoxLayout;//创建布局管理器对象
               QLabel  *label1=new QLabel();
               label1->setText(QString::number(j));
               label1->resize(800,80);

               edit1->addWidget(label1,1,j-1);
               QLabel  *label2=new QLabel();
               label2->setText(QString::number(j));
               QImage *img=new QImage;
               img->load(":/new/prefix2/image/Monkey1.jpg");
               label2->setPixmap(QPixmap::fromImage(*img));
               label2->resize(800,80);
               edit1->addWidget(label2,0,j-1);
               j++;

          }
          QString string;
          //对猴子的出列顺序进行展示
          PickKing* pk=new PickKing;
          pk->CreatingRing(num);
          int k=1;
          list=pk->StartJR(listingnum);
          while(k<=num-1){
              string=string.append("🐒[");
              string=string.append(list[k-1]).append("] ");
              edit2->setText(string);
              k++;}

          //找到挑选出来的猴子大王
          number=list[num-1];

      }
    }
}
void WidgetShow::on_King_clicked(){

    //弹出需要输入数字的提醒
  QMessageBox *box1=new QMessageBox();
  QString string="🐒[";
  string.append(number);
  string.append("] is the king");
  box1->setText(string);

  box1->setWindowTitle("the number of Monkey king!");
  box1->exec();


}
