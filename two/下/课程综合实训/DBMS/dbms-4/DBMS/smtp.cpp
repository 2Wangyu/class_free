//smtp.cpp
#include "smtp.h"
#include <QDebug>
Smtp::Smtp(QByteArray username,QByteArray password)
{
    if(username.contains("@163"))
    {
        this->username = username;
        this->password = password;
    }
    else
        qDebug()<<"NOT 163";
}

void Smtp::send(QByteArray recvaddr,QString subject,QString content)
{
    //赋值
    this->recvaddr = recvaddr;
    this->subject = subject;
    this->content = content;
    //存发送者账户和密码
    QByteArray usernametmp = this->username;
    QByteArray recvaddrtmp = this->recvaddr;
    //开始网络通信功能
    clientsocket=new QTcpSocket();
    //调用clientsocket的connectToHost方法连接到SMTP服务器（这里是网易的SMTP服务器"smtp.163.com"），端口号为25，以读写模式进行连接。
    this->clientsocket->connectToHost("smtp.163.com",25,QTcpSocket::ReadWrite);
    //连接
    this->clientsocket->waitForConnected(1000);
    this->clientsocket->waitForReadyRead(1000);
    //读取数据
    recvdata = clientsocket->readAll();
    //qDebug()<<recvdata;
    //向服务器发送“HELO”命令，这是SMTP协议中的一个标准命令，用于标识客户端并初始化会话。这里使用的标识是“smtp.163.com”。
    this->clientsocket->write("HELO smtp.163.com\r\n");
    this->clientsocket->waitForReadyRead(1000);
    recvdata = clientsocket->readAll();
    //qDebug()<<recvdata;
    this->clientsocket->write("AUTH LOGIN\r\n");
    this->clientsocket->waitForReadyRead(1000);
    recvdata = clientsocket->readAll();
    //qDebug()<<recvdata;
    //qDebug()<<"username:"<<username;

    //发送用户名和密码进行身份验证。这里使用了Base64编码，因为SMTP协议通常要求以这种方式发送凭据。
    this->clientsocket->write(username.toBase64().append("\r\n"));
    this->clientsocket->waitForReadyRead(1000);
    recvdata = clientsocket->readAll();
    //qDebug()<<recvdata;
    //qDebug()<<"password:"<<password;
    this->clientsocket->write(password.toBase64().append("\r\n"));
    this->clientsocket->waitForReadyRead(1000);
    recvdata = clientsocket->readAll();
    //qDebug()<<recvdata;

    //发送邮件的发送者地址和接收者地址。这些地址是SMTP命令的一部分，用于指定邮件的发送和接收方。
    this->clientsocket->write(mailfrom.append(usernametmp.append(">\r\n")));
    this->clientsocket->waitForReadyRead(1000);
    recvdata = clientsocket->readAll();
    //qDebug()<<recvdata;
    //发送邮箱
    this->clientsocket->write(rcptto.append(recvaddrtmp.append(">\r\n")));
    this->clientsocket->waitForReadyRead(1000);
    recvdata = clientsocket->readAll();
    //qDebug()<<recvdata;

    //接收邮箱
    //data表示开始传输数据
    this->clientsocket->write("data\r\n");
    this->clientsocket->waitForReadyRead(1000);
    recvdata = clientsocket->readAll();
    //qDebug()<<recvdata;
    usernametmp = this->username;
    recvaddrtmp = this->recvaddr;
    this->clientsocket->write(prefrom.append(usernametmp.append("\r\n")));
    this->clientsocket->write(preto.append(recvaddrtmp.append("\r\n")));
    this->clientsocket->write(presubject.append(subject.toLocal8Bit().append("\r\n")));
    this->clientsocket->write("\r\n");
    this->clientsocket->write(content.toLocal8Bit().append("\r\n"));
    this->clientsocket->write(".\r\n");
    this->clientsocket->waitForReadyRead(1000);
    recvdata = clientsocket->readAll();
    this->clientsocket->write("quit\r\n");
    this->clientsocket->waitForReadyRead(1000);
    recvdata = clientsocket->readAll();


}
Smtp::~Smtp()
{
    delete this->clientsocket;
}

