#include "graph.h"
#include"mainwindow.h"

Graph::Graph() {

    G=new AMGraph;
    createGraph(G);



}
Graph::~Graph(){

    delete G;
}

void Graph::createGraph(AMGraph *G){
    //G->vertices=10;
    G->edges=28;
    for (int var = 0; var<G->vertices; ++var) {
        G->vertex[var]=var+1;
    }

    //默认不带权重
    for (int  i= 0;  i<G->vertices; i++) {
        for (int j = 0; j < G->vertices; ++j) {
            G->edge[i][j]=0;
        }
    }
    //给矩阵的每一条边加上权重
    G->edge[0][1]=303;
    G->edge[0][2]=237;
    G->edge[0][3]=279;
    G->edge[0][4]=306;
    G->edge[0][5]=324;
    G->edge[0][6]=456;
    G->edge[0][7]=597;

    G->edge[1][0]=303;
    G->edge[2][0]=237;
    G->edge[3][0]=279;
    G->edge[4][0]=306;
    G->edge[5][0]=324;
    G->edge[6][0]=456;
    G->edge[7][0]=597;


    G->edge[1][2]=173;
    G->edge[2][3]=132;
    G->edge[3][4]=146;
    G->edge[4][5]=136;
    G->edge[5][6]=192;
    G->edge[6][7]=141;

    G->edge[2][1]=173;
    G->edge[3][2]=132;
    G->edge[4][3]=146;
    G->edge[5][4]=136;
    G->edge[6][5]=192;
    G->edge[7][6]=141;


    G->edge[8][1]=152;
    G->edge[8][2]=188;
    G->edge[8][3]=207;
    G->edge[8][4]=343;
    G->edge[8][5]=456;
    G->edge[8][6]=601;
    G->edge[8][7]=676;

    G->edge[1][8]=152;
    G->edge[2][8]=188;
    G->edge[3][8]=207;
    G->edge[4][8]=343;
    G->edge[5][8]=456;
    G->edge[6][8]=601;
    G->edge[7][8]=676;


    G->edge[9][1]=286;
    G->edge[9][2]=265;
    G->edge[9][3]=196;
    G->edge[9][4]=257;
    G->edge[9][5]=344;
    G->edge[9][6]=533;
    G->edge[9][7]=605;

    G->edge[1][9]=286;
    G->edge[2][9]=265;
    G->edge[3][9]=196;
    G->edge[4][9]=257;
    G->edge[5][9]=344;
    G->edge[6][9]=533;
    G->edge[7][9]=605;

    G->edge[8][9]=144;
    G->edge[9][8]=144;


}
