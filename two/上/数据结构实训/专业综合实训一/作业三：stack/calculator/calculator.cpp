#include "calculator.h"
#include "ui_calculator.h"
#include<QButtonGroup>
#include<QList>
#include<QDebug>
#include<QFile>
#include<fstream>
//#include"Stack.cpp"
#include<QTextEdit>
#include<math.h>
#include<unordered_map>
using namespace std;



calculator::calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::calculator)
{
    ui->setupUi(this);

}

calculator::~calculator()
{
    delete ui;
}

//这些按钮点击时直接显示出来即可
void calculator::on_pushButton_1_clicked()
{
   QPushButton *bt=(QPushButton *)sender();//返回发射信号的控件指针
   QString name=bt->text();
   ui->lineEdit_sysin->insert(name);

}

void calculator::on_pushButton_2_clicked()
{
    QPushButton *bt=(QPushButton *)sender();//返回发射信号的控件指针
    QString name=bt->text();
    ui->lineEdit_sysin->insert(name);
}

void calculator::on_pushButton_3_clicked()
{
    QPushButton *bt=(QPushButton *)sender();//返回发射信号的控件指针
    QString name=bt->text();
    ui->lineEdit_sysin->insert(name);
}

void calculator::on_pushButton_point_clicked()
{
    QPushButton *bt=(QPushButton *)sender();//返回发射信号的控件指针
    QString name=bt->text();
    ui->lineEdit_sysin->insert(name);
}

void calculator::on_pushButton_0_clicked()
{   QPushButton *bt=(QPushButton *)sender();//返回发射信号的控件指针
    QString name=bt->text();
    ui->lineEdit_sysin->insert(name);

}

void calculator::on_pushButton_right_clicked()
{
    QPushButton *bt=(QPushButton *)sender();//返回发射信号的控件指针
    QString name=bt->text();
    ui->lineEdit_sysin->insert(name);
}

void calculator::on_pushButton_left_clicked()
{
    QPushButton *bt=(QPushButton *)sender();//返回发射信号的控件指针
    QString name=bt->text();
    ui->lineEdit_sysin->insert(name);
}

void calculator::on_pushButton_9_clicked()
{
    QPushButton *bt=(QPushButton *)sender();//返回发射信号的控件指针
    QString name=bt->text();
    ui->lineEdit_sysin->insert(name);
}

void calculator::on_pushButton_8_clicked()
{
    QPushButton *bt=(QPushButton *)sender();//返回发射信号的控件指针
    QString name=bt->text();
    ui->lineEdit_sysin->insert(name);
}

void calculator::on_pushButton_7_clicked()
{
    QPushButton *bt=(QPushButton *)sender();//返回发射信号的控件指针
    QString name=bt->text();
    ui->lineEdit_sysin->insert(name);
}

void calculator::on_pushButton_plus_clicked()
{
    QPushButton *bt=(QPushButton *)sender();//返回发射信号的控件指针
    QString name=bt->text();
    ui->lineEdit_sysin->insert(name);
}

void calculator::on_pushButton_minus_clicked()
{
    QPushButton *bt=(QPushButton *)sender();//返回发射信号的控件指针
    QString name=bt->text();
    ui->lineEdit_sysin->insert(name);
}

void calculator::on_pushButton_mult_clicked()
{
    QPushButton *bt=(QPushButton *)sender();//返回发射信号的控件指针
    QString name=bt->text();
    ui->lineEdit_sysin->insert(name);
}

void calculator::on_pushButton_rid_clicked()
{
    QPushButton *bt=(QPushButton *)sender();//返回发射信号的控件指针
    QString name=bt->text();
    ui->lineEdit_sysin->insert(name);
}
void calculator::on_pushButton_4_clicked()
{
    QPushButton *bt=(QPushButton *)sender();//返回发射信号的控件指针
    QString name=bt->text();
    ui->lineEdit_sysin->insert(name);
}

void calculator::on_pushButton_5_clicked()
{
    QPushButton *bt=(QPushButton *)sender();//返回发射信号的控件指针
    QString name=bt->text();
    ui->lineEdit_sysin->insert(name);
}

