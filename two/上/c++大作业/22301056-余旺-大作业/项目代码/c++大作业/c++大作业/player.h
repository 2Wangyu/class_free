#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include<vector>
#include<iostream>

using namespace std;

class player
{
public:
    player();
    //չʾ��ǰ������
    void Display(vector<string>* chess, const int* arr1, const int* arr2);
    int chessplay[3] = {3,3,3};
    void playchess(int playnum, vector<string>* chess, int* arr);


};



#endif // PLAYER_H
