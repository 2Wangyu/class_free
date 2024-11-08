#ifndef GRAPH_H
#define GRAPH_H

struct AMGraph{
    int vertex[10];
    int edge[10][10];
    const int vertices=10;
    int edges;
};

//克鲁斯卡尔的边
struct Eset{
    //起点
    int start;
    //终点
    int end;

    int weight;

};

class Graph
{
public:
    AMGraph *G;
    Graph();
    ~Graph();
    void createGraph(AMGraph *G);

};

#endif // GRAPH_H