void calculator::on_pushButton_6_clicked()
{
    QPushButton *bt=(QPushButton *)sender();//返回发射信号的控件指针
    QString name=bt->text();
    ui->lineEdit_sysin->insert(name);
}

//清空内容
void calculator::on_pushButton_clear_clicked()
{
    ui->lineEdit_sysin->setText("");
    ui->lineEdit_sysout->setText("");
    string1=string2="";

}
//回退
void calculator::on_pushButton_back_clicked()
{
    ui->lineEdit_sysin->setCursorPosition(ui->lineEdit_sysin->cursorPosition()-1);
    ui->lineEdit_sysin->del();
}

//三个附加项平方开方和倒数
void calculator::on_pushButton_reverse_clicked()
{
    ui->lineEdit_sysin->insert("^-1");
}
void calculator::on_pushButton_twice_clicked()
{
    ui->lineEdit_sysin->insert("^2");
}
void calculator::on_pushButton_half_clicked()
{
    ui->lineEdit_sysin->insert("^0.5");
}


void calculator::on_pushButton_equal_clicked()
{
    stack1=new Stack<char>();
    stack2=new Stack<double>();
    //判断输入合法
    if(!isValid())
        return;


    //将字符进行转换
    //用于存储操作符号


    //将输入的内容转化成char数组以方便进行预处理
    string1=ui->lineEdit_sysin->text();
    char* ch;
    QByteArray ba = string1.toLatin1();//must
    ch=ba.data();
    //获取输入的一串字符的长度
    int len=string1.length();

    for(int i=0;i<len;i++){


        //左括号直接入栈
        if(ch[i]=='('){
            stack1->push(ch[i]);
            //处理符号的情况
            if(ch[i+1]=='-'){
            int j=i+2;


            //用于判断多个小数点的问题
            int num=0;
            while(isNumber(ch[j])||ch[j]=='.'){
                if(ch[j]=='.')
                    num++;

                j++;
            }
            if(num>1){
                string2="error:一个操作数不能有多个小数点";
                ui->lineEdit_sysout->setText(string2);
                record->append(string2);
                return;
            }

            QString str=string1;
            QString str1=str.mid(i+2,j-i-2);
            double b=str1.toDouble();
            b=0-b;
            stack2->push(b);
            i=j-1;
            }

        }

        //处理右括号
        else if(ch[i]==')'){
            //特殊情况(数)
            if(stack1->getFront()=='('){
                stack1->pop();
            }
            //根据运算只会剩下一个运算符号，直接出栈计算
            else{

                double a=stack2->getFront();
                stack2->pop();
                double b=stack2->getFront();
                 stack2->pop();
                char c=stack1->getFront();
                stack1->pop();
                double d;
                //计算内部的四则运算
                if(c=='+')
                    d=a+b;
                else if(c=='-')
                    d=b-a;
                else if(c=='*')
                    d=a*b;
                else{
                    if(a==0){
                        string2="error:0不做除数";
                        ui->lineEdit_sysout->setText(string2);
                        record->append(string2);
                        return;
                    }
                    d=b/a;
                }

                //压入栈中
                stack2->push(d);
                //左括号出栈
                stack1->pop();
            }
        }


        //对于附加功能的处理
        else if(ch[i]=='^'){

            //三种情况
            //^2
            if(ch[i+1]=='2'){
                double a=stack2->getFront();
                stack2->pop();
                a=pow(a,2);
                stack2->push(a);
                i++;
            }
            //^0.5
            else if(ch[i+1]=='0'){
                double a=stack2->getFront();
                stack2->pop();
                if(a<0){
                    string2="error:负数不能开根";
                    ui->lineEdit_sysout->setText(string2);
                    record->append(string2);
                    return ;
                }
                a=pow(a,0.5);
                stack2->push(a);
                i=i+3;
            }
            //^-1
            else{
                double a=stack2->getFront();
                stack2->pop();
                //对于0没有倒数
                  if(a==0){
                      string2="error:0无倒数";
                      ui->lineEdit_sysout->setText(string2);
                      record->append(string2);
                      return ;
                  }
                a=pow(a,-1);
                stack2->push(a);
                i=i+2;
            }

        }

        //对于四则运算
        else if (ch[i]=='+'||ch[i]=='-'||ch[i]=='*'||ch[i]=='/') {
            if(stack1->IsEmpty()||stack1->getFront()=='('){
                stack1->push(ch[i]);
            }
            else{
                bool a=compare(ch[i],stack1->getFront());
                if(a==true){
                    stack1->push(ch[i]);
                }
                else{
                    double a=stack2->getFront();
                    stack2->pop();
                    double b=stack2->getFront();
                     stack2->pop();
                    char c=stack1->getFront();
                    stack1->pop();
                    double d;
                    //计算内部的四则运算
                    if(c=='+')
                        d=a+b;
                    else if(c=='-')
                        d=b-a;
                    else if(c=='*')
                        d=a*b;
                    else{
                        if(a==0){
                            string2="error:0不做除数";
                            ui->lineEdit_sysout->setText(string2);
                            record->append(string2);
                            return;
                        }
                        d=b/a;
                    }

                    //压入栈中
                    stack2->push(d);
                    stack1->push(ch[i]);
                }
            }

        }

        //数字处理
        else if(isNumber(ch[i])){
            int j=i+1;

            //用于判断多个小数点的问题
            int num=0;

            while(isNumber(ch[j])||ch[j]=='.'){
                if(ch[j]=='.')
                    num++;

                j++;
            }
            if(num>1){
                string2="error:一个操作数不能有多个小数点";
                ui->lineEdit_sysout->setText(string2);
                 record->append(string2);
                return;
            }
            QString str=string1;
            QString str1=str.mid(i,j-i);
            double b=str1.toDouble();
            stack2->push(b);
            i=j-1;

            }

        }




    while(stack1->IsEmpty()==false){
        double a=stack2->getFront();
        stack2->pop();
        double b=stack2->getFront();
        stack2->pop();
        char c=stack1->getFront();
        stack1->pop();
        double d;
        //计算内部的四则运算
        if(c=='+')
            d=a+b;
        else if(c=='-')
            d=b-a;
        else if(c=='*')
            d=a*b;
        else{
            if(a==0){
                string2="error:0不做除数";
                ui->lineEdit_sysout->setText(string2);
                 record->append(string2);
                return;
            }
            d=b/a;
        }

        //压入栈中
        stack2->push(d);
    }

    //对于未输入数据且符合表达式的
    if(stack2->IsEmpty()){
        string2="请输入数据";//代表保留小数点后7位
        record->append(string2);
        ui->lineEdit_sysout->setText(string2);

    }

    else{
    double a=stack2->getFront();
    stack2->pop();
    string2=QString::number(a,'f', 7);//代表保留小数点后7位
    record->append(string2);
    ui->lineEdit_sysout->setText(string2);
}

}


