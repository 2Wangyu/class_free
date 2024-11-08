#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopServices>
#include <QUrl>
#include<QDebug>
#include<QFileDialog>
#include <fstream>
#include <iostream>
#include <string>
#include <locale>
#include <map>
#include <algorithm>
#include <queue>
#include"huffmantree.h"
#include <QFile>
#include <QTextStream>
#include<QTimer>
#include<QDir>
//#include <filesystem>
#include <cstdlib>
#include <sstream>
#include <bitset>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{


    ui->setupUi(this);
    Initwindow();
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_pushButton_clicked()
{
    QUrl url;
    url.setScheme("file");
    url.setPath("C:\\Qt\\qt\\HuffmanCompressor\\compress");

    if(QDesktopServices::openUrl(url)) {
        ui->textEdit->append("成功打开指定盘,对比解压缩和压缩功能");
    } else {
        ui->textEdit->append( "无法打开指定盘");
    }


}

void MainWindow::on_pushButton_2_clicked()
{
    // 打开文件夹并获取文件路径   , "C:\\Qt\\qt\\HuffmanCompressor\\compress",
    QString filePath = QFileDialog::getOpenFileName(nullptr, "打开文件");
    //qDebug()<<filePath;
    std::string filename ;
    //找到文件名
    size_t lastBackslashPos = filePath.toStdString().rfind('/');
    if (lastBackslashPos != std::string::npos) {
    filename = filePath.toStdString().substr(lastBackslashPos + 1);
       qDebug() << "Filename: " << QString::fromStdString(filename) << endl;
    } else {
       qDebug()<< "No backslash found." << endl;
        }
    //文件后缀和文件无后缀的名称

    std::stringstream ss(filename);
    std::string token;
    std::string str1, str2;
    while (std::getline(ss, token, '.')) {
           if (token.empty()) {
               continue;
           }
           if (token.back() == ',') {
               token.pop_back();
           }
           if (token.empty()) {
               continue;
           }
           if (str1.empty()) {
               str1 = token;
               qDebug() <<  QString::fromStdString(str1) << endl;
           } else {
               str2 = token;
               qDebug() <<  QString::fromStdString(str2) << endl;
           }
       }


//文件的压缩处理
    if (!filePath.isEmpty()) {
        // 将文件路径传入Qt中处理，例如打印到控制台或进行其他操作
       ui->textEdit->append( filePath+"存在，开始解压！");
    } else {
       ui->textEdit->append("未选择文件,无法解压！");
        return;
    }
     std::map<char, int> charFrequency; // 定义map容器来存储字符频率

     std::ifstream file(filePath.toStdString(),std::ios::binary);

     if(!file.is_open()){
         ui->textEdit->append("Failed to open");
     }
     char c;
     //逐个读取文件内容
     while(file.read(reinterpret_cast<char*>(&c),sizeof(c))){

             ++charFrequency[c];
     }
     file.close();
     ui->textEdit->append("频率-字符存储完成");


//          // 将charFrequency中的pair存储到优先队列中
//     std::priority_queue<std::pair<char, int>, std::vector<std::pair<char, int>>,Compare> pq;

//     for (const auto& pair : charFrequency) {
//         pq.push(pair);
//            }
//            // 按照频率值从优先队列中提取pair，并输出每个字符及其频率
//      while (!pq.empty()) {

//                pair<char,int> temp = pq.top();
//                pq.pop();
//                qDebug()<< "Character: " << temp.first << ", Frequency: " << temp.second;
//            }




      HuffmanTree *huff=new HuffmanTree(charFrequency);
      ui->textEdit->append("哈夫曼编码ok");
      map=huff->getHuffmanCodeString();


      static int n=1;
      //将哈夫曼编码记忆性存储进去
      compressmap[n]=map;
      finalname[n]=filename;

      // 替换为你的文件路径
      QString fileName = "C:\\Qt\\qt\\HuffmanCompressor\\compress\\compressed\\"+QString::fromStdString(str1)+".txt";

//       创建一个文件并写入内容
      //QFile file3(fileName);
      std::ofstream file2(fileName.toStdString()); // 打开二进制文件
      if (file2.is_open()) {
          //QTextStream out(&file3);

          //file2.write(reinterpret_cast<char*>(&n), sizeof(n));
          //file2.write(reinterpret_cast<char*>(&num), sizeof(num));
          //out<<QString::number(n);

          char ch = static_cast<char>(n+48);
          std::vector<char> buffer = {ch};
          file2.write(buffer.data(), 1);
          n++;
          // 更新进度条
          //逐个读取文件内容
          std::ifstream file3(filePath.toStdString(),std::ios::binary);
          //记录asci
          std::string asci="";
          while(file3.read(reinterpret_cast<char*>(&c),sizeof(c))){
              // 使用迭代器遍历map并找到对应的键值对
                 auto it = map.find(c);
                 if (it != map.end()) {

                     asci+=it->second;
                     if(asci.length()>=8){
                         std::string substring=asci.substr(0,8);
                         //算出它的asci码值
                        int decimalNumber = std::stoi(substring, nullptr, 2);  // 转换为十进制
                        char ch = static_cast<char>(decimalNumber);

                         std::string temp=asci.substr(8,asci.length());
                         asci=temp;
                         std::vector<char> buffer = {ch};
                         file2.write(buffer.data(), 1);

                         //file2.write( reinterpret_cast<const char*>(static_cast<unsigned char>(std::stoi(substring, nullptr, 2))),1);
                         //out<<QString(ch);
                     //找到读取的指针位置
                         std::streampos currentPos = file3.tellg();
                     //求出百分比
                         int progress = (int)((double)currentPos / (double)file3.seekg(0, ios::end).tellg() * 100);
                     //让指针回到原来的指向位置
                         file3.seekg(currentPos);
                     //更新
                         updateProgress(progress);

                     }
                 }

          }
          if(asci!=""){
             file2.write(asci.c_str(), sizeof (asci));
          }
          updateProgress(100);
          ui->textEdit->append("压缩完成");

          file2.close();  // 关闭文件
          file3.close();
      }
          else {
          // 如果创建文件或写入文件失败，处理错误
          ui->textEdit->append("Unable to open the file:");
      }

}

