#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<map>
#include<string>
#include<QProgressBar>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    //哈夫曼树
    map<char,string> map;
    //储存map数组
    std::map<char,string> compressmap[100];
    std::string finalname[100];
    //解码
    void decode(QString fileName,QString filePath);
    //更新进度条
    void updateProgress(int value);
    //新的窗口
    QDialog *dialog;
    //初始化
    void Initwindow();
    //进度条
    QProgressBar *progressBar;


private slots:


    //打开盘符对比
    void on_pushButton_clicked();

    //压缩文件
    void on_pushButton_2_clicked();

    //解压缩
    void on_pushButton_3_clicked();

    //一键压缩
    void on_pushButton_4_clicked();
    
    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