//判断是否位数字
bool calculator::isNumber(char number){
    if(number=='0'||number=='1'||number=='2'||number=='3'||number=='4'||number=='5'
            ||number=='6'||number=='7'||number=='8'||number=='9')
        return true;
    else
        return false;


}




//判断数据合法的逻辑
bool calculator::isValid(){
    //将输入的内容转化成char数组以方便进行预处理
    string1=ui->lineEdit_sysin->text();
    record->append(string1);
    char*  ch;
    QByteArray ba = string1.toLatin1(); // must
    ch=ba.data();
    //获取输入的一串字符的长度
    int len=string1.length();
    //对数据进行预处理：平方开方倒数等进行处理
    //判断输入数据的合法性：错误则退出并提示

    //判断是否输入
    if(string1==NULL){

        string2="Input please!";
        ui->lineEdit_sysout->setText(string2);
        record->append(string2);
        return false;
    }


    //对第一个字符进行判断
    if(!isNumber(ch[0])&&ch[0]!='('){
        string2="error:the first parameter you input is wrong! ";
        ui->lineEdit_sysout->setText( string2);
        record->append(string2);
        return false;
    }



//需要对输入的最后一个数据进行单独检验
    for(int i=0;i<len-1;i++){
        //数字后面不可以跟‘（’
        if(isNumber(ch[i])){

            if(ch[i+1]=='('){
                string2="error:number+'(' is wrong!";
                ui->lineEdit_sysout->setText( string2);
                record->append(string2);
                return false;
            }

        }

        else if(ch[i]=='^'){
            //三种情况
            //^2
            if(ch[i+1]=='2'){
                i++;
            }
            //^0.5
            else if(ch[i+1]=='0'){
                i=i+3;
            }
            //^-1
            else{
                i=i+2;
            }
            if(isNumber(ch[i+1])||ch[i+1]=='('||ch[i+1]=='.'){
                string2="error:附加功能后输入错误!";
                ui->lineEdit_sysout->setText( string2);
                record->append(string2);
                return false;
            }


        }

        else if(ch[i]=='+'||ch[i]=='-'||ch[i]=='*'||ch[i]=='/'){
            //四则运算后必须跟数字或者左括号
            if((!isNumber(ch[i+1]))&&ch[i+1]!='(')
            {
                string2="error:四则运算后输入错误";
                ui->lineEdit_sysout->setText( string2);
                record->append(string2);
                return false;
            }
        }

        //'.'后必跟数字
        else if(ch[i]=='.'){
            if(!isNumber(ch[i+1])){
                string2="error:符号‘.’后跟数字";
                ui->lineEdit_sysout->setText( string2);
                record->append(string2);
                return false;
            }
        }

        //括号的判断
        else{
                if(ch[i]=='('){
                    if(!isNumber(ch[i+1])&&ch[i+1]!='-'&&ch[i+1]!=')'&&ch[i+1]!='('){
                        string2="error:左括号后跟数字或者'负号或者‘）’";
                        ui->lineEdit_sysout->setText( string2);
                        record->append(string2);
                        return false;
                    }
                }

                else{
                    if(isNumber(ch[i+1])||ch[i+1]=='('||ch[i+1]=='.')
                    {
                        string2="error:右括号后错误";
                        ui->lineEdit_sysout->setText( string2);
                        record->append(string2);
                        return false;
                    }

              }
           }


        }
    if(ch[len-1]=='+'||ch[len-1]=='-'||ch[len-1]=='*'||ch[len-1]=='/'||ch[len-1]=='('||ch[len-1]=='.'){
        string2="结尾错误";
        ui->lineEdit_sysout->setText( string2);
        record->append(string2);
        return false;
    }
    if(!validEnco(string1)){
        string2="括号不匹配";
        ui->lineEdit_sysout->setText(string2);
        record->append(string2);
        return false;
    }

    return true;
}



//显示历史记录
void calculator::on_pushButton_record_clicked()
{

    record->resize(600,800);
    record->setEnabled(false);
    a->resize(600,800);
    a->setWindowTitle("record");
    QVBoxLayout *vbox=new QVBoxLayout;
    vbox->addWidget(record);
    a->setLayout(vbox);


    a->show();
}

bool calculator::validEnco(QString tem){
    //将输入的内容转化成char数组以方便进行预处理
    Stack<char>* stack1=new Stack<char>;
    char*  ch;
    QByteArray ba = tem.toLatin1(); // must
    ch=ba.data();
    //获取输入的一串字符的长度
    int len=string1.length();
      for(int i=0;i<len;i++){
          if(ch[i]=='('){
              stack1->push(ch[i]);
          }
          if(ch[i]==')'){
              if(stack1->IsEmpty())
                  return false;
              else
                  stack1->pop();
          }
      }
      if(stack1->IsEmpty())
         return true;
      else
         return false;
}


//优先级的处理
bool calculator::compare(char a, char b){
    unordered_map<char,int> map={
        {'+','1'},
        {'-','1'},
        {'*','2'},
        {'/','2'}
    };
    if(map[a]<=map[b]){
        return false;
    }
    else
        return true;


}