void MainWindow::on_pushButton_3_clicked()
{
    // 打开文件夹并获取文件路径   , "C:\\Qt\\qt\\HuffmanCompressor\\compress",
    QString filePath = QFileDialog::getOpenFileName(nullptr, "打开文件");
    if (!filePath.isEmpty()) {
        // 将文件路径传入Qt中处理，例如打印到控制台或进行其他操作
        ui->textEdit->append( filePath+"存在，开始解压缩");
    } else {
       ui->textEdit->append("未选择文件，无法解压缩文件");
    }

    //获取文件名
    std::ifstream file(filePath.toStdString()); // 打开文件
    if (!file) {
       ui->textEdit->append( "无法打开文件写入");
               }
    else{
        string str="";
        char ch;
        file.get(ch);
        int a=std::stoi(std::string(1, ch));
        file.close();
        QString fileName = "C:\\Qt\\qt\\HuffmanCompressor\\compress\\decompress\\"+QString::fromStdString(finalname[a]);  // 替换为你的文件路径
    decode(fileName,filePath);
       //使用默认的程序打开文件
       // 定义文件路径和文件名
    std::string filePath1 = fileName.toStdString();
         // 使用系统命令打开文件
    std::string command = "start " + filePath1;
    system(command.c_str());

}
}
void MainWindow::decode(QString fileName,QString filePath){
//    QString  sourceName= ("C:/Qt/qt/HuffmanCompressor/compress/"+QString::fromStdString(finalname[a])); ;
//    QString targetName = ("C:/Qt/qt/HuffmanCompressor/compress/decompress/"+QString::fromStdString(finalname[a]));
//    QFile sourceFile(sourceName);
//                if (!sourceFile.open(QIODevice::ReadOnly)) {
//                    qDebug() << "无法打开源文件：" ;
//                }
//                QFile destinationFile(targetName);
//                if (destinationFile.exists()) {
//                 destinationFile.remove();}
//                if (!destinationFile.open(QIODevice::WriteOnly)) {
//                    qDebug() << "无法创建目标文件：" ;
//                    return;
//               }
//                destinationFile.write(sourceFile.readAll());
//                destinationFile.close();
//                sourceFile.close();
    int a;
    //       创建一个文件并写入内容
    std::ofstream file1(fileName.toStdString(), std::ios::binary); // 打开二进制文件
    //if (file1.open(QIODevice::WriteOnly | QIODevice::Text))
    if(file1.is_open()){

         //QTextStream out(&file1);
         std::ifstream file(filePath.toStdString()); // 打开文件
         if (!file) {
            ui->textEdit->append( "无法打开文件写入");
                    }
         else{
             string str="";

             char ch;
             file.get(ch);
             a=static_cast<int>(ch);
             a=a-48;

             std::map<char,string> tempmap=compressmap[a];

             std::string binary_repr="";

             QString line="";
             while (file.get(ch)) { // 逐个读取字符
                 int ascii_val = static_cast<int>(ch); // 获取ASCII码值
                 // 将ASCII码值转换为二进制数字并存储在string中
                 binary_repr += std::bitset<8>(ascii_val).to_string();

                int length=0;
                for (const auto& pair : tempmap) {
                     length++;
                }
                // str=str+ch;
                 while (true) {
                     int n=0;
                 for (const auto& pair : tempmap) {
                      n++;
                        //if (pair.second == str) { // 如果找到匹配的值
                           //指针
                            size_t pos = 0;
                            while (pos < binary_repr.length() && pos < pair.second.length() && binary_repr[pos] == pair.second[pos]) {
                                 ++pos;
                             }
                             if (pos == binary_repr.length() && pos == pair.second.length()) {
                                file1.write(&pair.first,sizeof(pair.first));
                                binary_repr="";
                                n=0;
                                 // 全部字符都匹配，返回空字符串
                             } else if (pos == pair.second.length()) {
                                 std::string temp=binary_repr.substr(pos);
                                 binary_repr= temp;
                                 file1.write(&pair.first,sizeof(pair.first));
                                 // 匹配到pair结尾，返回剩余字符串
                                 n=0;
                             }
                            //file1.write(&pair.first,sizeof(pair.first));
                           // str="";
                       // }

                }
                 if(n==length)
                     break;
                 }
                 //找到读取的指针位置
                 std::streampos currentPos = file.tellg();
                 //求出百分比
                 int progress = (int)((double)currentPos / (double)file.seekg(0, ios::end).tellg() * 100);
                 //让指针回到原来的指向位置
                 file.seekg(currentPos);
                 //更新
                 updateProgress(progress);
                       }
             if(binary_repr!=""){

             }

           }
        updateProgress(100);
        ui->textEdit->append("解压完成！");
         file1.close(); // 关闭文件


         file.close();  // 关闭文件

    }
    else {
        // 如果创建文件或写入文件失败，处理错误
        ui->textEdit->append( "Unable to open the file:" );
    }
}
void MainWindow::updateProgress(int value) // 更新进度槽函数
{
    // 根据文件读取的完成率更新进度条的值，并根据需要显示或隐藏进度条
    progressBar->setValue(value); // 设置进度条的值
    dialog->setVisible(true);
    dialog->show();
//    // 创建QTimer对象，并设置定时器时间间隔为seconds秒
//    QTimer *timer = new QTimer(this);
//    timer->setInterval(1000); // 单位为毫秒
//    // 连接定时器的timeout信号到槽函数，实现等待的功能
//    connect(timer, &QTimer::timeout, [=](){

//    });
//    // 启动定时器
//    timer->start();

}
void MainWindow::Initwindow(){
    dialog=new QDialog(this);
    dialog->setWindowTitle("进度条");
    dialog->setGeometry(100,100,300,100);

    progressBar = new QProgressBar(dialog);
    progressBar->setMaximum(100); // 设置进度条的最大值
    progressBar->setGeometry(50,50,200,25);
    progressBar->setValue(0); // 初始值为0
    progressBar->setVisible(true); // 初始时隐藏进度条
    dialog->setVisible(false);

}

