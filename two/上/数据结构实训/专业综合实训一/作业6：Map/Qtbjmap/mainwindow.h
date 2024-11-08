#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QGraphicsView>
#include <QMainWindow>
#include<QGraphicsScene>
#include<QPushButton>
#include"graph.h"
#include<stack>
#include<QStack>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Graph *g;


    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //利用地图软件确定景点之间的距离，并抽象成图数据结构来表示
    void Initmap();
    QPushButton *arr[11];
    //为ui界面创造绘制线条的
    QGraphicsScene *scene=new QGraphicsScene;
    QPushButton *XUEHUO=new QPushButton();
    QPushButton *SX=new QPushButton();
    QPushButton *YF=new QPushButton();
    QPushButton * GYM=new QPushButton();
    QPushButton *HISTORY=new QPushButton();
    QPushButton *SY=new QPushButton();
    QPushButton *ZHIXING=new QPushButton();
    QPushButton *SD=new QPushButton();
    QPushButton *Lake=new QPushButton();
    QPushButton *Library=new QPushButton();

    //克鲁斯卡尔求整个校园的推荐路径
    void Sort_Eset(Eset *E,int length);
    void InitEset(Eset* E,AMGraph *G);
    void Krusal(AMGraph *G);

    //求最短路径
    void sp_Dijkstra(AMGraph *G,int start,int end);
    int *sp(AMGraph *G,int v,int *path);

    //深度优先求所有的推荐路径
    void DFS(AMGraph *G,int start,int end,bool visited[10],QString string);
    void DFS_AMGraph(AMGraph *G,int start,int end);
    bool visit[10]={false};
    QStack <int>stackV;
    void getPathofTwoNode(int startNode, int endNode);
    void findPath(int startNode, int endNode);
    //

    //数据库存储信息
    void linkedatabasescene();
    void linkedatabasepath();

private slots:

//交互式信息展示
    void on_gym_clicked();
    void on_xuehuo_clicked();
    void on_sx_clicked();
    void on_sy_clicked();
    void on_sd_clicked();
    void on_minghu_clicked();
    void on_library_clicked();
    void on_yf_clicked();
    void on_history_clicked();
    void on_do_2_clicked();


    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