void MainWindow::on_pushButton_4_clicked()
{

    QStringList fileNames = QFileDialog::getOpenFileNames(NULL, "选择文件", "", "所有文件 (*);;文本文件 (*.txt)");
    if (!fileNames.isEmpty()) {

        ui->textEdit->append( "选择的文件，开始解压缩");

        for (const QString &fileNamem : fileNames)
        {
            qDebug() << fileNamem;
            //获取文件名
            std::ifstream file(fileNamem.toStdString()); // 打开文件
            if (!file) {
               ui->textEdit->append( "无法打开文件写入");
                       }
            else{
                string str="";
                char ch;
                file.get(ch);
                int a=std::stoi(std::string(1, ch));
                QString fileName = "C:\\Qt\\qt\\HuffmanCompressor\\compress\\decompress\\"+QString::fromStdString(finalname[a]);  // 替换为你的文件路径
            decode(fileName,fileNamem);
               //使用默认的程序打开文件
               // 定义文件路径和文件名
            std::string filePath1 = fileName.toStdString();
                 // 使用系统命令打开文件
            std::string command = "start " + filePath1;
            system(command.c_str());

        }
        ui->textEdit->append("解压缩完成！");
    }
    }
    else {

        ui->textEdit->append( "未选择文件");
    }





}

void MainWindow::on_pushButton_5_clicked()
{
    // 指定要删除文件的文件夹路径，例如在C盘根目录下
      QString folderPath1 = "C:\\Qt\\qt\\HuffmanCompressor\\compress\\compressed";
      QString folderPath2 = "C:\\Qt\\qt\\HuffmanCompressor\\compress\\decompress";
      // 创建QDir对象
      QDir directory1(folderPath1);
      // 遍历文件夹中的所有文件并删除
      QStringList files1 = directory1.entryList(QDir::Files);
      for (const QString& file : files1) {
          QString filePath = directory1.absoluteFilePath(file);
          bool result = QFile::remove(filePath);
          if (!result) {
              ui->textEdit->append("删除文件" +filePath + "失败！");
          }
      }
      // 创建QDir对象
      QDir directory2(folderPath2);
      // 遍历文件夹中的所有文件并删除
      QStringList files2 = directory2.entryList(QDir::Files);
      for (const QString& file : files2) {
          QString filePath = directory2.absoluteFilePath(file);
          bool result = QFile::remove(filePath);
          if (!result) {
             ui->textEdit->append("删除文件" + filePath+ "失败！");
          }
      }
      ui->textEdit->append("删除文件!");

//      // 删除文件夹（清空文件夹）
//         bool result = directory.rmdir(".");
//         if (!result) {
//             qDebug() << "清空文件夹失败！";
//         } else {
//             qDebug() << "文件夹已清空！";
//         }

}
